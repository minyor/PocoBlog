
#include "Poco/URI.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"

#include <core/Header.h>
#include <core/Server.h>
#include <core/Page.h>


using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Util::ServerApplication;
using namespace core;


class NotFoundRequestHandler: public Poco::Net::HTTPRequestHandler
{

public:
	NotFoundRequestHandler() 
	{
	}

	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
	{
		/// Check for default page
		Poco::URI uri(request.getURI());
		std::string path = uri.getPath();
		if(path.size() < 2 && server().conf().defaultPage().size() > 1)
			return response.redirect(server().conf().defaultPage());

		/// Check for resources
		std::fstream file(server().conf().webInfFolder() + path, std::fstream::in|std::fstream::binary);
		if(file.is_open())
		{
			response.send() << file.rdbuf();
			file.close();
			return;
		}

		/// Do standard 'Not Found' message
		response.setChunkedTransferEncoding(true);
		response.setContentType("text/html");
		std::ostream& ostr = response.send();
		ostr <<
			"<html>\n"
			"<head>\n"
			"<title>Not Found Page</title>\n"
			"</head>\n"
			"<body>\n"
			"<h1>Error 404: Not Found</h1>\n"
			"</body>\n";
	}
};


Page::Page()
{
	_newClass = NULL;
	_path = "/";
}
Page::~Page()
{
}

Poco::Net::HTTPRequestHandler *Page::newHandler()
{
	return new NotFoundRequestHandler;
}