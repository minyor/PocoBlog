#ifndef CTRL_CONTROLLER_H
#define CTRL_CONTROLLER_H


#include <core/Header.h>
#include <model/Service.h>
#include <core/Page.h>


namespace ctrl
{
	class Controller : public core::Session
	{
		struct Data;
		std::unique_ptr<Data> _data;

	public:
		Controller();
		~Controller();

	public:
		void logout(core::Form &form, std::istream *stream);
		void login(core::Form &form, std::istream *stream);
		void search(core::Form &form, std::istream *stream);
		void parser(core::Form &form, std::istream *stream);

	public:
		__inline model::Service &service() const { return (model::Service &)core::server().sql(); }

	};
}


#endif // CTRL_CONTROLLER_H
