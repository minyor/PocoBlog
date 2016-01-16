
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"

#include <ctrl/form/Blog.h>


using namespace ctrl::form;


Blog::Blog()
{
	oldCategoryID = oldBlogID = 0;
	editPostID = 0;
	sort = 1;

	sortModes.add("Top Rated", "0");
	sortModes.add("Newest", "1");
	sortModes.add("Oldest", "-1");

	addEvent(newCategory);
	addEvent(newBlog);
	addEvent(newPost);
	addEvent(editBlog);
	addEvent(editPost);
	addEvent(getContent);
	addEvent(removeCategory);
	addEvent(removeBlog);
	addEvent(removePost);
	addEvent(ratePost);
	addEvent(paginate);
}
Blog::~Blog()
{
}

std::string Blog::format(const std::string &in, bool paragraphs)
{
	return core::util::Html::format(in, paragraphs);
}
Blog::Mode Blog::mode()
{
	if(hasSearchResults)
		return MODE_SEARCH;
	else if(blog.id())
		return MODE_BLOG;
	else
		return MODE_CATEGORY;
}
std::string Blog::param()
{
	std::string ret;
	switch(mode())
	{
	case MODE_SEARCH: ret += "q=" + searchQuery + "&"; break;
	case MODE_BLOG: ret += "b=" + std::to_string(blog.id()) + "&"; break;
	case MODE_CATEGORY: ret += "c=" + std::to_string(category.id()) + "&"; break;
	}

	ret += "p=" + std::to_string(paginator.page()) + "&";
	ret += "s=" + std::to_string(sort) + "&";

	return ret;
}

void Blog::onEnter()
{
	val["status"] = "";
}

void Blog::onLoad()
{
	oldCategoryID = category.id();
	oldBlogID = blog.id() ? blog.id() : oldBlogID;
	category.id(0);
	blog.id(0);
	categories = NULL;
	blogs = NULL;

	/// Parameters
	core::DataID categoryID = 0; std::istringstream(val["c"]) >> categoryID;
	core::DataID blogID = 0; std::istringstream(val["b"]) >> blogID;
	std::int32_t sort = 1; std::istringstream(val["s"]) >> sort;
	std::int32_t page = INTMAX(32); std::istringstream(val["p"]) >> page;
	auto &query = val["q"];

	sortModes.selected = core::to_string(this->sort = sort);
	if(page != INTMAX(32)) paginator.page(page);

	/// Retvieve current category
	ctrl().service().getCategory(category, categoryID);

	/// Mode
	switch(0)
	{ default:

		/// Prepare Search Results table
		hasSearchResults = !query.empty();
		if(hasSearchResults)
		{
			searchQuery = query;
			paginator.reset();
			paginator.doExtending(searchResults.count());
			searchResults = ctrl().service().searchBlogs(searchQuery, sort, paginator.limit(), paginator.offset());
			paginator.doExtending(searchResults.count());
			break;
		}

		/// Prepare Blog and Posts
		ctrl().service().getBlog(blog, blogID, user().id());
		if(blog.id())
		{
			categoryID = blog.categoryId();
			if(oldBlogID && oldBlogID != blog.id()) paginator.reset();
			paginator.doExtending(posts.count());
			posts = ctrl().service().getPostsByBlog(blog.id(), user().id(), sort, paginator.limit(), paginator.offset());
			paginator.doExtending(posts.count());
			break;
		}

		/// Prepare Category and Blog tables
		hasCategories = ctrl().service().getCategoriesCount(categoryID);
		hasBlogs = ctrl().service().getBlogsCountByCategory(categoryID);
		if(oldCategoryID != category.id()) paginator.reset();
		if(hasCategories) {
			paginator.doPaging(hasCategories);
			categories = ctrl().service().getCategories(categoryID, sort, paginator.limit(), paginator.offset());
		}
		if(hasBlogs) {
			paginator.doPaging(hasBlogs);
			blogs = ctrl().service().getBlogsByCategory(categoryID, sort, paginator.limit(), paginator.offset());
		}

		/// Forbids to create blogs inside root category
		hasCategories = !categoryID ? uint64_t(1) : hasCategories;
	}

	/// Prepare Category chain
	categoryChain = ctrl().service().getCategoryChain(categoryID);

	/// Reset parameters
	val["c"] = val["b"] = val["p"] = val["s"] = val["p"] = val["q"] = "";
}

