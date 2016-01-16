
#include "Poco/Data/Session.h"
#include "Poco/Data/TypeHandler.h"

#include <core/Header.h>
#include <model/Service.h>
#include <core/Server.h>
#include <core/db/SQLTable.h>


using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using namespace core;
using namespace core::db;
using namespace model;


SQLTableBegin(Category, model::Category)
	SQLColumn(1, _id, "INTEGER PRIMARY KEY")
	SQLColumn(2, _parent_id, "INTEGER")
	SQLColumn(3, _title, "VARCHAR(100) UNIQUE")
	SQLColumn(4, _date, "DATETIME")
SQLTableEnd(Category)

SQLTableBegin(Blog, model::Blog)
	SQLColumn(1, _id, "INTEGER PRIMARY KEY")
	SQLColumn(2, _category_id, "INTEGER")
	SQLColumn(3, _post_id, "INTEGER")
	SQLColumn(4, _title, "VARCHAR(100)")
	SQLColumn(5, _date, "DATETIME")
	SQLColumn(6, _rating, "INTEGER")
SQLTableEnd(Blog)

SQLTableBegin(Post, model::Post)
	SQLColumn(1, _id, "INTEGER PRIMARY KEY")
	SQLColumn(2, _parent_id, "INTEGER")
	SQLColumn(3, _blog_id, "INTEGER")
	SQLColumn(4, _user_id, "INTEGER")
	SQLColumn(5, _content, "TEXT")
	SQLColumn(6, _date, "DATETIME")
	SQLColumn(7, _rating, "INTEGER")
SQLTableEnd(Post)

SQLTableBegin(Rating, model::Rating)
	SQLColumn(1, _id, "INTEGER PRIMARY KEY")
	SQLColumn(2, _post_id, "INTEGER")
	SQLColumn(3, _user_id, "INTEGER")
SQLTableEnd(Rating)


Service::Service()
{
}
Service::~Service()
{
}

void Service::onInit(core::db::DataSession &session)
{
	try {
		session << table("Category").createQuery(), now;
		printff("SQL 'Category' table created.\n");
	}
	catch(...) {}

	try {
		session << table("Blog").createQuery(), now;
		printff("SQL 'Blog' table created.\n");
	}
	catch(...) {}

	try {
		session << table("Post").createQuery(), now;
		printff("SQL 'Post' table created.\n");
	}
	catch(...) {}

	try {
		session << table("Rating").createQuery(), now;
		printff("SQL 'Rating' table created.\n");
	}
	catch(...) {}
}

bool Service::createCategory(Category &val)
{
	val.id(0);
	val.date(Poco::DateTime());

	std::unique_ptr<DataSession> session = this->session();

	try {
		val.id(0);
		core::DataID lastId;
		Statement(*session) << this->table("Category").insertQuery(), use(val), now;
		Statement(*session) << this->table("Category").lastIdQuery(), into(lastId), now;
		val.id(lastId); printff("create Category: %ld\n", val.id());
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }

	return true;
}
bool Service::updateCategory(Category &val)
{
	core::DataID id = val.id();
	val.date(Poco::DateTime());

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement(*session) << this->table("Category").updateQuery() + " WHERE _id=?", use(val), use(id), now;
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return true;
}
bool Service::deleteCategory(core::DataID id)
{
	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement(*session) << "DELETE FROM Category WHERE _id=?", use(id), now;
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }

	deleteBlogsByCategory(id);
	return true;
}
bool Service::getCategory(Category &val, core::DataID id)
{
	if(!id) return false;
	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT * FROM Category WHERE _id=?", into(val), use(id),
			range(0, 1); //  iterate over result set one row at a time
		select.execute();
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return val.id();
}
core::Vector<Category> Service::getCategoryChain(core::DataID id)
{
	Category val;
	Vector<Category> ret;
	do {
		getCategory(val, id);
		if(val.id()) ret.add(new Category(val));
		id = val.parentId();
	}
	while(id);
	return ret;
}
core::Vector<Category> Service::getCategories(core::DataID parentID,
	std::int8_t sort, std::int64_t limit, std::int64_t offset)
{
	Category val;
	Vector<Category> ret;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << (std::string)"SELECT ACat.* FROM (\
				SELECT _id FROM Category WHERE ifnull(_parent_id, 0)=?\
				ORDER BY _id " + (sort < 0 ? "ASC " : "DESC ") + "LIMIT ? OFFSET ?\
			) AS L INNER JOIN Category AS ACat ON ACat._id=L._id\
			ORDER BY ACat._id " + (sort < 0 ? "ASC " : "DESC "),
			into(val), use(parentID), use(limit), use(offset), range(0, 1); //  iterate over result set one row at a time

		while(!select.done()) {
			select.execute(); if(!val.id()) continue;
			ret.add(new Category(val));
		}
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return Vector<Category>(); }
	catch(...) { return Vector<Category>(); }
	return ret;
}
std::uint64_t Service::getCategoriesCount(core::DataID parentID)
{
	std::uint64_t count = 0;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT COUNT(_id) FROM Category WHERE ifnull(_parent_id, 0)=?", into(count), use(parentID),
			range(0, 1), now; //  iterate over result set one row at a time
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return 0; }
	catch(...) { return 0; }
	return count;
}

