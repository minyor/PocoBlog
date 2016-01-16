
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"

#include <core/Header.h>
#include <ctrl/Controller.h>


using namespace core;
using namespace ctrl;


struct Controller::Data
{
	Controller &me;

	Data(Controller &me) : me(me) {}
};

Controller::Controller() : _data(new Data(*this))
{
	menuList.add(new core::MenuEntry("Home", core::server().conf().defaultPage()));
	menuList.add(new core::MenuEntry("Documentation", "/Documentation"));
	menuList.add(new core::MenuEntry("Download", "/Download"));
	menuList.add(new core::MenuEntry("Blog", "/Blog"));
	menuList.add(new core::MenuEntry("Contact", "/Contact"));

	sidebarList.add(new core::MenuEntry("Home", core::server().conf().defaultPage()));
	sidebarList.add(new core::MenuEntry("Documentation", "/Documentation"));
	sidebarList.add(new core::MenuEntry("Download", "/Download"));
	sidebarList.add(new core::MenuEntry("Blog", "/Blog"));
	sidebarList.add(new core::MenuEntry("Contact", "/Contact"));

	addEvent(logout);
	addEvent(login);
	addEvent(search);
	addEvent(parser);
}
Controller::~Controller()
{
}

void Controller::logout(core::Form &form, std::istream *stream)
{
	server().logout(*this);
}

void Controller::login(core::Form &form, std::istream *stream)
{
	/// Parameters
	auto &username = form["username"];
	auto &password = form["password"];

	form["status"] = "";

	/// Validation
	if(!server().login(request(), username, password))
		form["status"] = "*Sorry, but your username or password is incorrect!";

	form.val.erase("password");
	if(!form["status"].empty()) return;

	if(form.path() == "/Login") response().redirect(prevPath());
}

void Controller::search(core::Form &form, std::istream *stream)
{
	auto &query = form["query"];
	redirect("/Blog?q=" + query);
}

void Controller::parser(core::Form &form, std::istream *stream)
{
	send() << core::util::Html::format(form["data"]);
	form["data"] = "";
}