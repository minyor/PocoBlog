#ifndef MODEL_CATEGORY_H
#define MODEL_CATEGORY_H


#include <core/Header.h>
#include <core/Util.h>


namespace model
{
	class Category
	{
	public:
		Poco::Nullable<core::DataID> _id;
		Poco::Nullable<core::DataID> _parent_id;
		std::string _title;
		Poco::DateTime _date;

	public:
		Category();
		~Category();

	public:
		__inline void id(core::DataID val) { val ? (_id = val) : (_id = Poco::NULL_GENERIC); }
		__inline core::DataID id() const { return _id.isNull() ? 0 : (core::DataID)_id; }

		__inline void parentId(core::DataID val) { val ? (_parent_id = val) : (_parent_id = Poco::NULL_GENERIC); }
		__inline core::DataID parentId() const { return _parent_id.isNull() ? 0 : (core::DataID)_parent_id; }

		__inline void title(const std::string &val) { _title = val; }
		__inline const std::string &title() const { return _title; }

		__inline void date(const Poco::DateTime &val) { _date = val; }
		__inline const Poco::DateTime &date() const { return _date; }

	};
}


#endif // MODEL_CATEGORY_H
