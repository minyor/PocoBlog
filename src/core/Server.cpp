//
// Server class and singletone
// to store configuration and sessions
//
// Copyright (c) 2016, minyor.
//
// License:	BSD
//


#include "Poco/URI.h"
#include "Poco/Net/HTTPCookie.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"

#include <core/Header.h>
#include <core/Server.h>
#include <core/Page.h>


using namespace core;


const static char EVENT_SYMBOL = '*';


Session *CreatorBase::newSession() const
{
	return new Session;
}
db::Sql *CreatorBase::newSql() const
{
	return new db::Sql;
}


class NotFoundPage : public Page
{
};

static Page &notFoundPage()
{
	static NotFoundPage page;
	return page;
}


class IgnorePage : public Page
{
	class RequestHandler: public Poco::Net::HTTPRequestHandler
	{
		void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
		}
	};
	Poco::Net::HTTPRequestHandler *newHandler()
	{
		return new RequestHandler;
	}
};

static Page &ignorePage()
{
	static IgnorePage page;
	return page;
}


class Server::EventHandler: public Poco::Net::HTTPRequestHandler
{
public:
	EventHandler() {}
	~EventHandler() {}

	void handle(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
	{
		auto session = server().session(request, response);
		if(core::server().forcedUrl(response) == "*" || response.sent()) return;
		return response.redirect(session->url());

		/*printff("redirectUrl: '%s'\n", redirectUrl.c_str());
		{
			request.setURI(redirectUrl);
			std::unique_ptr<Poco::Net::HTTPRequestHandler> handler = std::unique_ptr<Poco::Net::HTTPRequestHandler>(
				core::server().newHandler(Poco::URI(redirectUrl).getPath()));
			handler->handleRequest(request, response);
		}
		return;*/

		response.setChunkedTransferEncoding(true);
		response.setContentType("text/html");

		std::ostream& ostr = response.send();
		ostr <<
			"<html>\n"
			"<head>\n"
			"<title>Event Page</title>\n"
			"</head>\n"
			"<body>\n"
			"<h1>You should not see me!</h1>\n"
			"</body>\n";
	}

public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

};

class EventPage : public Page
{
public:
	Poco::Net::HTTPRequestHandler *newHandler() { return new Server::EventHandler; }
};

static Page &eventPage()
{
	static EventPage page;
	return page;
}


static std::vector<void (*)()> &pageInits()
{
	static std::vector<void (*)()> inits;
	return inits;
}

static void initPages()
{
	static bool initialized = false;
	if(initialized) return;
	initialized = true;
	for(size_t i=0; i<::pageInits().size(); ++i) ::pageInits()[i]();
}

static std::vector<void (*)()> &sqlInits()
{
	static std::vector<void (*)()> inits;
	return inits;
}

static void initSql()
{
	static bool initialized = false;
	if(initialized) return;
	initialized = true;
	for(size_t i=0; i<::sqlInits().size(); ++i) ::sqlInits()[i]();
}

static core::Mutex getPageMutex;
static core::Mutex setPageMutex;
static core::Mutex sessionMutex;
static core::Mutex requestMutex;

#ifdef _WIN32
	#include <Windows.h>
#elif __APPLE__
	#include <libproc.h>
#else
#endif

static std::string appDir()
{
	const static int len = 512;
	char pBuf[len];

#ifdef _WIN32
	int bytes = GetModuleFileName(NULL, pBuf, len);
	if(bytes == 0) pBuf[0] = '\0';
#elif __APPLE__
	pid_t pid = getpid(); int ret;

	if ( argc > 1 ) {
		pid = (pid_t) atoi(argv[1]);
		ret = proc_pidpath (pid, pBuf, sizeof(pBuf));
		if ( ret <= 0 ) {
			fprintf(stderr, "PID %d: proc_pidpath ();\n", pid);
			fprintf(stderr, "    %s\n", strerror(errno));
		} else {
			printff("proc %d: %s\n", pid, pBuf);
		}
	}
#else
	char szTmp[32];
	sprintf(szTmp, "/proc/%d/exe", getpid());
	int bytes = std::min(readlink(szTmp, pBuf, len), ssize_t(len - 1));
	if(bytes >= 0)
		pBuf[bytes] = '\0';
#endif

	std::string path = pBuf;
	return path.substr(0, path.find_last_of("/\\"));
}

Config::Config()
{
	_https = false;
	_port = 8080;
	_portUPnP = 0;
	_timeOut = 20;/*min*/
	_lifeTime = 0;/*min*/
	_changeIdTimeOut = 1;/*min*/
	_activationTimeOut = 60;/*min*/
	_dateFormat = "%W, %e %b %y %H:%M:%S %Z";
	_dateTimeZone = Poco::DateTimeFormatter::UTC;

	_sqlConnector = "SQLite";
	_sqlConnectionString = "data.db";
	_sqlMinSessions = 1;
	_sqlMaxSessions = 32;
	_sqlIdleTime = 60;

	_smtpHost = "smtp.gmail.com";
	_smtpPort = 587;
	_smtpUsername = "";
	_smtpPassword = "";
}
Config::~Config()
{
}

void Config::emoticon(const std::string &name, const std::string &src)
{
	_emoticons.add(new Config::Emoticon(name, src));
}

struct Server::Data
{
	struct Request
	{
		Poco::Net::NameValueCollection in, out;
		Poco::Net::HTTPServerRequest *request;
		Poco::Net::HTTPServerResponse *response;
		std::int32_t _locked;
		std::string _redirectTo;
		bool _force;
		__inline Request() { _locked = 0; _force = false; }
	};

