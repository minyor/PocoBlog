#ifndef Documentation_INCLUDED
#define Documentation_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class DocumentationHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // Documentation_INCLUDED
