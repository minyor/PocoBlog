
/*#include "Poco/URI.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"*/

#include <model/Rating.h>
#include <core/Server.h>


using namespace core;
using namespace model;


Rating::Rating()
{
	_id = 0;
	_post_id = 0;
	_user_id = 0;

}
Rating::~Rating()
{
}