	typedef std::map<Poco::Net::HTTPServerResponse *, Request> RequestMap;
	typedef std::map<core::UserID, core::SessionPtr> UserMap;

	RequestMap _requests;
	UserMap _users;
	Server &_server;

	Data(Server &server) : _server(server) {}

	void redirectedUrl(Poco::Net::HTTPServerResponse &response, const std::string &url)
	{
		core::ScopedLock lock(requestMutex);
		Request &req = _requests[&response];
		if(req._redirectTo.empty()) req._redirectTo = url;
	}
	std::string redirectedUrl(Poco::Net::HTTPServerResponse &response)
	{
		core::ScopedLock lock(requestMutex);
		Request &req = _requests[&response];
		return req._redirectTo;
	}

	const std::string &getCookie(const std::string &key, Poco::Net::HTTPServerResponse &response)
	{
		core::ScopedLock lock(requestMutex);
		Request &req = _requests[&response];
		return req.in.get(key, "");
	}
	void setCookie(const std::string &key, const std::string &val,
		Poco::Net::HTTPServerResponse &response)
	{
		core::ScopedLock lock(requestMutex);
		Request &req = _requests[&response];
		req.in.set(key, val);
		req.out.set(key, val);
	}

	void commitCookies(Poco::Net::HTTPServerResponse &response)
	{
		using namespace Poco::Net;
		core::ScopedLock lock(requestMutex);
		Request &req = _requests[&response];
		for(NameValueCollection::ConstIterator iterator = req.out.begin(); iterator != req.out.end(); ++iterator)
		{
			Poco::Net::HTTPCookie cookie(iterator->first, iterator->second);
			cookie.setMaxAge(-1); cookie.setHttpOnly(true);
			req.response->addCookie(cookie);
		}
		req.out.clear();
	}

	void forceRequestEnd(Poco::Net::HTTPServerResponse &response)
	{
		commitCookies(response);
		core::ScopedLock lock(requestMutex);
		Request &req = _requests[&response];
		req._force = true;
	}

	void lockCookies(Poco::Net::HTTPServerResponse &response)
	{
		using namespace Poco::Net;
		core::ScopedLock lock(requestMutex);
		Request &req = _requests[&response];
		++req._locked;
	}
	void unlockCookies(Poco::Net::HTTPServerResponse &response)
	{
		bool _force = false;
		{
			core::ScopedLock lock(requestMutex);
			Request &req = _requests[&response];
			--req._locked; if(req._locked != 0) return;
			_force = req._force;
		}
		commitCookies(response);
		//if(_force) requestEnd(response);
	}

