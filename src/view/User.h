#ifndef User_INCLUDED
#define User_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class UserHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // User_INCLUDED
