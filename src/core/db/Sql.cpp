
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/SessionPool.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/TypeHandler.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/MySQL/Connector.h"

#include <core/Header.h>
#include <core/Util.h>
#include <core/Server.h>
#include <core/db/Sql.h>
#include <core/db/SQLTable.h>


using namespace Poco::Data::Keywords;
using Poco::DateTime;
using Poco::DateTimeFormatter;
using Poco::Data::SessionPool;
using Poco::Data::Session;
using Poco::Data::Statement;
using namespace core;
using namespace core::db;


struct core::db::Sql::Data
{
	typedef std::map<std::string, std::shared_ptr<Table> > TableMap;

	Sql &me;
	bool _initialized;
	TableMap _tables;
	std::unique_ptr<SessionPool> _pool;

public:
	Data(Sql &me) : me(me)
	{
		_initialized = false;
	}

public:
	void refresh()
	{
		if(_initialized) return;
		_initialized = true;

		core::server().initSql();
		initSQL();

		std::unique_ptr<DataSession> session = this->session();
		Table &table = me.table("User");

		try {
			*session << table.createQuery(), now;
			printff("SQL 'User' table created.\n");
		}
		catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); }
		catch(...) {}

		try { me.onInit(*session); }
		catch(...) {}
	}
	void initSQL()
	{
		Poco::Data::SQLite::Connector::registerConnector();
		Poco::Data::MySQL::Connector::registerConnector();
		_pool = std::unique_ptr<SessionPool>(new SessionPool(
			server().conf().sqlConnector(),
			server().conf().sqlConnectionString(),
			server().conf().sqlMinSessions(),
			server().conf().sqlMaxSessions(),
			server().conf().sqlIdleTime()
		));
	}
	
	__inline std::unique_ptr<DataSession> session()
	{
		refresh();
		return std::unique_ptr<DataSession>(new DataSession(_pool->get()));
	}

};


namespace
{
	class NotFoundTable : public Table
	{
	public:
		NotFoundTable() : Table("", "", NULL) {}
	};
}

static Table &notFoundTable()
{
	static NotFoundTable table;
	return table;
}

Sql::Sql() : _data(new Data(*this))
{
}
Sql::~Sql()
{
}

void Sql::addTable(Table *table)
{
	_data->_tables[table->name()] = std::unique_ptr<Table>(table);
	_data->_tables[table->className()] = _data->_tables[table->name()];
	table->refresh();
}
Table &Sql::table(const std::string &name)
{
	Data::TableMap::iterator it = _data->_tables.find(name);
	if(it == _data->_tables.end()) return notFoundTable();
	return *it->second;
}

std::unique_ptr<DataSession> Sql::session()
{
	return _data->session();
}
void Sql::onInit(core::db::DataSession &session)
{
}

static std::mutex userMutex;

