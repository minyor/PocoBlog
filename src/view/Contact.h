#ifndef Contact_INCLUDED
#define Contact_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class ContactHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // Contact_INCLUDED
