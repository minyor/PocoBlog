
#include "Poco/URI.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"

#include <core/Header.h>
#include <core/Server.h>
#include <core/Session.h>
#include <core/Page.h>


using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Util::ServerApplication;
using namespace core;


class DefaultPage : public Page
{
};

static Page &defaultPage()
{
	static DefaultPage page;
	return page;
}


void HTTPCustomResponse::redirect(const std::string &uri, HTTPStatus status, int unused)
{
	server().forceCommit(*this, uri);
	((Poco::Net::HTTPServerResponse *)this)->redirect(uri, status);
}
void HTTPCustomResponse::requireAuthentication(const std::string &realm, int unused)
{
	server().forceCommit(*this, "*");
	((Poco::Net::HTTPServerResponse *)this)->requireAuthentication(realm);
}
std::ostream &HTTPCustomResponse::send(int unused)
{
	server().forceCommit(*this, "*");
	return ((Poco::Net::HTTPServerResponse *)this)->send();
}
void HTTPCustomResponse::sendBuffer(const void *pBuffer, std::size_t length, int unused)
{
	server().forceCommit(*this, "*");
	((Poco::Net::HTTPServerResponse *)this)->sendBuffer(pBuffer, length);
}
void HTTPCustomResponse::sendContinue(int unused)
{
	server().forceCommit(*this, "*");
	((Poco::Net::HTTPServerResponse *)this)->sendContinue();
}
void HTTPCustomResponse::sendFile(const std::string &path, const std::string &mediaType, int unused)
{
	server().forceCommit(*this, "*");
	((Poco::Net::HTTPServerResponse *)this)->sendFile(path, mediaType);
}


void Session::genID()
{
	_id = core::util::Hash::salt(64);
}
void Session::genCsrfID()
{
	_lastCsrfGen = Poco::Timestamp();
	_csrfID = core::util::Hash::salt(8);
}
struct Session::Prop
{
	std::string _path;
	std::string _lastPath;
	std::string _prevPath;
	std::string _pathParams;
};
Session::Prop *Session::saveProp()
{
	Session::Prop *par = new Session::Prop;
	par->_path = _path;
	par->_lastPath = _lastPath;
	par->_prevPath = _prevPath;
	par->_pathParams = _pathParams;
	return par;
}
void Session::loadProp(Session::Prop *par)
{
	_path = par->_path;
	_lastPath = par->_lastPath;
	_prevPath = par->_prevPath;
	_pathParams = par->_pathParams;
	delete par;
}
void Session::receive(std::string event, Poco::Net::NameValueCollection &params, std::istream *stream)
{
	using namespace Poco::Net;

	//printff("_path='%s'; _lastPath='%s' _prevPath='%s';\n", _path.c_str(), _lastPath.c_str(), _prevPath.c_str());

	Form &form = this->form();
	if(path() != lastPath())
	{
		FormMap::iterator it = _forms.find(lastPath());
		if(it != _forms.end())
		{
			onLeave(*it->second);
			it->second->onLeave();
		}

		onEnter(form);
		form.onEnter();
	}
	else if(!form.enteredAfterCreation())
	{
		form.enteredAfterCreation(true);
		onEnter(form);
		form.onEnter();
	}

	for(NameValueCollection::ConstIterator iterator = params.begin(); iterator != params.end(); ++iterator)
		form[iterator->first] = iterator->second;

	auto it = form.val.find("event");
	if(it != form.val.end())
	{
		event = it->second;
		form.val.erase("event");
	}

	if(event.empty())
	{
		onLoad(form);
		form.onLoad();
		return;
	}

	onAction(event, form, stream);
	call(event, form, stream);
	form.call(event, stream);
}

Session::Session()
{
	_page = &defaultPage();
	genID();
	genCsrfID();
	_path = _lastPath = _prevPath = "/";
	_locked = false;
}
Session::~Session()
{
}

Session::operator bool () const
{
	return (bool)*_user;
}

Form &Session::form()
{
	FormMap::iterator it = _forms.find(page().path());
	if(it != _forms.end()) return *it->second;

	Form *form = page().newClass() ? (Form *)page().newClass()() : new Form();
	_forms[page().path()] = std::unique_ptr<Form>(form);
	form->session(*this);
	return *form;
}