bool Sql::createUser(model::User &user)
{
	std::string password = user.password();
	{
		std::lock_guard<std::mutex> lock(userMutex);

		user.username(core::util::Html::format(user.username()));
		user.email(core::util::Html::format(user.email()));
		user.firstName(core::util::Html::format(user.firstName()));
		user.lastName(core::util::Html::format(user.lastName()));
		user.phoneNumber(core::util::Html::format(user.phoneNumber()));

		user.createDate(Poco::DateTime());
		user.modifyDate(Poco::DateTime());
		user.password("");

		std::unique_ptr<DataSession> session = this->session();

		try {
			user.id(0);
			core::UserID lastId;
			Statement(*session) << this->table("User").insertQuery(), use(user), now;
			Statement(*session) << this->table("User").lastIdQuery(), into(lastId), now;
			user.id(lastId); printff("createUser: %ld\n", user.id());
		}
		catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
		catch(...) { return false; }

		/// The first created user shall be admin
		if(user.id() == 1)
		{
			user.group(user.ADMIN);
			printff("ADMIN: %d\n", (int)user.group());
		}
	}

	return updateUserPass(user, password);
}
bool Sql::updateUser(model::User &user)
{
	try {
		std::unique_ptr<DataSession> session = this->session();
		Table &table = this->table("User");

		user.username(core::util::Html::format(user.username()));
		user.email(core::util::Html::format(user.email()));
		user.firstName(core::util::Html::format(user.firstName()));
		user.lastName(core::util::Html::format(user.lastName()));
		user.phoneNumber(core::util::Html::format(user.phoneNumber()));

		core::UserID id = user.id();
		if(!id) return false;

		user.modifyDate(Poco::DateTime());
		Statement insert(*session);
		insert << table.updateQuery() + " WHERE _id=?", use(user), use(id);
		insert.execute();
		return true;
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
}
bool Sql::updateUserPass(model::User &user, const std::string &password)
{
	std::lock_guard<std::mutex> lock(userMutex);

	std::string salt = core::util::Hash::salt(64);
	std::string hash = core::util::Hash::hash(password + salt);

	user.password(hash + salt);
	user.modifyDate(Poco::DateTime());
	updateUser(user);
	return true;
}
bool Sql::deleteUser(core::UserID id)
{
	try {
		std::unique_ptr<DataSession> session = this->session();

		if(!id) return false;
		Statement insert(*session);
		insert << "DELETE FROM User WHERE _id=?", use(id);
		insert.execute();
		return true;
	}
	catch(...) { return false; }
}
bool Sql::deleteInactiveUser(model::User &user)
{
	if(user.group() != user.INACTIVE) return false;
	if((user.modifyDate().timestamp().elapsed() / 60000000) < server().conf().activationTimeOut()) return false;

	deleteUser(user.id());
	printff("Inactive User '%s' deleted!\n", user.username().c_str());
	user = model::User();
	return true;
}
bool Sql::getUserByUsername(model::User &user, const std::string &username)
{
	try {
		std::unique_ptr<DataSession> session = this->session();

		Statement select(*session);
		std::string str = username;
		select << "SELECT * FROM User WHERE _username = ?", into(user), use(str),
			range(0, 1); //  iterate over result set one row at a time

		select.execute();
		if(!user.registered()) return false;
		return !deleteInactiveUser(user);
	}
	catch(...) { return false; }
}
bool Sql::getUserByEmail(model::User &user, const std::string &email)
{
	try {
		std::unique_ptr<DataSession> session = this->session();

		Statement select(*session);
		std::string str = email;
		select << "SELECT * FROM User WHERE _email = ?", into(user), use(str),
			range(0, 1); //  iterate over result set one row at a time

		select.execute();
		if(!user.registered()) return false;
		return !deleteInactiveUser(user);
	}
	catch(...) { return false; }
}
bool Sql::getUser(model::User &user, core::UserID id)
{
	try {
		std::unique_ptr<DataSession> session = this->session();

		Statement select(*session);
		select << "SELECT * FROM User WHERE _id=?", into(user), use(id),
			range(0, 1); //  iterate over result set one row at a time

		select.execute();
		if(!user.registered()) return false;
		return !deleteInactiveUser(user);
	}
	catch(...) { return false; }
}
Vector<model::User> Sql::getUsersByGroup(core::UserGroup group)
{
	try {
		std::unique_ptr<DataSession> session = this->session();

		std::uint8_t _group = (std::uint8_t)group;
		model::User user;
		Statement select(*session);
		select << "SELECT * FROM User WHERE _group=?", into(user), use(_group),
			range(0, 1); //  iterate over result set one row at a time

		Vector<model::User> users;
		while(!select.done()) {
			select.execute(); if(!user.id()) continue;
			users.add(new model::User(user));
		}
		return users;
	}
	catch(...) { return Vector<model::User>(); }
}
/**
 * @param sort : column number begining from 1, negative number: reverse order, 0: no sorting;
 */
Vector<model::User> Sql::getUsers(std::int16_t group, std::int8_t sort, std::int64_t limit, std::int64_t offset)
{
	model::User val;
	Vector<model::User> ret;

	Poco::Nullable<std::int16_t> grp = group; if(group < 0) grp = Poco::NULL_GENERIC;
	std::int8_t sortIndex = abs(sort) - 1;
	std::string column = (sortIndex >= 0 && sortIndex < table("User").size()) ? table("User").column(sortIndex).name() : "";
	printff("group=%d; grp=%d; sort='%s'\n", group, grp.isNull() ? -7 : grp.operator short &(), column.c_str());

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << (std::string)"SELECT AUser.* FROM (\
				SELECT _id FROM User WHERE ? IS NULL OR _group=?\
				ORDER BY " + (column.empty() ? (std::string)"_id " : (column + (sort < 0 ? " DESC " : " ASC "))) + "LIMIT ? OFFSET ?\
			) AS L INNER JOIN User AS AUser ON AUser._id=L._id\
			ORDER BY " + (column.empty() ? (std::string)"AUser._id " : ("AUser." + column + (sort < 0 ? " DESC " : " ASC "))),
			into(val), use(grp), use(grp), use(limit), use(offset), range(0, 1); //  iterate over result set one row at a time

		while(!select.done()) {
			select.execute(); if(!val.id()) continue;
			ret.add(new model::User(val));
		}
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return Vector<model::User>(); }
	catch(...) { return Vector<model::User>(); }
	return ret;
}
std::uint64_t Sql::getUsersCount()
{
	std::uint64_t count = 0;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT COUNT(_id) FROM User", into(count),
			range(0, 1), now; //  iterate over result set one row at a time
	}
	catch(...) { return 0; }
	return count;
}


