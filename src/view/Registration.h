#ifndef Registration_INCLUDED
#define Registration_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class RegistrationHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // Registration_INCLUDED
