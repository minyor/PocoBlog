
/*#include "Poco/URI.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"*/

#include <model/Post.h>
#include <core/Server.h>


using namespace core;
using namespace model;


Post::Post()
{
	_viewLevel = 1;
	_rating = 0;
	_rated = false;

	_id = 0;
	_parent_id = Poco::NULL_GENERIC;
	_blog_id = 0;
	_user_id = 0;
}
Post::~Post()
{
}