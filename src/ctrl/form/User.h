#ifndef CTRL_FORM_USER_H
#define CTRL_FORM_USER_H


#include <core/Header.h>
#include <ctrl/Controller.h>


namespace ctrl { namespace form
{
	class User : public core::Form
	{
	public:
		enum Mode {MODE_SETTINGS=0, MODE_USERS};

		struct UserRow
		{
			bool checked;
			core::Vector<std::string> data;
			__inline UserRow(core::Vector<std::string> data) : checked(false), data(data) {}
		};

	public:
		core::facet::Paginator paginator;
		core::facet::Table userTable;
		core::facet::List userGroups;

		core::Vector<model::User> users;

	public:
		User();
		~User();

	public:
		std::string format(const std::string &in);
		Mode mode();
		std::string param();

	public:
		void onEnter();
		void onLoad();

	private:
		void updateUser(std::istream *stream);
		void removeUser(std::istream *stream);
		void selectUser(std::istream *stream);
		void updateGroup(std::istream *stream);
		void paginate(std::istream *stream);

	public:
		__inline Controller &ctrl() const { return (Controller &)session(); }

	};
}}


#endif // CTRL_FORM_USER_H