	void requestBegin(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
	{
		//requestEnd(request);
		core::ScopedLock lock(requestMutex);
		Request &req = _requests[&response];
		req.request = &request;
		req.response = &response;
		request.getCookies(req.in);
		printff("\n\nRequest Started! [%ld]\n", (std::uint64_t)&request);
	}
	void requestEnd(Poco::Net::HTTPServerResponse &response)
	{
		using namespace Poco::Net;
		core::ScopedLock lock(requestMutex);
		_requests.erase(&response);
		printff("Request Ended!\n");
	}

	bool isSessionValid(Session &session, Poco::Net::HTTPServerRequest *request = NULL)
	{
		return (
			session.timeOut() < _server.conf().timeOut() &&
			(!_server.conf().lifeTime() || session.lifeTimeOut() < _server.conf().lifeTime()) &&
			(!request || core::util::Hash::isEqual(session.host(), request->clientAddress().host().toString()))
		);
	}

	Page &page(const std::string &path)
	{
		core::ScopedLock lock(getPageMutex);

		::initPages();
		if(path == "/undefined") return ignorePage();
		if(path.size() > 1 && path[1] == EVENT_SYMBOL) return eventPage();
		PageMap::iterator it = _server._pages.find(path);
		if(it == _server._pages.end()) return notFoundPage();
		return *it->second;
	}

	std::shared_ptr<Session> *changeSessionID(Server &server, Session &session, Poco::Net::HTTPServerRequest &request)
	{
		SessionMap::iterator it = server._sessions.find(session.id());
		if(it == server._sessions.end()) return NULL;

		std::shared_ptr<Session> pointer = it->second;
		server._sessions.erase(pointer->id());
		pointer->genID();
		setCookie("sessionID", pointer->id(), request.response());

		std::shared_ptr<Session> &ref = server._sessions[pointer->id()];
		ref = pointer;
		return &ref;
	}

	std::shared_ptr<Session> &noUserSession(Server &server, Poco::Net::HTTPServerRequest &request)
	{
		std::shared_ptr<Session> *session = NULL, unregUserSession;

		unregUserSession = std::shared_ptr<Session>(server._creator->newSession());
		unregUserSession->host(request.clientAddress().host().toString());
		unregUserSession->user(new model::User());
		Session &currSession = *unregUserSession;
		server._sessions[currSession.id()] = unregUserSession;
		session = &server._sessions[currSession.id()];
		(*session)->_created = Poco::Timestamp();
		(*session)->active();

		server._data->setCookie("sessionID", (*session)->id(), request.response());
		printff("NEW_SESSION: %s\n", (*session)->id().c_str());
		return *session;
	}
};

Server::Server() : _data(new Data(*this))
{
	conf().webInfFolder(appDir() + "/WEB-INF");
	printf("WEB-INF Folder: '%s'\n", conf().webInfFolder().c_str());

	//_creator = std::unique_ptr<CreatorBase>(new CreatorBase);
}
Server::~Server()
{
}

Server &Server::instance()
{
	static Server server;
	return server;
}
void Server::addInit(void (*init)())
{
	::pageInits().push_back(init);
}
void Server::addSqlInit(void (*init)())
{
	::sqlInits().push_back(init);
}
void Server::initSql()
{
	::initSql();
}

void Server::forceCommit(Poco::Net::HTTPServerResponse &response, const std::string &url)
{
	_data->forceRequestEnd(response);
	if(!url.empty()) _data->redirectedUrl(response, url);
}
std::string Server::forcedUrl(Poco::Net::HTTPServerResponse &response)
{
	return _data->redirectedUrl(response);
}

void Server::addPage(Page *page)
{
	core::ScopedLock lock(setPageMutex);

	using namespace Poco::Net;

	class PageShellHandler: public HTTPRequestHandler {
		std::unique_ptr<HTTPRequestHandler> _handle;
	public:
		__inline PageShellHandler(HTTPRequestHandler *handle) : _handle(std::unique_ptr<HTTPRequestHandler>(handle)) {}
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
			server()._data->requestBegin(request, response);
			_handle->handleRequest(request, response);
			server()._data->requestEnd(response);
		}
	};