namespace
{
	class NotFoundColumn : public Table::Column
	{
	public:
		NotFoundColumn() : Table::Column("", "") {}
	};
}

static Table::Column &notFoundColumn()
{
	static NotFoundColumn column;
	return column;
}

Table::Table(const std::string &name, const std::string &className, SqlToStringProc toStringProc) :
	_name(name), _className(className), _toStringProc(toStringProc)
{
}
Table::~Table()
{
}

void Table::addColumn(Table::Column *col)
{
	_columns.push_back(std::unique_ptr<Table::Column>(col));
}
Table::Column &Table::column(std::uint32_t i) const
{
	if(i < _columns.size()) return *_columns[i];
	return notFoundColumn();
}
void Table::refresh()
{
	std::string str = server().conf().sqlConnector();
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	bool isSQLite = strstr(str.c_str(), "SQLITE");

	for(std::uint32_t i=0; i<size(); ++i) {
		str = column(i).type(); std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		if(strstr(str.c_str(), "PRIMARY")) str += isSQLite ? " AUTOINCREMENT" : " AUTO_INCREMENT";
		column(i).type(str);

		str = column(i).name(); std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		column(i).visible(!strstr(str.c_str(), "PASSW"));
	}

	_createQuery = "CREATE TABLE " + name() + " (";
	for(std::uint32_t i=0, e=size()-1; i<size(); ++i) _createQuery += column(i).name() + " " + column(i).type() + (i == e ? "" : ", ");
	_createQuery += ")";

	_insertQuery = "INSERT INTO " + name() + " (";
	for(std::uint32_t i=0, e=size()-1; i<size(); ++i) _insertQuery += column(i).name() + (i == e ? "" : ", ");
	_insertQuery += ") VALUES(";
	for(std::uint32_t i=0, e=size()-1; i<size(); ++i) _insertQuery += std::string("?") + (i == e ? "" : ", ");
	_insertQuery += ")";

	_updateQuery = "UPDATE " + name() + " SET ";
	for(std::uint32_t i=0, e=size()-1; i<size(); ++i) _updateQuery += column(i).name() + "=?" + (i == e ? "" : ", ");

	_lastIdQuery = isSQLite ? "SELECT last_insert_rowid()" : "SELECT last_insert_id()";
}

core::Vector<Table::Column *> Table::header() const
{
	core::Vector<Column *> ret;
	for(std::uint32_t i=0; i<size(); ++i) ret.add(new Column *(&column(i)));
	return ret;
}
core::Vector<std::string> Table::headerNames(bool visibleOnly) const
{
	core::Vector<std::string> ret;
	for(std::uint32_t i=0; i<size(); ++i) ret.add(new std::string((!visibleOnly || column(i).visible()) ? column(i).name() : ""));
	return ret;
}
core::Vector<std::string> Table::data(void *v, bool visibleOnly) const {
	core::Vector<std::string> ret;
	if(_toStringProc) _toStringProc(ret, v, *this, visibleOnly);
	return ret;
}