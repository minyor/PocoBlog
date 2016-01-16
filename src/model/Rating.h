#ifndef MODEL_RATING_H
#define MODEL_RATING_H


#include <core/Header.h>
#include <core/Util.h>


namespace model
{
	class Rating
	{
	public:
		Poco::Nullable<core::DataID> _id;
		core::DataID _post_id;
		core::DataID _user_id;

	public:
		Rating();
		~Rating();

	public:
		__inline void id(core::DataID val) { val ? (_id = val) : (_id = Poco::NULL_GENERIC); }
		__inline core::DataID id() const { return _id.isNull() ? 0 : (core::DataID)_id; }

		__inline void postId(core::DataID val) { _post_id = val; }
		__inline core::DataID postId() const { return _post_id; }

		__inline void userId(core::DataID val) { _user_id = val; }
		__inline core::DataID userId() const { return _user_id; }

	};
}


#endif // MODEL_RATING_H
