#ifndef CORE_SESSION_H
#define CORE_SESSION_H


#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Timestamp.h"

#include <core/Header.h>
#include <core/Server.h>


#define addEvent(_name) add(#_name, &__hide_type_unref<decltype(*this)>::Type::_name);


namespace core
{
	class Form;
	class HTTPCustomResponse;

	class MenuEntry { public:
		std::string title, url;
		__inline MenuEntry(std::string title, std::string url) : title(title), url(url) {}
	};

	class Session
	{
		typedef void (Session::*Callback)(core::Form &form, std::istream *stream);
		typedef std::map<std::string, Callback> EventMap;
		typedef std::map<std::string, std::unique_ptr<Form> > FormMap;
		friend class Server;

		struct Prop;

		std::string _id;
		std::string _csrfID;
		Page *_page;
		std::unique_ptr<model::User> _user;
		Poco::Timestamp _lastActive;
		Poco::Timestamp _created;
		Poco::Timestamp _lastCsrfGen;
		std::string _path;
		std::string _lastPath;
		std::string _prevPath;
		std::string _pathParams;
		std::string _host;
		std::string _event;

		Poco::Net::HTTPServerRequest *_request;
		Poco::Net::HTTPServerResponse *_response;
		std::string _contentType;
		std::string _method;

		EventMap _events;
		FormMap _forms;
		bool _locked;

	private:
		void genID();
		void genCsrfID();
		Prop *saveProp();
		void loadProp(Prop *par);
		void path(const std::string &pathVal, const std::string &paramsVal);
		void receive(std::string event, Poco::Net::NameValueCollection &params, std::istream *stream);

		__inline void request(Poco::Net::HTTPServerRequest &val) { _request = &val; }
		__inline void response(Poco::Net::HTTPServerResponse &val) { _response = &val; }

	public:
		core::Vector<MenuEntry> menuList;
		core::Vector<MenuEntry> sidebarList;

	public:
		Session();
		virtual ~Session();

	public:
		operator bool () const;

	public:
		Form &form();
		void update();
		void reidentify();
		void redirect(const std::string &uri);
		std::ostream &send();
		void comeback();

	public:
		void call(const std::string &event, core::Form &form, std::istream *stream);
		void add(const std::string &event, Callback callback);
		template<typename T> void add(const std::string &event, void (T::*callback)(core::Form &form, std::istream *stream)) {
			add(event, (Callback)callback);
		}

	public:
		virtual void onEnter(core::Form &form);
		virtual void onLeave(core::Form &form);
		virtual void onLoad(core::Form &form);
		virtual void onAction(const std::string &event, core::Form &form, std::istream *stream);

	public:
		__inline const std::string &id() const { return _id; }
		__inline const std::string &csrfID() const { return _csrfID; }

		__inline void page(Page &val) { _page = &val; }
		__inline Page &page() const { return *_page; }

		__inline void user(model::User *val) { _user = std::unique_ptr<model::User>(val); }
		__inline const model::User &user() const { return *_user; }

		__inline void active() { _lastActive = Poco::Timestamp(); }
		__inline std::uint32_t timeOut() const { return _lastActive.elapsed() / 60000000; }
		__inline std::uint32_t lifeTimeOut() const { return _created.elapsed() / 60000000; }
		__inline std::uint32_t csrfTimeOut() const { return _lastCsrfGen.elapsed() / 60000000; }

		std::string url() const;
		const std::string &path() const;
		__inline const std::string &lastPath() const { return _lastPath; }
		__inline const std::string &prevPath() const { return _prevPath; }
		__inline const std::string &pathParams() const { return _pathParams; }

		__inline void host(const std::string &val) { _host = val; }
		__inline const std::string &host() const { return _host; }

		__inline void event(const std::string &val) { _event = val; }
		__inline const std::string &event() const { return _event; }

		__inline Poco::Net::HTTPServerRequest &request() { return *_request; }
		__inline HTTPCustomResponse &response() { return (HTTPCustomResponse &)*_response; }

		__inline void contentType(const std::string &val) { _contentType = val; }
		__inline const std::string &contentType() const { return _contentType; }

		__inline void method(const std::string &val) { _method = val; }
		__inline const std::string &method() const { return _method; }

		__inline void locked(bool val) { _locked = val; }
		__inline bool locked() const { return _locked; }

		__inline db::Sql &service() const { return core::server().sql(); }

	};

	typedef std::stringstream TemplateStream;
	typedef std::map<std::string, std::shared_ptr<TemplateStream> > TemplateMap;

	class Form
	{
		typedef void (Form::*Callback)(std::istream *stream);
		typedef std::map<std::string, Callback> EventMap;

		bool _enteredAfterCreation;
		Session *_session;
		EventMap _events;

	public:
		std::map<std::string, std::string> val;
		core::Vector<MenuEntry> menuList;
		core::Vector<MenuEntry> sidebarList;

		__inline core::Vector<MenuEntry> &menu() { return menuList ? menuList : ctrl().menuList; }
		__inline core::Vector<MenuEntry> &sidebar() { return sidebarList ? sidebarList : ctrl().sidebarList; }

	public:
		Form();
		virtual ~Form();

	public:
		bool checkPath(const std::string &url) const;
		__inline std::string &operator[] (const std::string &key) { return val[key]; }

	public:
		void call(const std::string &event, std::istream *stream);
		void add(const std::string &event, Callback callback);
		template<typename T> void add(const std::string &event, void (T::*callback)(std::istream *stream)) {
			add(event, (Callback)callback);
		}

	public:
		void htmlTemplate(const std::string &path, const std::string &source, TemplateMap &map, std::ostream &responseStream);
		void htmlInstance(const std::string &name, const std::string &source, TemplateMap &map, std::ostream &responseStream);
		std::string htmlTagPar(const std::string &name);
		std::string htmlCSRF();

	public:
		virtual void onEnter();
		virtual void onLeave();
		virtual void onLoad();

	public:
		__inline void enteredAfterCreation(bool val) { _enteredAfterCreation = val; }
		__inline bool enteredAfterCreation() const { return _enteredAfterCreation; }

		__inline void session(Session &val) { _session = &val; }
		__inline Session &session() const { return *_session; }

		__inline Page &page() const { return session().page(); }
		const std::string &path() const;

		__inline const model::User &user() const { return session().user(); }
		__inline Session &ctrl() const { return session(); }

	};

	class HTTPCustomResponse : public Poco::Net::HTTPServerResponse
	{
	public:
		void redirect(const std::string &uri, HTTPStatus status = HTTP_FOUND, int unused=0);
		void requireAuthentication(const std::string &realm, int unused=0);
		std::ostream &send(int unused=0);
		void sendBuffer(const void *pBuffer, std::size_t length, int unused=0);
		void sendContinue(int unused=0);
		void sendFile(const std::string &path, const std::string &mediaType, int unused=0);

	};
}


#endif // CORE_SESSION_H