void Blog::newCategory(std::istream *stream)
{
	if(!user() || user().group() != user().ADMIN) return;

	/// Parameters
	auto &title = val["title"];

	val["status"] = "";
	if(hasBlogs) return;

	/// Validation
	if(title.empty()) val["status"] = "Please enter Category title";

	if(!val["status"].empty()) return;

	model::Category category;
	category.parentId(this->category.id());
	category.title(title);
	if(!ctrl().service().createCategory(category))
		val["status"] = "Can't create new category";

	/// Reset parameters
	val.erase("title");
}

void Blog::newBlog(std::istream *stream)
{
	if(!user() || user().group() != user().ADMIN) return;

	/// Parameters
	auto &title = val["title"];
	auto &content = val["content"];

	val["status"] = "";
	if(hasCategories) return;

	/// Validation
	if(title.empty()) val["status"] = "Please enter Blog title";

	if(!val["status"].empty()) return;

	/// Blog creation
	model::Blog blog;
	blog.categoryId(this->category.id());
	blog.title(title);
	blog.post().userId(user().id());
	blog.post().content(content);
	if(!ctrl().service().createBlog(blog))
		val["status"] = "Can't create new blog";

	/// Reset parameters
	val.erase("title");
	val.erase("content");
}

void Blog::newPost(std::istream *stream)
{
	if(!blog.id()) return;

	/// Parameters
	core::DataID parentPostID = 0; std::istringstream(val["pp"]) >> parentPostID; val["pp"] = "";
	auto &email = val["email"];
	auto &content = val["content"];

	model::User userCheckEmail, newUser;
	if(!user()) {
		ctrl().service().getUserByEmail(userCheckEmail, email);
	}

	model::User *subscriber = userCheckEmail.group() == model::User::SUBSCRIBER ? &userCheckEmail : NULL;

	val["status"] = "";

	/// Validation
	if(!user() && !subscriber) {
		if(userCheckEmail.registered())
			val["status"] = "*Sorry, that email is registered!";
		if(!core::util::Email::valid(email))
			val["status"] = "*Incorrect email format!";
		if(email.empty())
			val["status"] = "*Please enter email address!";
	}

	if(!val["status"].empty()) return;

	/// Subscribe as Anonymous
	if(!user() && !subscriber) {
		newUser.group(newUser.SUBSCRIBER);
		newUser.username("Anonymous");
		newUser.email(email);
		ctrl().service().createUser(newUser);
		subscriber = &newUser;
		printff("New subscriber: '%s'\n", email.c_str());
	}

	const model::User *currUser = user() ? &user() : subscriber;
	if(!currUser || !*currUser) return;

	/// Add Comment
	model::Post post;
	post.parentId(parentPostID);
	post.blogId(blog.id());
	post.userId(currUser->id());
	post.content(content);
	if(!ctrl().service().createPost(post))
		val["status"] = "Can't create new post";

	/// Reset parameters
	val.erase("content");
}
void Blog::editBlog(std::istream *stream)
{
	if(!blog.id()) return;

	/// Parameters
	core::DataID blogID = 0; std::istringstream(val["b"]) >> blogID; val["b"] = "";
	auto &title = val["title"];
	auto &content = val["content"];

	val["status"] = "";

	/// Validation

	if(!val["status"].empty()) return;

	model::Blog blog; ctrl().service().getBlog(blog, blogID, user().id());
	if(!blog.id() || user().group() != user().ADMIN)
		return;

	blog.title(title);
	if(!ctrl().service().updateBlog(blog))
		val["status"] = "Can't update blog";

	model::Post post; ctrl().service().getPost(post, blog.post().id());
	post.content(content);
	if(!ctrl().service().updatePost(post))
		val["status"] = "Can't update post";

	/// Reset parameters
	val.erase("title");
	val.erase("content");
}
void Blog::editPost(std::istream *stream)
{
	if(!blog.id()) return;

	/// Parameters
	core::DataID postID = 0; std::istringstream(val["p"]) >> postID; val["p"] = "";
	auto &content = val["content"];

	val["status"] = "";

	/// Validation

	if(!val["status"].empty()) return;

	model::Post post; ctrl().service().getPost(post, postID);
	if(!post.id() || (post.user().id() != user().id() && user().group() != user().ADMIN))
		return;

	post.content(content);
	if(!ctrl().service().updatePost(post))
		val["status"] = "Can't update post";

	/// Reset parameters
	val.erase("content");
}
void Blog::getContent(std::istream *stream)
{
	/// Parameters
	core::DataID blogID = 0; std::istringstream(val["b"]) >> blogID; val["b"] = "";
	core::DataID postID = 0; std::istringstream(val["p"]) >> postID; val["p"] = "";

	if(blogID) {
		model::Blog blog; ctrl().service().getBlog(blog, blogID, user().id());
		ctrl().send() << blog.title();
		return;
	}
	if(postID) {
		model::Post post; ctrl().service().getPost(post, postID);
		ctrl().send() << post.content();
		return;
	}
	ctrl().send() << "None";
}

