#ifndef CTRL_FORM_REGISTRATION_H
#define CTRL_FORM_REGISTRATION_H


#include <core/Header.h>
#include <ctrl/Controller.h>


namespace ctrl { namespace form
{
	class Registration : public core::Form
	{
	public:
		std::unique_ptr<model::User> newUser;
		core::facet::CaptchaCalc captcha;

	public:
		Registration();
		~Registration();

	private:
		bool sendActivationEmail();

	public:
		void onEnter();
		void onLoad();

	private:
		void signin(std::istream *stream);
		void resendActivationEmail(std::istream *stream);
		void activate(std::istream *stream);

	public:
		__inline Controller &ctrl() const { return (Controller &)session(); }

	};
}}


#endif // CTRL_FORM_REGISTRATION_H
