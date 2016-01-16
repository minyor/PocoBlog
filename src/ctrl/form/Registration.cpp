
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"

#include <ctrl/form/Registration.h>


using namespace core;
using namespace ctrl::form;


Registration::Registration()
{
	addEvent(signin);
	addEvent(resendActivationEmail);
	addEvent(activate);
}
Registration::~Registration()
{
}

bool Registration::sendActivationEmail()
{
	if(!newUser) return false;
	newUser->activationToken(util::Hash::salt(24));
	ctrl().service().updateUser(*newUser);
	printff("Registration::sendActivationEmail '%s'\n", newUser->activationToken().c_str());

	Poco::Net::MailMessage message;
	message.setSender(server().conf().smtpUsername());
	message.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, newUser->email()));
	message.setSubject("Activation email!");
	std::string content;
	content += "Hi " + newUser->username() + ",\r\n";
	content += "Thank you for signing up with " + server().conf().name() + ". To activate\r\n";
	content += "your newly created account, please click on the following\r\n";
	content += "link:\r\n";
	content += "\r\n";
	content += (server().conf().https() ? "https://" : "http://") + server().conf().url() +
		"/Registration?event=activate&id=" + std::to_string(newUser->id()) + "&token=" + newUser->activationToken() + "\r\n";
	content += "\r\n";
	content += "The " + server().conf().name() + " Team";
	message.addContent(new Poco::Net::StringPartSource(content));
	return util::Email::send(server().conf().smtpHost(), server().conf().smtpPort(), message, server().conf().smtpUsername(), server().conf().smtpPassword());
}

void Registration::onEnter()
{
	val.clear();
	newUser = NULL;
}
void Registration::onLoad()
{
	if(newUser) ctrl().service().getUser(*newUser, newUser->id());
	captcha.refresh();
}

void Registration::signin(std::istream *stream)
{
	/// Parameters
	auto username = val["username"];
	auto email = val["email"];
	auto password = val["password"];
	auto password2 = val["password2"];
	auto capVal = val[captcha.name()];

	model::User userCheckUsername, userCheckEmail;
	ctrl().service().getUserByUsername(userCheckUsername, username);
	ctrl().service().getUserByEmail(userCheckEmail, email);

	val["status"] = "";
	val["mode"] = "";

	/// Validation
	if(captcha != capVal)
		val["status"] = "*Wrong answer to control question!";
	if(password != password2)
		val["status"] = "*Password does not match!";
	if(password.size() < 6)
		val["status"] = "*Password must be at least 6 characters long!";
	if(userCheckEmail.registered() && userCheckEmail.group() != userCheckEmail.SUBSCRIBER)
		val["status"] = "*Sorry, that email already registered!";
	if(userCheckEmail.registered() && userCheckEmail.group() == userCheckEmail.INACTIVE)
		val["status"] = "*Your account needs to be verified!";
	if(!core::util::Email::valid(email))
		val["status"] = "*Incorrect email format!";
	if(email.empty())
		val["status"] = "*Please enter email address!";
	if(userCheckUsername.registered())
		val["status"] = "*Sorry, that username already exists!";
	if(username.empty())
		val["status"] = "*Please enter username!";

	val.erase("password");
	val.erase("password2");
	val.erase(captcha.name());
	if(!val["status"].empty()) return;

	if(userCheckEmail.registered())
		ctrl().service().deleteUser(userCheckEmail.id());

	newUser = std::unique_ptr<model::User>(new model::User);
	newUser->username(username); newUser->password(password); newUser->email(email);
	ctrl().service().createUser(*newUser);

	if(newUser->group() == newUser->ADMIN)
	{
		newUser = NULL;
		ctrl().response().redirect("/");
		return;
	}

	sendActivationEmail();
	val["mode"] = "inactive";
}

void Registration::resendActivationEmail(std::istream *stream)
{
	sendActivationEmail();
}

void Registration::activate(std::istream *stream)
{
	if(val["id"].empty()) return;
	core::UserID id = 0; std::istringstream(val["id"]) >> id;
	if(!id) return;

	/// Check user
	model::User user;
	ctrl().service().getUser(user, id);
	if(!user.registered() || user.group() != user.INACTIVE || user.activationToken().empty())
		return;

	/// Erase activation token
	std::string activationToken = user.activationToken();
	user.activationToken("");
	ctrl().service().updateUser(user);

	/// If activation token does not match then delete user.
	if(!util::Hash::isEqual(val["token"], activationToken))
	{
		ctrl().service().deleteUser(user.id());
		return;
	}

	/// Update user
	user.group(user.USER);
	ctrl().service().updateUser(user);
	newUser = std::unique_ptr<model::User>(new model::User(user));
	val["mode"] = "activated";
	printff("User '%s' Activated!", user.username().c_str());
}