bool Service::createBlog(Blog &val)
{
	val.id(0);
	val.date(Poco::DateTime());

	std::unique_ptr<DataSession> session = this->session();

	try {
		val.id(0);
		core::DataID lastId;
		Statement(*session) << this->table("Blog").insertQuery(), use(val), now;
		Statement(*session) << this->table("Blog").lastIdQuery(), into(lastId), now;
		val.id(lastId); printff("create Blog: %ld\n", val.id());
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }

	val.post().blogId(val.id());
	if(!createPost(val.post()))
		return false;

	val.postId(val.post().id());
	return updateBlog(val);
}
bool Service::updateBlog(Blog &val)
{
	core::DataID id = val.id();
	val.date(Poco::DateTime());

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement(*session) << this->table("Blog").updateQuery() + " WHERE _id=?", use(val), use(id), now;
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return true;
}
bool Service::deleteBlog(core::DataID id)
{
	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement(*session) << "DELETE FROM Blog WHERE _id=?", use(id), now;
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }

	deletePostsByBlog(id);
	return true;
}
bool Service::deleteBlogsByCategory(core::DataID catId)
{
	Blog val;
	std::stack<core::DataID> ids;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT * FROM Blog WHERE ifnull(_category_id, 0)=?",
			into(val), use(catId), range(0, 1); //  iterate over result set one row at a time

		while(!select.done()) {
			select.execute();
			ids.push(val.id());
		}
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }

	for(; !ids.empty(); ids.pop()) deleteBlog(ids.top());
	return true;
}
bool Service::getBlog(Blog &val, core::DataID blogId, core::DataID userId)
{
	if(!blogId) return false;
	std::unique_ptr<DataSession> session = this->session();

	std::uint64_t rated = 0;
	try {
		Statement select(*session);
		select << "SELECT ABlog.*, APost.*, AUser.*,\
				(SELECT COUNT(ARating._id) FROM Rating AS ARating WHERE ARating._post_id=APost._id AND ARating._user_id=?)\
			FROM Blog AS ABlog \
			INNER JOIN Post AS APost ON ABlog._post_id=APost._id \
			LEFT OUTER JOIN User AS AUser ON APost._user_id=AUser._id \
			WHERE ABlog._id=?", into(val), into(val.post()), into(val.post().user()), into(rated), use(userId), use(blogId),
			range(0, 1); //  iterate over result set one row at a time
		select.execute();
		val.post().rated(rated);
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return val.id();
}
core::Vector<Blog> Service::searchBlogs(const std::string &query,
	std::int8_t sort, std::int64_t limit, std::int64_t offset)
{
	std::string key;
	std::vector<std::string> keys;
	std::istringstream iss(query);
	while(iss >> key) keys.push_back("%" + key + "%");

	std::string _searchQuery = "SELECT ABlog.*\
		FROM (\
			SELECT DISTINCT ABlog.*\
			FROM Blog AS ABlog\
			LEFT OUTER JOIN Post AS APost ON ABlog._post_id=APost._id OR ABlog._id=APost._blog_id \
			WHERE ";
	for(std::uint32_t i=0, e=keys.size()-1; i<keys.size(); ++i) _searchQuery +=
		(std::string)"LOWER(ABlog._title) LIKE LOWER(?)" + (i == e ? "" : " OR ");
	_searchQuery += " OR ";
	for(std::uint32_t i=0, e=keys.size()-1; i<keys.size(); ++i) _searchQuery +=
		(std::string)"LOWER(APost._content) LIKE LOWER(?)" + (i == e ? "" : " OR ");
	_searchQuery += " \
			ORDER BY ABlog._id\
			LIMIT ? OFFSET ?\
		) AS L\
		INNER JOIN Blog AS ABlog ON ABlog._id=L._id\
	";

	Blog val;
	Vector<Blog> ret;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << _searchQuery, into(val);
		for(std::uint32_t i=0; i<keys.size(); ++i) select, use(keys[i]);
		for(std::uint32_t i=0; i<keys.size(); ++i) select, use(keys[i]);
		select, use(limit), use(offset), range(0, 1); //  iterate over result set one row at a time

		while(!select.done()) {
			select.execute(); if(!val.id()) continue;
			ret.add(new Blog(val));
		}
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return Vector<Blog>(); }
	catch(...) { return Vector<Blog>(); }
	return ret;

}
core::Vector<Blog> Service::getBlogsByCategory(core::DataID id,
	std::int8_t sort, std::int64_t limit, std::int64_t offset)
{
	Blog val;
	Vector<Blog> ret;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << (std::string)"SELECT ABlog.* FROM (\
				SELECT _id FROM Blog WHERE ifnull(_category_id, 0)=?\
				ORDER BY _id " + (sort < 0 ? "ASC " : "DESC ") + "LIMIT ? OFFSET ?\
			) AS L INNER JOIN Blog AS ABlog ON ABlog._id=L._id\
			ORDER BY ABlog._id " + (sort < 0 ? "ASC " : "DESC "),
			into(val), use(id), use(limit), use(offset), range(0, 1); //  iterate over result set one row at a time

		while(!select.done()) {
			select.execute(); if(!val.id()) continue;
			ret.add(new Blog(val));
		}
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return Vector<Blog>(); }
	catch(...) { return Vector<Blog>(); }
	return ret;
}
std::uint64_t Service::getBlogsCountByCategory(core::DataID id)
{
	std::uint64_t count = 0;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT COUNT(_id) FROM Blog WHERE ifnull(_category_id, 0)=?", into(count), use(id),
			range(0, 1), now; //  iterate over result set one row at a time
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return 0; }
	catch(...) { return 0; }
	return count;
}

