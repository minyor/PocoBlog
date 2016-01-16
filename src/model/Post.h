#ifndef MODEL_POST_H
#define MODEL_POST_H


#include <core/Header.h>
#include <core/Util.h>
#include <model/User.h>


namespace model
{
	class Post
	{
		User _user;
		std::uint64_t _viewLevel;
		bool _rated;

	public:
		Poco::Nullable<core::DataID> _id;
		Poco::Nullable<core::DataID> _parent_id;
		core::DataID _blog_id;
		core::DataID _user_id;
		std::string _content;
		std::int64_t _rating;
		Poco::DateTime _date;

	public:
		Post();
		~Post();

	public:
		__inline User &user() { return _user; }

		__inline void viewLevel(std::uint64_t val) { _viewLevel = val; }
		__inline std::uint64_t viewLevel() { return _viewLevel; }

		__inline void rated(bool val) { _rated = val; }
		__inline bool rated() { return _rated; }

	public:
		__inline void id(core::DataID val) { val ? (_id = val) : (_id = Poco::NULL_GENERIC); }
		__inline core::DataID id() const { return _id.isNull() ? 0 : (core::DataID)_id; }

		__inline void parentId(core::DataID val) { val ? (_parent_id = val) : (_parent_id = Poco::NULL_GENERIC); }
		__inline core::DataID parentId() const { return _parent_id.isNull() ? 0 : (core::DataID)_parent_id; }

		__inline void blogId(core::DataID val) { _blog_id = val; }
		__inline core::DataID blogId() const { return _blog_id; }

		__inline void userId(core::DataID val) { _user_id = val; }
		__inline core::DataID userId() const { return _user_id; }

		__inline void content(const std::string &val) { _content = val; }
		__inline const std::string &content() const { return _content; }

		__inline void rating(std::uint64_t val) { _rating = val; }
		__inline std::uint64_t rating() { return _rating; }

		__inline void date(const Poco::DateTime &val) { _date = val; }
		__inline const Poco::DateTime &date() const { return _date; }

	};
}


#endif // MODEL_POST_H
