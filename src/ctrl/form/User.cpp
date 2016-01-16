
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"

#include <ctrl/form/User.h>


using namespace ctrl::form;


static const std::string birthdayFormat = "%Y-%n-%e";
std::string birthdayFromDate(const Poco::DateTime &date)
{
	return Poco::DateTimeFormatter::format(date, birthdayFormat);
}
Poco::DateTime birthdayToDate(const std::string &bday)
{
	Poco::DateTime date;
	int timeZoneDifferential;
	if(Poco::DateTimeParser::tryParse(birthdayFormat, bday, date, timeZoneDifferential))
		return date;
	return Poco::DateTime(Poco::Timestamp(0));
}


User::User()
{
	userTable.hideEmptyCollumns(true);

	userGroups.prompt = "Set Group";
	userGroups.add("Admin", "0");
	userGroups.add("User", "2");
	userGroups.add("Subscriber", "3");

	addEvent(updateUser);
	addEvent(removeUser);
	addEvent(selectUser);
	addEvent(updateGroup);
	addEvent(paginate);
}
User::~User()
{
}

std::string User::format(const std::string &in)
{
	return core::util::Html::format(in);
}
User::Mode User::mode()
{
	if(users)
		return MODE_USERS;
	else
		return MODE_SETTINGS;
}
std::string User::param()
{
	std::string ret;
	switch(mode())
	{
	case MODE_USERS: ret += "m=users&"; break;
	case MODE_SETTINGS: ret += ""; break;
	}

	ret += "p=" + std::to_string(paginator.page()) + "&";
	ret += "s=" + std::to_string(userTable.sort()) + "&";

	return ret;
}

void User::onEnter()
{
	val["status"] = "";

	/// Fill settings
	val["firstName"] = user().firstName();
	val["lastName"] = user().lastName();
	val["phoneNumber"] = user().phoneNumber();
	val["country"] = user().country();
	val["state"] = user().state();
	val["birthday"] = birthdayFromDate(user().birthday());
}

void User::onLoad()
{
	users = NULL;

	/// Parameters
	auto &mode = val["m"];
	std::int64_t sort = 0; std::istringstream(val["s"]) >> sort;
	std::int32_t page = INTMAX(32); std::istringstream(val["p"]) >> page;

	userTable.sort(sort);
	if(page != INTMAX(32)) paginator.page(page);

	/// Mode
	switch(0)
	{ default:

		/// Prepare User table
		bool modeUsers = mode == "users" && user().group() == user().ADMIN;
		if(modeUsers)
		{
			paginator.doPaging(ctrl().service().getUsersCount());
			users = ctrl().service().getUsers(-1, userTable.sort(), paginator.limit(), paginator.offset());
			userTable.set(users);
			break;
		}

		userTable.clear();
	}

	/// Reset parameters
	val["m"] = val["s"] = val["p"] = "";
}

void User::updateUser(std::istream *stream)
{
	if(!user()) return;

	/// Parameters
	auto firstName = val["firstName"];
	auto lastName = val["lastName"];
	auto phoneNumber = val["phoneNumber"];
	auto country = val["country"];
	auto state = val["state"];
	auto birthday = birthdayToDate(val["birthday"]);

	val["status"] = "";

	/// Validation
	if(!birthday.timestamp().raw())
		val["status"] = "*Incorrect birthday format!";
	if(lastName.empty())
		val["status"] = "*Please enter Last Name!";
	if(firstName.empty())
		val["status"] = "*Please enter First Name!";

	if(!val["status"].empty()) return;

	model::User user = this->user();
	user.firstName(firstName);
	user.lastName(lastName);
	user.phoneNumber(phoneNumber);
	user.country(country);
	user.state(state);
	user.birthday(birthday);
	ctrl().service().updateUser(user);
	ctrl().update();

	val["status"] = "Updated successfully!";
}

void User::removeUser(std::istream *stream)
{
	if(user().group() != user().ADMIN) return;

	for(std::uint32_t i=0; i<users->size(); ++i) {
		if(!userTable.rows()[i]->checked) continue;
		ctrl().service().deleteUser(users()[i]->id());
	}

	userTable.clear();
}

void User::selectUser(std::istream *stream)
{
	if(user().group() != user().ADMIN) return;

	/// Parameters
	core::DataID rowAll = 0; std::istringstream(val["a"]) >> rowAll;
	core::DataID rowInd = core::DataID(-1); std::istringstream(val["r"]) >> rowInd;
	val["a"] = val["r"] = "";

	if(rowAll) {
		userTable.toggleAll();
		return;
	}

	userTable.toggle(rowInd);
}

void User::updateGroup(std::istream *stream)
{
	if(user().group() != user().ADMIN) return;

	/// Parameters
	std::int32_t group = -1; std::istringstream(val["g"]) >> group;
	val["g"] = "";

	if(group < 0) return;

	for(std::uint32_t i=0; i<users->size(); ++i) {
		if(!userTable.rows()[i]->checked) continue;
		users()[i]->group((model::User::Group)group);
		ctrl().service().updateUser(*users()[i]);
	}

	userTable.clear();
}

void User::paginate(std::istream *stream)
{
	/// Parameters
	std::int32_t sort = INTMAX(32); std::istringstream(val["s"]) >> sort;
	std::int32_t page = INTMAX(32); std::istringstream(val["p"]) >> page;
	val["s"] = val["p"] = "";

	if(sort != INTMAX(32)) userTable.sort(sort);
	else if(page != INTMAX(32)) paginator.page(page);
	else paginator.extend();

	ctrl().redirect(path() + "?" + param());
}