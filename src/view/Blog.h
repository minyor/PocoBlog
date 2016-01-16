#ifndef Blog_INCLUDED
#define Blog_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class BlogHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // Blog_INCLUDED