bool Service::createPost(Post &val)
{
	val.id(0);
	val.date(Poco::DateTime());

	/// If parent post has parent (Level 3 and deeper) then use Level 1 as a parent instead
	if(val.parentId()) {
		Post parent; getPost(parent, val.parentId());
		if(parent.id() && parent.parentId()) val.parentId(parent.parentId());
	}

	std::unique_ptr<DataSession> session = this->session();

	try {
		val.id(0);
		core::DataID lastId;
		Statement(*session) << this->table("Post").insertQuery(), use(val), now;
		Statement(*session) << this->table("Post").lastIdQuery(), into(lastId), now;
		val.id(lastId); printff("create Post: %ld\n", val.id());
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }

	return true;
}
bool Service::updatePost(Post &val)
{
	core::DataID id = val.id();
	val.date(Poco::DateTime());

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement(*session) << this->table("Post").updateQuery() + " WHERE _id=?", use(val), use(id), now;
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return true;
}
bool Service::deletePost(core::DataID id)
{
	if(!id) return false;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement(*session) << "DELETE FROM Post WHERE _id=?", use(id), now;
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }

	deleteRatingsByPost(id);
	deletePostsByPost(id);
	return true;
}
bool Service::deletePostsByBlog(core::DataID blogId)
{
	Post val;
	std::stack<core::DataID> ids;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT * FROM Post WHERE _blog_id=?",
			into(val), use(blogId), range(0, 1); //  iterate over result set one row at a time

		while(!select.done()) {
			select.execute();
			ids.push(val.id());
		}
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }

	for(; !ids.empty(); ids.pop()) deletePost(ids.top());
	return true;
}
bool Service::deletePostsByPost(core::DataID postId)
{
	Post val;
	std::stack<core::DataID> ids;

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT * FROM Post WHERE COALESCE(_parent_id, 0)=?",
			into(val), use(postId), range(0, 1); //  iterate over result set one row at a time

		while(!select.done()) {
			select.execute();
			ids.push(val.id());
		}
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }

	for(; !ids.empty(); ids.pop()) deletePost(ids.top());
	return true;
}
bool Service::getPost(Post &val, core::DataID id)
{
	if(!id) return false;
	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT APost.*, AUser.* FROM Post AS APost\
			LEFT OUTER JOIN User AS AUser ON APost._user_id=AUser._id\
			LEFT OUTER JOIN Rating AS ARating ON APost._id=ARating._post_id\
			WHERE APost._id=?",
			into(val), into(val.user()), use(id), range(0, 1); //  iterate over result set one row at a time
		select.execute();
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return val.id();
}
/**
 * @param sort : (1)newest; (-1)oldest; (0)toprated.
 */