	class PageShell : public core::Page {
		std::unique_ptr<Page> _page;
	public:
		__inline PageShell(Page *page) : _page(std::unique_ptr<Page>(page)) {}
		Page &self() { return *_page; }
		HTTPRequestHandler *newHandler() { return new PageShellHandler(_page->newHandler()); }
	};

	_pages[page->path()] = std::unique_ptr<Page>(new PageShell(page));
}
Page &Server::page(const std::string &path)
{
	return _data->page(path).self();
}
Page &Server::page(const Poco::Net::HTTPServerRequest &request)
{
	printff("page 01 '%s'\n", Poco::URI(request.getURI()).getPath().c_str());
	return page(Poco::URI(request.getURI()).getPath());
}
Poco::Net::HTTPRequestHandler *Server::newHandler(const std::string &path)
{
	return _data->page(path).newHandler();
}
Poco::Net::HTTPRequestHandler *Server::newHandler(const Poco::Net::HTTPServerRequest &request)
{
	return newHandler(Poco::URI(request.getURI()).getPath());
}

SessionPtr Server::session(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
	class FormHandler: public Poco::Net::PartHandler
	{
		Server &server;
		Poco::Net::HTTPServerRequest &request;
		Poco::Net::HTTPServerResponse &response;
		std::string _csrfID;
		bool _partCalled;

	public:
		std::shared_ptr<Session> session;

	public:
		FormHandler(Server &server, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) :
			server(server), request(request), response(response), session(prepareSession())
		{
			_partCalled = false;
		}

		/// Send stream uploadings and parameters to controller
		void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream)
		{
			if (header.has("Content-Disposition"))
			{
				std::string disp;
				Poco::Net::NameValueCollection params;
				Poco::Net::MessageHeader::splitParameters(header["Content-Disposition"], disp, params);
				_partCalled = true;
				call(header.get("Content-Type", "(unspecified)"), "POST", params, &stream);
			}
		}

		/// Send data to controller events handler
		void call(std::string contentType, std::string method,
			Poco::Net::NameValueCollection &params, std::istream *stream)
		{
			/// Cross-Site Request Forgery (CSRF) validation
			std::string receivedCSRF = params.get("csrfID", "");
			printff("CSRF check [%s] : [%s]!\n", csrfID().c_str(), receivedCSRF.c_str());
			if(!receivedCSRF.empty() && !core::util::Hash::isEqual(csrfID(), receivedCSRF))
				return;

			session->contentType(contentType);
			session->method(method);
			session->request(request);
			session->response(response);

			session->locked(true);
			session->receive(session->event(), params, stream);
			session->locked(false);
		}

		/// Prepare session
		std::shared_ptr<Session> &prepareSession()
		{
			(void)server; (void)request; (void)response;

			std::shared_ptr<Session> *session = NULL;
			{
				core::ScopedLock lock(sessionMutex);

				/// Get sessionID from cookies
				std::string sessionID = server._data->getCookie("sessionID", response);
				printff("sessionID='%s'\n", sessionID.c_str());

				/// If there's no session, create one
				SessionMap::iterator it = server._sessions.find(sessionID);
				if(it == server._sessions.end())
					session = &server._data->noUserSession(server, request);
				else
					session = &it->second;

				/// Generate new sessionID and csrfID periodically
				_csrfID = (*session)->csrfID();
				if((*session)->csrfTimeOut() > server.conf().changeIdTimeOut())
				{
					std::shared_ptr<Session> *updatedSession = server._data->
						changeSessionID(server, *(*session), request);
					session = updatedSession ? updatedSession : session;
					(*session)->genCsrfID();
					printff("Gen Id's [%s] [%s]\n", (*session)->csrfID().c_str(), (*session)->id().c_str());
				}

				/// Check for session expiration and client IP
				if(server._data->isSessionValid(*(*session), &request))
				{
					(*session)->active();
					return *session;
				}
			}

			printff("Session Timeup [%s] [%s]\n", (*session)->csrfID().c_str(), (*session)->id().c_str());

			/// Delete old session and create new instead
			Session::Prop *par = (*session)->saveProp();
			server.logout(*(*session));
			{
				core::ScopedLock lock(sessionMutex);
				std::shared_ptr<Session> &newSession = server._data->noUserSession(server, request);
				newSession->loadProp(par);
				return newSession;
			}
		}

	public:
		__inline void partCalled(bool val) { _partCalled = val; }
		__inline bool partCalled() const { return _partCalled; }

		__inline const std::string &csrfID() const { return _csrfID; }

	};

