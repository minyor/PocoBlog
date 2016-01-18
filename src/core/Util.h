//
// Helper classes and functions
// for use with facets and sessions
//
// Copyright (c) 2016, minyor.
//
// License:	BSD
//


#ifndef CORE_UTIL_H
#define CORE_UTIL_H


#include "Poco/Net/MailMessage.h"
#include "Poco/Net/StringPartSource.h"

#include <core/Header.h>


#ifndef NULL
	#define NULL 0
#endif


namespace core
{
	typedef std::uint64_t DataID;
	typedef DataID UserID;
	typedef std::uint8_t UserGroup;

	typedef Poco::Mutex Mutex;
	//typedef Poco::FastMutex Mutex;
	typedef core::Mutex::ScopedLock ScopedLock;

	template<typename T>
		class Vector
		{
			typedef std::shared_ptr<T> Item;
			typedef std::vector<Item> Vec;
			typedef std::shared_ptr<Vec> Ptr;
			Ptr _vec;

		public:
			__inline void add(T *ptr) { (*this)->push_back(Item(ptr)); }
			__inline Vector &operator =(Vec *vec) { _vec = Ptr(vec); return *this; }
			__inline Vec *operator ->() { return &(*(*this)); }
			__inline Vec &operator ()() { return (*(*this)); }
			__inline Vec &me() { return (*(*this)); }
			__inline Vec &operator *() { if(!_vec) _vec = Ptr(new Vec); return *_vec; }
			__inline operator bool() const { return (bool)_vec; }
			__inline std::uint64_t count() { return (*(*this)).size(); }

		};

	template<typename T>
		class Tree
		{
			typedef std::shared_ptr<T> Item;

		public:
			struct Node {
				Item item; Tree children;
				__inline Node(T *ptr = NULL) { item = Item(ptr); }
				__inline T *operator ->() { return &(*(*this)); }
				__inline T &operator ()() { return (*(*this)); }
				__inline T &operator *() { return *item; }
			};

		public:
			__inline Tree() : _count(0) {}

		private:
			typedef std::vector<Node> Vec;
			typedef std::shared_ptr<Vec> Ptr;
			Ptr _vec;
			std::uint64_t _count;

		public:
			__inline void add(T *ptr) { (*this)->push_back(Node(ptr)); }
			__inline Tree &operator =(Vec *vec) { _vec = Ptr(vec); return *this; }
			__inline Vec *operator ->() { return &(*(*this)); }
			__inline Vec &operator ()() { return (*(*this)); }
			__inline Vec &me() { return (*(*this)); }
			__inline Vec &operator *() { if(!_vec) _vec = Ptr(new Vec); return *_vec; }
			__inline operator bool() const { return (bool)_vec; }

		public:
			__inline void count(std::uint64_t val) { _count = val; }
			__inline std::uint64_t count() const { return _count; }
			std::uint64_t calcCount() { _count = me().size();
				for(std::uint32_t i=0; i<me().size(); ++i)
					if(me()[i].children) _count += me()[i].children.calcCount();
				return _count;
			}

		};

	std::string dateFormat();
	std::int32_t dateTimeZone();

	__inline static std::string to_string(const std::string &val) { return val; }
	__inline static std::string to_string(const Poco::DateTime &val) { return Poco::DateTimeFormatter::format(val, dateFormat(), dateTimeZone()); }
	template<typename T> __inline static std::string to_string(const Poco::Nullable<T> &val) {
		if(val.isNull()) return "null"; return std::to_string((T &)val); }
	using std::to_string;

	namespace util
	{
		class Hash
		{
		public:
			static std::string salt(std::uint32_t size);
			static std::string hash(const std::string &in);

			/**
			 * @brief Constant Time strings comparision implementation
			 * @return true if a == b, false otherwise
			 */
			static bool isEqual(const std::string &a, const std::string &b);

		};

		class Html
		{
		public:
			/**
			 * @brief Text to html and BBcode formating
			 * @param paragraphs: if true, converts 2 or more new lines into paragraph i.e. <p>...</p> 
			 * @return formatted string 
			 */
			static std::string format(const std::string &in, bool paragraphs = false);

		};

		class Email
		{
		public:
			static bool valid(const std::string &email);
			static bool send(const std::string &host, std::uint16_t port, const Poco::Net::MailMessage &message,
				const std::string &username = "", const std::string &password = "");

		};
	}
}


#endif // CORE_UTIL_H