core::Tree<Post> Service::getPostsByBlog(core::DataID blogId, core::DataID userId,
	std::int8_t sort, std::int64_t limit, std::int64_t offset)
{
	Post val;
	Tree<Post> ret;

	std::unique_ptr<DataSession> session = this->session();

	/// Retrieve blog's content post id
	Blog blog;
	core::DataID blogPostId;
	try {
		Statement select(*session);
		select << "SELECT * FROM Blog \
			WHERE Blog._id=?", into(blog), use(blogId),
			range(0, 1); //  iterate over result set one row at a time
		select.execute();
		blogPostId = blog.postId();
	}
	catch(...) { return Tree<Post>(); }

	/// Retrieve posts (Level 2 only). No recursion.
	try {
		std::uint64_t count = 0;
		std::uint64_t rated = 0;

		Statement select(*session);
		select << (std::string)
			"SELECT APost.*, AUser.*, (SELECT COUNT(_id) FROM Rating WHERE _post_id=APost._id AND _user_id=?) "
			"FROM ( "
			"	SELECT _p._id as _id, _p._rating AS _gr1, _c._rating AS _gr2 "
			"	FROM Post AS _p LEFT OUTER JOIN Post AS _c ON _p._parent_id=_c._id"
			"	WHERE _p._blog_id=? AND _p._id<>? "
			"	ORDER BY " + (!sort ?
			"		(CASE WHEN _p._parent_id IS NULL THEN _p._rating ELSE _c._rating END) DESC, " : "") +
			"		COALESCE(_p._parent_id, _p._id) " + (sort < 0 ? "ASC, " : "DESC, ") +
			"		_p._parent_id IS NOT NULL ASC, _p._id ASC LIMIT ? OFFSET ? "
			") AS L INNER JOIN Post AS APost ON APost._id=L._id "
			"LEFT OUTER JOIN User AS AUser ON APost._user_id=AUser._id "
			"ORDER BY " + (!sort ?
			"	(CASE WHEN APost._parent_id IS NULL THEN L._gr1 ELSE L._gr2 END) DESC, " : "") +
			"	COALESCE(APost._parent_id, APost._id) " + (sort < 0 ? "ASC, " : "DESC, ") +
			"	APost._parent_id IS NOT NULL ASC, APost._id ASC "
		;
		select, into(val), into(val.user()), into(rated),
			use(userId), use(blogId), use(blogPostId),
			use(limit), use(offset), range(0, 1);

		Tree<Post>::Node *prevRow = NULL;
		while(!select.done()) {
			select.execute(); if(!val.id()) continue;
			val.rated(rated);
			if(prevRow && val.parentId() == prevRow->item->id()) {
				prevRow->children.add(new Post(val)); ++count;
				continue;
			}
			ret.add(new Post(val)); ++count;
			prevRow = &ret().back();
		}
		ret.count(count);
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return Tree<Post>(); }
	catch(...) { return Tree<Post>(); }
	return ret;
}

bool Service::createRating(Rating &val)
{
	val.id(0);

	std::unique_ptr<DataSession> session = this->session();

	try {
		val.id(0);
		core::DataID lastId;
		Statement(*session) << this->table("Rating").insertQuery(), use(val), now;
		Statement(*session) << this->table("Rating").lastIdQuery(), into(lastId), now;

		/// Update '_rating' field in Post table
		core::DataID postID = val.postId();
		Statement(*session) << "UPDATE Post SET _rating= "
			"(SELECT COUNT(ARating._id) FROM Rating AS ARating WHERE ARating._post_id=Post._id) "
			"WHERE _id=?", use(postID), now;

		val.id(lastId); printff("create Rating: %ld\n", val.id());
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return true;
}
bool Service::deleteRating(core::DataID id)
{
	Rating val; getRating(val, id);

	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement(*session) << "DELETE FROM Rating WHERE _id=?", use(id), now;

		/// Update '_rating' field in Post table
		core::DataID postID = val.postId();
		Statement(*session) << "UPDATE Post SET _rating= "
			"(SELECT COUNT(ARating._id) FROM Rating AS ARating WHERE ARating._post_id=Post._id) "
			"WHERE _id=?", use(postID), now;
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return true;
}
bool Service::deleteRatingsByPost(core::DataID postId)
{
	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement(*session) << "DELETE FROM Rating WHERE _post_id=?", use(postId), now;
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return true;
}
bool Service::getRating(Rating &val, core::DataID id)
{
	if(!id) return false;
	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT * FROM Rating WHERE _id=?", into(val), use(id),
			range(0, 1); //  iterate over result set one row at a time
		select.execute();
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return val.id();
}
bool Service::getRatingByPostAndUser(Rating &val, core::DataID postId, core::DataID userId)
{
	if(!postId || !userId) return false;
	try {
		std::unique_ptr<DataSession> session = this->session();
		Statement select(*session);
		select << "SELECT * FROM Rating WHERE _post_id=? AND _user_id=?", into(val), use(postId), use(userId),
			range(0, 1); //  iterate over result set one row at a time
		select.execute();
	}
	catch(Poco::Exception &e) { printff("Poco::Exception: '%s'\n", e.displayText().c_str()); return false; }
	catch(...) { return false; }
	return val.id();
}