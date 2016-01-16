
/*#include "Poco/URI.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"*/

#include <core/Header.h>


using namespace core;
using namespace model;


User::User()
{
	_id = 0;
	_group = INACTIVE;
	_birthday = Poco::DateTime(Poco::Timestamp(0));
}
User::~User()
{
}

User::operator bool() const
{
	return registered() && group() != INACTIVE;
}