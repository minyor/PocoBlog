
/*#include "Poco/URI.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"*/

#include <model/Blog.h>
#include <model/Post.h>
#include <core/Server.h>


using namespace core;
using namespace model;


Blog::Blog()
{
	_id = 0;
	_category_id = 0;
	_post_id = 0;
}
Blog::~Blog()
{
}

/*void Blog::post(Post *val)
{
	_post = std::shared_ptr<Post>(val);
}*/