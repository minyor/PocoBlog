#ifndef Download_INCLUDED
#define Download_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class DownloadHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // Download_INCLUDED