void Blog::removeCategory(std::istream *stream)
{
	if(!user()) return;

	/// Parameters
	core::DataID categoryID = 0; std::istringstream(val["c"]) >> categoryID;
	val["c"] = "";

	/// Remove Category
	model::Category cat;
	ctrl().service().getCategory(cat, categoryID);
	if(!cat.id() || user().group() != user().ADMIN)
		return;

	if(categoryID) ctrl().service().deleteCategory(categoryID);
}

void Blog::removeBlog(std::istream *stream)
{
	if(!user()) return;

	/// Parameters
	core::DataID blogID = 0; std::istringstream(val["b"]) >> blogID;
	val["b"] = "";

	/// Remove Blog
	model::Blog blog;
	ctrl().service().getBlog(blog, blogID, user().id());
	if(!blog.id() || user().group() != user().ADMIN)
		return;

	if(blogID) ctrl().service().deleteBlog(blogID);
	this->blog.id(0);
	ctrl().redirect(path() + "?" + param());
}

void Blog::removePost(std::istream *stream)
{
	if(!user()) return;

	/// Parameters
	core::DataID postID = 0; std::istringstream(val["p"]) >> postID;
	val["p"] = "";

	/// Remove Post
	model::Post post;
	ctrl().service().getPost(post, postID);
	if(!post.id() || (post.user().id() != user().id() && user().group() != user().ADMIN))
		return;

	if(postID) ctrl().service().deletePost(postID);
}

void Blog::ratePost(std::istream *stream)
{
	if(!user()) return;

	/// Parameters
	core::DataID postID = 0; std::istringstream(val["p"]) >> postID;
	val["p"] = "";

	model::Post post;
	ctrl().service().getPost(post, postID);
	if(post.id())
	{
		model::Rating rating;
		ctrl().service().getRatingByPostAndUser(rating, post.id(), user().id());
		if(rating.id())
			ctrl().service().deleteRating(rating.id());
		else
		{
			rating.postId(post.id());
			rating.userId(user().id());
			ctrl().service().createRating(rating);
		}
	}
}

void Blog::paginate(std::istream *stream)
{
	/// Parameters
	std::int32_t sort = INTMAX(32); std::istringstream(val["s"]) >> sort;
	std::int32_t page = INTMAX(32); std::istringstream(val["p"]) >> page;
	val["s"] = val["p"] = "";

	if(sort != INTMAX(32)) this->sort = sort;
	else if(page != INTMAX(32)) paginator.page(page);
	else paginator.extend();

	ctrl().redirect(path() + "?" + param());
}