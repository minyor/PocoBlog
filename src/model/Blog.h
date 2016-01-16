#ifndef MODEL_BLOG_H
#define MODEL_BLOG_H


#include <core/Header.h>
#include <core/Util.h>
#include <model/Post.h>


namespace model
{
	class Category;
	class Post;

	class Blog
	{
		Post _post;

	public:
		Poco::Nullable<core::DataID> _id;
		core::DataID _category_id;
		core::DataID _post_id;
		std::string _title;
		std::int64_t _rating;
		Poco::DateTime _date;

	public:
		Blog();
		~Blog();

	public:
		//void post(Post *val);
		//__inline Post *post() const { return &(*_post); }
		__inline Post &post() { return _post; }

	public:
		__inline void id(core::DataID val) { val ? (_id = val) : (_id = Poco::NULL_GENERIC); }
		__inline core::DataID id() const { return _id.isNull() ? 0 : (core::DataID)_id; }

		__inline void categoryId(core::DataID val) { _category_id = val; }
		__inline core::DataID categoryId() const { return _category_id; }

		__inline void postId(core::DataID val) { _post_id = val; }
		__inline core::DataID postId() const { return _post_id; }

		__inline void title(const std::string &val) { _title = val; }
		__inline const std::string &title() const { return _title; }

		__inline void rating(std::uint64_t val) { _rating = val; }
		__inline std::uint64_t rating() { return _rating; }

		__inline void date(const Poco::DateTime &val) { _date = val; }
		__inline const Poco::DateTime &date() const { return _date; }

	};
}


#endif // MODEL_BLOG_H
