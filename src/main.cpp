

#include "Poco/URI.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/SecureStreamSocket.h"
#include "Poco/Net/SecureServerSocket.h"
#include "Poco/Net/HTTPServerRequestImpl.h"
#include "Poco/Net/X509Certificate.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadPool.h"

#include "ctrl/Controller.h"
#include "model/Service.h"


using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Net::SecureStreamSocket;
using Poco::Net::SecureServerSocket;
using Poco::Net::HTTPServerRequestImpl;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;


//cpspc "$(FileFullPath)";cp dummy.o $(IntermediateDirectory)/$(ObjectName)$(ObjectSuffix)


class LocalHostTest : public Poco::Runnable { public:
	void run() {
		system((std::string("sleep 0.5; firefox ") +
			(core::server().conf().https() ? "https" : "http") + "://localhost:" +
				std::to_string(core::server().conf().port())).c_str());
	}
};


class WebServerHandlerFactory: public HTTPRequestHandlerFactory
{
public:
	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		return core::server().newHandler(request);
	}
};


class HTTPWebServerApp: public Poco::Util::ServerApplication
{
	bool _helpRequested;

public:
	HTTPWebServerApp(): _helpRequested(false)
	{
		Poco::Net::initializeSSL();
	}

	~HTTPWebServerApp()
	{
		Poco::Net::uninitializeSSL();
	}

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);
		
		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value)
	{
		ServerApplication::handleOption(name, value);

		if(name == "help")
			_helpRequested = true;
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A Web server.");
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args)
	{
		if(_helpRequested)
		{
			displayHelp();
		}
		else
		{
			/// get parameters from configuration file
			core::server().conf().name(config().getRawString("HTTPWebServer.name", core::server().conf().name()));
			core::server().conf().url(config().getRawString("HTTPWebServer.url", core::server().conf().url()));
			core::server().conf().portUPnP((std::uint16_t)config().getInt("HTTPWebServer.portUPnP", core::server().conf().portUPnP()));
			core::server().conf().port((std::uint16_t)config().getInt("HTTPWebServer.port", core::server().conf().port()));
			core::server().conf().timeOut(config().getInt("HTTPWebServer.timeOut", core::server().conf().timeOut()));
			core::server().conf().lifeTime(config().getInt("HTTPWebServer.lifeTime", core::server().conf().lifeTime()));
			core::server().conf().changeIdTimeOut(config().getInt("HTTPWebServer.changeIdTimeOut", core::server().conf().changeIdTimeOut()));
			core::server().conf().activationTimeOut(config().getInt("HTTPWebServer.activationTimeOut", core::server().conf().activationTimeOut()));
			core::server().conf().https(config().getBool("HTTPWebServer.https", core::server().conf().https()));
			core::server().conf().defaultPage(config().getRawString("HTTPWebServer.defaultPage", core::server().conf().defaultPage()));
			core::server().conf().dateFormat(config().getRawString("HTTPWebServer.dateFormat", core::server().conf().dateFormat()));
			core::server().conf().dateTimeZone((std::int32_t)config().getInt("HTTPWebServer.dateTimeZone", core::server().conf().dateTimeZone()));

			/// Sql database connection
			core::server().conf().sqlConnector(config().getRawString("HTTPWebServer.sql.connector", core::server().conf().sqlConnector()));
			core::server().conf().sqlConnectionString(config().getRawString("HTTPWebServer.sql.connectionString", core::server().conf().sqlConnectionString()));
			core::server().conf().sqlMinSessions((std::int32_t)config().getInt("HTTPWebServer.sql.minSessions", core::server().conf().sqlMinSessions()));
			core::server().conf().sqlMaxSessions((std::int32_t)config().getInt("HTTPWebServer.sql.maxSessions", core::server().conf().sqlMaxSessions()));
			core::server().conf().sqlIdleTime((std::int32_t)config().getInt("HTTPWebServer.sql.idleTime", core::server().conf().sqlIdleTime()));

			printff("sqlConnector='%s'\n", core::server().conf().sqlConnector().c_str());
			printff("sqlConnectionString='%s'\n", core::server().conf().sqlConnectionString().c_str());

			/// get mail parameters for user verification emails
			core::server().conf().smtpHost(config().getRawString("HTTPWebServer.smtp.host", core::server().conf().smtpHost()));
			core::server().conf().smtpPort((std::uint16_t)config().getInt("HTTPWebServer.smtp.port", core::server().conf().smtpPort()));
			core::server().conf().smtpUsername(config().getRawString("HTTPWebServer.smtp.username", core::server().conf().smtpUsername()));
			core::server().conf().smtpPassword(config().getRawString("HTTPWebServer.smtp.password", core::server().conf().smtpPassword()));

			/// emoticons
			std::uint32_t emoticonIndex = 1;
			for(std::string val; !(val=config().getRawString("HTTPWebServer.emoticon" +
					std::to_string(emoticonIndex), "")).empty(); ++emoticonIndex)
			{
				const char *name = val.c_str(), *comma = strstr(name, ","), *src = comma + 1;
				if(comma) core::server().conf().emoticon(std::string(name, comma - name), src);
			}

			/// define controller and service classes
			core::server().creator(new core::Creator<ctrl::Controller, model::Service>());

			/// this code tries to open default page in firefox
			LocalHostTest localHostTest;
			Poco::ThreadPool threadpool;
			if(config().getBool("HTTPWebServer.testLocalhost", false))
				threadpool.start(localHostTest);

			/// set-up a server socket
			std::unique_ptr<ServerSocket> svs(std::unique_ptr<ServerSocket>(core::server().conf().https() ?
				new SecureServerSocket(core::server().conf().port()) : new ServerSocket(core::server().conf().port()) ));
			/// set-up a HTTPServer instance
			HTTPServer srv(new WebServerHandlerFactory, *svs, new HTTPServerParams);
			/// start the HTTPServer
			srv.start();
			/// wait for CTRL-C or kill
			waitForTerminationRequest();
			/// Stop the HTTPServer
			srv.stop();
		}
		return Application::EXIT_OK;
	}
};


int main(int argc, char** argv)
{
	HTTPWebServerApp app;
	return app.run(argc, argv);
}
