#ifndef MODEL_SERVICE_H
#define MODEL_SERVICE_H


#include <model/User.h>
#include <model/Category.h>
#include <model/Blog.h>
#include <model/Post.h>
#include <model/Rating.h>
#include <core/Server.h>


namespace model
{
	class Service : public core::db::Sql
	{
	public:
		Service();
		~Service();

	protected:
		void onInit(core::db::DataSession &session);

	public:
		bool createCategory(Category &val);
		bool updateCategory(Category &val);
		bool deleteCategory(core::DataID id);
		bool getCategory(Category &val, core::DataID id);
		core::Vector<Category> getCategoryChain(core::DataID id);
		core::Vector<Category> getCategories(core::DataID parentID = 0, 
			std::int8_t sort = 1, std::int64_t limit = INTMAX(64), std::int64_t offset = 0);
		std::uint64_t getCategoriesCount(core::DataID parentID = 0);

		bool createBlog(Blog &val);
		bool updateBlog(Blog &val);
		bool deleteBlog(core::DataID id);
		bool deleteBlogsByCategory(core::DataID catId);
		bool getBlog(Blog &val, core::DataID blogId, core::DataID userId);
		core::Vector<Blog> searchBlogs(const std::string &query,
			std::int8_t sort = 1, std::int64_t limit = INTMAX(64), std::int64_t offset = 0);
		core::Vector<Blog> getBlogsByCategory(core::DataID id, 
			std::int8_t sort = 1, std::int64_t limit = INTMAX(64), std::int64_t offset = 0);
		std::uint64_t getBlogsCountByCategory(core::DataID id);

		bool createPost(Post &val);
		bool updatePost(Post &val);
		bool deletePost(core::DataID id);
		bool deletePostsByBlog(core::DataID blogId);
		bool deletePostsByPost(core::DataID postId);
		bool getPost(Post &val, core::DataID id);
		/**
		 * @param sort : (1)newest; (-1)oldest; (0)toprated.
		 */
		core::Tree<Post> getPostsByBlog(core::DataID blogId, core::DataID userId,
			std::int8_t sort = 1, std::int64_t limit = INTMAX(64), std::int64_t offset = 0);

		bool createRating(Rating &val);
		bool deleteRating(core::DataID id);
		bool deleteRatingsByPost(core::DataID postId);
		bool getRating(Rating &val, core::DataID id);
		bool getRatingByPostAndUser(Rating &val, core::DataID postId, core::DataID userId);

	};
}


#endif // MODEL_SERVICE_H
