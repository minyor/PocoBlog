#ifndef CORE_PAGE_H
#define CORE_PAGE_H


#include <core/Header.h>
#include <core/Server.h>
#include <core/Session.h>


namespace core
{
	typedef void *(*NewClass)();

	class Page
	{
		NewClass _newClass;
		std::string  _path;

		friend void Server::addPage(Page *page);
		friend Poco::Net::HTTPRequestHandler *Server::newHandler(const std::string &path);
		virtual Poco::Net::HTTPRequestHandler *newHandler();

	public:
		Page();
		virtual ~Page();

	public:
		virtual Page &self() { return *this; }

	public:
		__inline void newClass(NewClass val) { _newClass = val; }
		__inline NewClass newClass() const { return _newClass; }
		
		__inline void path(const std::string &val) { _path = val; }
		__inline const std::string &path() const { return _path; }

	};
}


#endif // CORE_PAGE_H
