//
// Base SQL database service
//
// Copyright (c) 2016, minyor.
//
// License:	BSD
//


#ifndef CORE_DB_SQL_H
#define CORE_DB_SQL_H


#include <core/Header.h>
#include <model/User.h>


namespace core
{
	namespace db
	{
		class Table;
		typedef Poco::Data::Session DataSession;
		typedef void (*SqlToStringProc)(core::Vector<std::string> &to, void *var, const Table &table, bool visibleOnly);

		class Sql
		{
			struct Data;
			std::unique_ptr<Data> _data;

		public:
			Sql();
			virtual ~Sql();

		public:
			std::unique_ptr<DataSession> session();

		public:
			void addTable(Table *table);
			Table &table(const std::string &name);
			__inline Table &table(const char *name) { return table((std::string)name); }
			template<typename T> __inline Table &table(const T &data) { return table(typeid(T).name()); }

		protected:
			virtual void onInit(core::db::DataSession &session);

		public:
			bool createUser(model::User &user);
			bool updateUser(model::User &user);
			bool updateUserPass(model::User &user, const std::string &password);
			bool deleteUser(core::UserID id);
			bool deleteInactiveUser(model::User &user);
			bool getUserByUsername(model::User &user, const std::string &username);
			bool getUserByEmail(model::User &user, const std::string &email);
			bool getUser(model::User &user, core::UserID id);
			Vector<model::User> getUsersByGroup(core::UserGroup group);
			/**
			 * @param sort : column number begining from 1, negative number: reverse order, 0: no sorting;
			 */
			Vector<model::User> getUsers(std::int16_t group = -1, std::int8_t sort = 0, std::int64_t limit = INTMAX(64), std::int64_t offset = 0);
			std::uint64_t getUsersCount();

		};

		class Table
		{
		public:
			class Column
			{
				std::string _name;
				std::string _type;
				bool _visible;

			public:
				__inline Column(std::string name, std::string type) : _name(name), _type(type), _visible(true) {}

			public:
				__inline void name(const std::string &val) { _name = val; }
				__inline const std::string &name() const { return _name; }

				__inline void type(const std::string &val) { _type = val; }
				__inline const std::string &type() const { return _type; }

				__inline void visible(bool val) { _visible = val; }
				__inline bool visible() const { return _visible; }

			};

		private:
			std::vector<std::unique_ptr<Column> > _columns;
			SqlToStringProc _toStringProc;
			std::string _name, _className;
			std::string _createQuery;
			std::string _insertQuery;
			std::string _updateQuery;
			std::string _lastIdQuery;

		public:
			Table(const std::string &name, const std::string &className, SqlToStringProc toStringProc);
			~Table();

		public:
			__inline operator bool() const { return !_name.empty(); }

		public:
			void addColumn(Column *col);
			Column &column(std::uint32_t i) const;
			void refresh();

		public:
			core::Vector<Column *> header() const;
			core::Vector<std::string> headerNames(bool visibleOnly = false) const;
			core::Vector<std::string> data(void *v, bool visibleOnly = false) const;
			template<typename T> core::Vector<std::string> data(T &v, bool visibleOnly = false) const { return data(&v); }

		public:
			__inline std::uint32_t size() const { return _columns.size(); }
			__inline SqlToStringProc toStringProc() const { return _toStringProc; }
			__inline const std::string &name() const { return _name; }
			__inline const std::string &className() const { return _className; }
			__inline const std::string &createQuery() const { return _createQuery; }
			__inline const std::string &insertQuery() const { return _insertQuery; }
			__inline const std::string &updateQuery() const { return _updateQuery; }
			__inline const std::string &lastIdQuery() const { return _lastIdQuery; }

		};
	}
}


#endif // CORE_DB_SQL_H
