#ifndef Index_INCLUDED
#define Index_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class IndexHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // Index_INCLUDED
