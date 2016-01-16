#ifndef CORE_SERVER_H
#define CORE_SERVER_H


#include <core/Header.h>
#include <core/Util.h>
#include <model/User.h>
#include <core/db/Sql.h>


namespace core
{
	class Page;
	class Session;
	class Server;

	void initUPnP();
	Server &server();

	struct CreatorBase { virtual ~CreatorBase() {}
		virtual Session *newSession() const;
		virtual db::Sql *newSql() const;
	};
	template<typename SessionType=Session, typename SqlType=db::Sql>
		struct Creator : public CreatorBase {
			Session *newSession() const { return new SessionType; }
			db::Sql *newSql() const { return new SqlType; }
		};

	typedef std::shared_ptr<Session> SessionPtr;

	class Config
	{
	public:
		struct Emoticon
		{
			std::string name, src;
			__inline Emoticon(std::string name, std::string src) : name(name), src(src) {}
		};

	private:
		core::Vector<Emoticon> _emoticons;

		bool _https;
		std::string _name;
		std::string _url;
		std::uint16_t _port;
		std::uint16_t _portUPnP;
		std::uint32_t _timeOut;
		std::uint32_t _lifeTime;
		std::uint32_t _changeIdTimeOut;
		std::uint32_t _activationTimeOut;
		std::string _webInfFolder;
		std::string _defaultPage;
		std::string _dateFormat;
		std::int32_t _dateTimeZone;

		std::string _sqlConnector;
		std::string _sqlConnectionString;
		std::int32_t _sqlMinSessions;
		std::int32_t _sqlMaxSessions;
		std::int32_t _sqlIdleTime;

		std::string _smtpHost;
		std::uint16_t _smtpPort;
		std::string _smtpUsername;
		std::string _smtpPassword;

	public:
		Config();
		~Config();

	public:
		void emoticon(const std::string &name, const std::string &src);
		__inline core::Vector<Emoticon> emoticons() { return _emoticons; }

	public:
		__inline void https(bool val) { _https = val; }
		__inline bool https() const { return _https; }

		__inline void name(const std::string &val) { _name = val; }
		__inline const std::string &name() const { return _name; }

		__inline void url(const std::string &val) { _url = val; }
		__inline const std::string &url() const { return _url; }

		__inline void port(std::uint16_t val) { _port = val; }
		__inline std::uint16_t port() const { return _port; }

		__inline void portUPnP(std::uint16_t val) { _portUPnP = val; }
		__inline std::uint16_t portUPnP() const { return _portUPnP; }

		__inline void timeOut(std::uint32_t val) { _timeOut = val; }
		__inline std::uint32_t timeOut() const { return _timeOut; }

		__inline void lifeTime(std::uint32_t val) { _lifeTime = val; }
		__inline std::uint32_t lifeTime() const { return _lifeTime; }
		
		__inline void changeIdTimeOut(std::uint32_t val) { _changeIdTimeOut = val; }
		__inline std::uint32_t changeIdTimeOut() const { return _changeIdTimeOut; }

		__inline void activationTimeOut(std::uint32_t val) { _activationTimeOut = val; }
		__inline std::uint32_t activationTimeOut() const { return _activationTimeOut; }

		__inline void webInfFolder(const std::string &val) { _webInfFolder = val; }
		__inline const std::string &webInfFolder() const { return _webInfFolder; }

		__inline void defaultPage(const std::string &val) { _defaultPage = val; }
		__inline const std::string &defaultPage() const { return _defaultPage; }

		__inline void dateFormat(const std::string &val) { _dateFormat = val; }
		__inline const std::string &dateFormat() const { return _dateFormat; }

		__inline void dateTimeZone(std::int32_t val) { _dateTimeZone = val; }
		__inline std::int32_t dateTimeZone() const { return _dateTimeZone; }

		__inline void sqlConnector(const std::string &val) { _sqlConnector = val; }
		__inline const std::string &sqlConnector() const { return _sqlConnector; }

		__inline void sqlConnectionString(const std::string &val) { _sqlConnectionString = val; }
		__inline const std::string &sqlConnectionString() const { return _sqlConnectionString; }

		__inline void sqlMinSessions(std::int32_t val) { _sqlMinSessions = val; }
		__inline std::int32_t sqlMinSessions() const { return _sqlMinSessions; }

		__inline void sqlMaxSessions(std::int32_t val) { _sqlMaxSessions = val; }
		__inline std::int32_t sqlMaxSessions() const { return _sqlMaxSessions; }

		__inline void sqlIdleTime(std::int32_t val) { _sqlIdleTime = val; }
		__inline std::int32_t sqlIdleTime() const { return _sqlIdleTime; }

		__inline void smtpHost(const std::string &val) { _smtpHost = val; }
		__inline const std::string &smtpHost() const { return _smtpHost; }

		__inline void smtpPort(std::uint16_t val) { _smtpPort = val; }
		__inline std::uint16_t smtpPort() const { return _smtpPort; }

		__inline void smtpUsername(const std::string &val) { _smtpUsername = val; }
		__inline const std::string &smtpUsername() const { return _smtpUsername; }

		__inline void smtpPassword(const std::string &val) { _smtpPassword = val; }
		__inline const std::string &smtpPassword() const { return _smtpPassword; }

	};

	class Server
	{
	public:
		class EventHandler;

	private:
		typedef std::map<std::string, std::unique_ptr<Page> > PageMap;
		typedef std::map<std::string, SessionPtr > SessionMap;

		Config _config;
		std::unique_ptr<db::Sql> _sql;
		PageMap _pages;
		SessionMap _sessions;

		std::unique_ptr<CreatorBase> _creator;

		struct Data;
		std::unique_ptr<Data> _data;

	private:
		Server();
		~Server();

	public:
		static Server &instance();
		void forceCommit(Poco::Net::HTTPServerResponse &response, const std::string &url);
		std::string forcedUrl(Poco::Net::HTTPServerResponse &response);

	public:
		static void addInit(void (*init)());
		static void addSqlInit(void (*init)());
		static void initSql();

	public:
		void addPage(Page *page);
		Page &page(const std::string &path);
		Page &page(const Poco::Net::HTTPServerRequest &request);
		Poco::Net::HTTPRequestHandler *newHandler(const std::string &path);
		Poco::Net::HTTPRequestHandler *newHandler(const Poco::Net::HTTPServerRequest &request);

	public:
		SessionPtr session(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
		Session &login(Poco::Net::HTTPServerRequest &request, const std::string &username, const std::string &password);
		bool logout(Session &session);

	public:
		Config &conf();
		db::Sql &sql();

		__inline void creator(CreatorBase *val) { _creator = std::unique_ptr<CreatorBase>(val); }
		__inline const CreatorBase &creator() const { return *_creator; }

	};
}


#endif // CORE_SERVER_H
