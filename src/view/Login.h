#ifndef Login_INCLUDED
#define Login_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class LoginHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // Login_INCLUDED