	/// Make sure, cookies not gonna be sended too early
	_data->lockCookies(response);

	FormHandler handler(*this, request, response);
	if(!handler.session->locked())
	{
		printff("ip: '%s' : '%s'\n", request.clientAddress().host().toString().c_str(), request.getVersion().c_str());

		/// Prepare URI, path and event
		Poco::URI uri(request.getURI());
		std::string path = uri.getPath();
		handler.session->event("");

		/// Check for action event and parse path history
		if(path.size() > 1 && path[1] == EVENT_SYMBOL) {
			handler.session->event(path.c_str() + 2);
			handler.session->path(handler.session->page().path(), handler.session->pathParams());
		}
		else {
			handler.session->page(this->page(path));
			handler.session->path(handler.session->page().path(), uri.getPathEtc().c_str() + path.size());
		}

		printff("event 01 '%s'; '%s'\n", path.c_str(), handler.session->event().c_str());

		/// If there's no stream uploadings then send form parameters to controller
		Poco::Net::HTMLForm form(request, request.stream(), handler);
		if(form.size() || !handler.partCalled()) handler.call(request.getContentType(), request.getMethod(), form, NULL);
	}

	/// Make sure, cookies not gonna be sended too early
	_data->unlockCookies(response);

	return handler.session;
}

Session &Server::login(Poco::Net::HTTPServerRequest &request,
	const std::string &username, const std::string &password)
{
	Poco::Net::HTTPServerResponse &response = request.response();

	/// Cancel if someone logged in already
	SessionPtr oldSessionPtr = this->session(request, response);
	Session &oldSession = *oldSessionPtr;
	if(oldSession) return oldSession;

	Session::Prop *par = oldSession.saveProp();

	SessionPtr session;
	{
		core::ScopedLock lock(sessionMutex);

		/// Prepare new session and retrieve user data from db
		session = std::unique_ptr<Session>(_creator->newSession());
		model::User &user = *new model::User();
		session->loadProp(par);
		session->host(request.clientAddress().host().toString());
		session->_created = Poco::Timestamp();
		session->user(&user);
		sql().getUserByUsername(user, username);

		/// Purge abandoned sessions, checking by userID
		auto it = _data->_users.find(user.id());
		if(it != _data->_users.end() && !_data->isSessionValid(*it->second, NULL))
			logout(*it->second);

		printff("REG: '%s'=%s\n", user.username().c_str(), (_data->_users.find(user.id()) != _data->_users.end()) ? "true" : "false");

		/// Checking if user not logged in and allowed to be logged in
		if(	!user													||
			user.group() == user.SUBSCRIBER							||
			_data->_users.find(user.id()) != _data->_users.end()	)
			return oldSession;

		/// User password validation
		std::string salt = user.password().c_str() + 64;
		std::string hash = core::util::Hash::hash(password + salt);
		if(!core::util::Hash::isEqual(user.password(), hash + salt))
			return oldSession;
	}

	logout(oldSession);

	/// Register new session
	{
		core::ScopedLock lock(sessionMutex);

		Session &currSession = *session;
		_data->_users[session->user().id()] = session;
		_sessions[currSession.id()] = session;
		currSession.active();

		_data->setCookie("sessionID", currSession.id(), response);

		return currSession;
	}
}

bool Server::logout(Session &session)
{
	core::ScopedLock lock(sessionMutex);

	/// Purge session from session map and user map
	_data->_users.erase(session.user().id());
	return _sessions.erase(session.id());
}

Config &Server::conf()
{
	return _config;
}
db::Sql &Server::sql()
{
	if(!_sql) _sql = std::unique_ptr<db::Sql>(_creator->newSql());
	return *_sql;
}

void Server::EventHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	server()._data->requestBegin(request, response);
	handle(request, response);
	server()._data->requestEnd(response);
}

Server &core::server()
{
	initUPnP();
	return Server::instance();
}