void Session::update()
{
	if(user().registered())
		service().getUser(*_user, user().id());
}
void Session::reidentify()
{
	_lastCsrfGen -= Poco::Timestamp::TimeDiff(server().conf().changeIdTimeOut());
}
void Session::redirect(const std::string &uri)
{
	response().redirect(uri);
}
std::ostream &Session::send()
{
	return response().send();
}
void Session::comeback()
{
	response().sendContinue();
}
/*void Session::redirect(const std::string &to)
{
	server().forceCommit(request(), to);
	if(server().forcedUrl(request()) == "*") return;
	response().redirect(to);
}
void Session::send()
{
	server().forceCommit(request(), "*");
}*/

void Session::call(const std::string &event, core::Form &form, std::istream *stream)
{
	auto it = _events.find(event);
	if(it == _events.end()) return;
	(this->*it->second)(form, stream);
}
void Session::add(const std::string &event, Callback callback)
{
	auto it = _events.find(event);
	if(it != _events.end()) return;
	_events[event] = callback;
}

void Session::onEnter(core::Form &form) {}
void Session::onLeave(core::Form &form) {}
void Session::onLoad(core::Form &form) {}
void Session::onAction(const std::string &event, core::Form &form, std::istream *stream) {}

void Session::path(const std::string &pathVal, const std::string &paramsVal)
{
	_lastPath = _path;
	if(pathVal != _path) _prevPath = _path;
	_path = pathVal;
	_pathParams = paramsVal;
}
std::string Session::url() const
{
	return path() + _pathParams;
}
const std::string &Session::path() const
{
	return page().path();
}


Form::Form()
{
	_enteredAfterCreation = false;
}
Form::~Form()
{
}

bool Form::checkPath(const std::string &url) const
{
	return Poco::URI(path()).getPath() == Poco::URI(url).getPath();
}

void Form::call(const std::string &event, std::istream *stream)
{
	auto it = _events.find(event);
	if(it == _events.end()) return;
	(this->*it->second)(stream);
}
void Form::add(const std::string &event, Callback callback)
{
	auto it = _events.find(event);
	if(it != _events.end()) return;
	_events[event] = callback;
}

void Form::htmlTemplate(const std::string &path, const std::string &source, TemplateMap &map, std::ostream &responseStream)
{
	const static std::string tileKey = "<@TILE=";
	const static std::string tileEnd = "@>";

	//std::string templatePath = source.substr(0, source.find_last_of("/\\")) + path;
	std::string templatePath = server().conf().webInfFolder() + "/" + path;
	std::ifstream infile(templatePath);
	for(std::string line; std::getline(infile, line); )
	{
		size_t isTileKey = line.find(tileKey);
		if(isTileKey != std::string::npos)
		{
			isTileKey += tileKey.size();
			size_t isTileEnd = line.find(tileEnd, isTileKey);
			if(isTileEnd != std::string::npos)
			{
				std::string tile = line.substr(isTileKey, isTileEnd - isTileKey);
				std::shared_ptr<TemplateStream> &chunk = map[tile];
				if(!chunk)
				{
					std::ifstream infile(templatePath.substr(0, templatePath.find_last_of("/\\")+1) + tile + ".html");
					if(infile) responseStream << infile.rdbuf();
					continue;
				}

				responseStream << chunk->str();
				continue;
			}
		}

		responseStream << line << "\n";
	}
}

void Form::htmlInstance(const std::string &name, const std::string &source, TemplateMap &map, std::ostream &responseStream)
{
	(void)source;

	std::shared_ptr<TemplateStream> &chunk = map[name];
	if(!chunk)return;

	responseStream << chunk->str();
}

std::string Form::htmlTagPar(const std::string &name)
{
	return std::string("name=\"") + name + std::string("\" value=\"") +
		(*this)[name] + std::string("\"");
}

std::string Form::htmlCSRF()
{
	return std::string("<input type=\"hidden\" name=\"csrfID\" value=\"") + 
		session().csrfID() + std::string("\">");
}

void Form::onEnter() {}
void Form::onLeave() {}
void Form::onLoad() {}

const std::string &Form::path() const
{
	return page().path();
}