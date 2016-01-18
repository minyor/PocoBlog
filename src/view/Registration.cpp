#include "Registration.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"


#include "core/Tag.h"
#include "ctrl/form/Registration.h"
#line 4 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
PAGE(Registration, PATH("/Registration")CLASS(ctrl::form::Registration))

void RegistrationHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");

#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
SESSION	std::ostream& responseStream = response.send();
	responseStream << "";
	responseStream << "\n";
	responseStream << "";
	responseStream << "\n";
	responseStream << "";
	responseStream << "\n";
	responseStream << "";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 8 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_BEGIN("head")	responseStream << "";
	// begin include src/view/tile/head.html
	responseStream << "\n";
	responseStream << "\t<meta charset=\"utf-8\">\n";
	responseStream << "\t<meta http-equiv=\"X-UA-Compatible\" content=\"IE=9\" />\n";
	responseStream << "\t<script type=\"text/javascript\">window.suggestmeyes_loaded = true;</script>\n";
	responseStream << "\t<title>Main Page</title>\n";
	responseStream << "\t<link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\">\n";
	responseStream << "\t<!--<meta http-equiv=\"refresh\" content=\"1\">-->\n";
	responseStream << "";
	// end include src/view/tile/head.html
	responseStream << "";
#line 8 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 9 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_BEGIN("topbar")	responseStream << "";
	// begin include src/view/tile/topbar.html
	responseStream << "\n";
	responseStream << "\t";
#line 2 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
IF(user)	responseStream << "\n";
	responseStream << "\t\t<div id=\"session\">\n";
	responseStream << "\t\t\t<span class=\"topbar\">\n";
	responseStream << "\t\t\t\t<a class=\"topbar\" href=\"/User\"><span class=\"topbar\">\n";
	responseStream << "\t\t\t\t\t";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
IF(user.group() == user.ADMIN)	responseStream << "#";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
	responseStream << (user.username());
	responseStream << "#";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
ELSE	responseStream << "[";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
	responseStream << (user.username());
	responseStream << "]";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
ENDIF	responseStream << "\n";
	responseStream << "\t\t\t\t</span></a>\n";
	responseStream << "\t\t\t\t<a class=\"topbar\" href=\"/*logout\">Sign out</a>\n";
	responseStream << "\t\t\t</span>\n";
	responseStream << "\t\t</div>\n";
	responseStream << "\t";
#line 11 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
ELSE	responseStream << "\n";
	responseStream << "\t\t<script type=\"text/javascript\"> function submitSigninForm() { document.forms[\"signinForm\"].submit(); } </script>\n";
	responseStream << "\t\t<form id=\"signinForm\" class=\"ignore\" method=\"POST\" action=\"*login\">";
#line 13 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t<div id=\"session\">\n";
	responseStream << "\t\t\t\t<span class=\"topbar\">\n";
	responseStream << "\t\t\t\t\t<input class=\"topbar\" type=\"text\" ";
#line 16 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
	responseStream << (NAME(username));
	responseStream << " placeholder=\"Username...\" style=\"width: 100px;\" onkeypress=\"if(event.keyCode==13) submitSigninForm();\">\n";
	responseStream << "\t\t\t\t\t<input class=\"topbar\" type=\"password\" ";
#line 17 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
	responseStream << (NAME(password));
	responseStream << " placeholder=\"Password...\" style=\"width: 100px;\" onkeypress=\"if(event.keyCode==13) submitSigninForm();\">\n";
	responseStream << "\t\t\t\t\t<!--<a class=\"topbar\" href=\"/Login\">Sign In</a>-->\n";
	responseStream << "\t\t\t\t\t<a class=\"topbar\" href=\"javascript:submitSigninForm()\">Log in</a>\n";
	responseStream << "\t\t\t\t\t<a class=\"topbar\" href=\"/Registration\">Sign up</a>\n";
	responseStream << "\t\t\t\t</span>\n";
	responseStream << "\t\t\t</div>\n";
	responseStream << "\t\t</form>\n";
	responseStream << "\t";
#line 24 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/topbar.html"
ENDIF	responseStream << "\n";
	responseStream << "";
	// end include src/view/tile/topbar.html
	responseStream << "";
#line 9 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 10 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_BEGIN("header")	responseStream << "";
	// begin include src/view/tile/header.html
	responseStream << "\n";
	responseStream << "\t<a id=\"logo\" href=\"/\">\n";
	responseStream << "\t\t<img src=\"/images/logo.png\" alt=\"Stack Overflow\" />\n";
	responseStream << "\t</a>\n";
	responseStream << "\t<script type=\"text/javascript\"> function submitSearchForm() { document.forms[\"searchForm\"].submit(); } </script>\n";
	responseStream << "\t<form id=\"searchForm\" class=\"ignore\" method=\"GET\" action=\"*search\">\n";
	responseStream << "\t\t<div id=\"search\">\n";
	responseStream << "\t\t\t<span class=\"toolbar\">\n";
	responseStream << "\t\t\t\t<input class=\"search\" type=\"text\" ";
#line 9 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/header.html"
	responseStream << (NAME(query));
	responseStream << " placeholder=\"Search...\" style=\"width: 170px;\" onkeypress=\"if(event.keyCode==13) submitSearchForm();\">\n";
	responseStream << "\t\t\t\t<a class=\"toolbar\" href=\"javascript:submitSearchForm()\">Find</a>\n";
	responseStream << "\t\t\t</span>\n";
	responseStream << "\t\t</div>\n";
	responseStream << "\t</form>\t\n";
	responseStream << "";
	// end include src/view/tile/header.html
	responseStream << "";
#line 10 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 11 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_BEGIN("menu")	responseStream << "";
	// begin include src/view/tile/menu.html
	responseStream << "\n";
	responseStream << "\t<ul id=\"menu\">\n";
	responseStream << "\t\t";
#line 3 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/menu.html"
FOREACH(entry, me.menu())	responseStream << "\n";
	responseStream << "\t\t\t<li><a href=\"";
#line 4 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/menu.html"
	responseStream << (entry.url);
	responseStream << "\" ";
#line 4 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/menu.html"
	responseStream << (me.checkPath(entry.url) ? "class='active'" : "");
	responseStream << "><span>";
#line 4 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/menu.html"
	responseStream << (entry.title);
	responseStream << "</span></a></li>\n";
	responseStream << "\t\t";
#line 5 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/menu.html"
ENDFOR	responseStream << "\n";
	responseStream << "\t</ul>\n";
	responseStream << "";
	// end include src/view/tile/menu.html
	responseStream << "";
#line 11 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 13 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_BEGIN("content")	responseStream << "\n";
	responseStream << "\t\t";
#line 14 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
IF(me["mode"] == "activated")	responseStream << "\n";
	responseStream << "\t\t\t<h1>Activation Successful!</h1>\n";
	responseStream << "\t\t\tThe account for ";
#line 16 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (me.newUser->username());
	responseStream << " has been successfully activated!\n";
	responseStream << "\t\t";
#line 17 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
ELIF(me["mode"] == "inactive" && me.newUser && me.newUser->group() == me.newUser->INACTIVE)	responseStream << "\n";
	responseStream << "\t\t\t<h1>Registration Successful!</h1>\n";
	responseStream << "\t\t\tThank you for registering! A confirmation email has been sent to ";
#line 19 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (me.newUser->email());
	responseStream << ". Please click on the Activation Link to Activate your account.\n";
	responseStream << "\t\t\t<a href=\"/*resendActivationEmail\">Resend confirmation email?</a>\n";
	responseStream << "\t\t";
#line 21 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
ELIF(!user)	responseStream << "\n";
	responseStream << "\t\t\t<h1>Registration:</h1>\n";
	responseStream << "\t\t\t";
#line 23 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (me.captcha.htmlUse());
	responseStream << "\n";
	responseStream << "\t\t\t<form method=\"POST\" action=\"*signin\" id=\"userForm\">";
#line 24 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t<div class=\"userCol1\">Username:</div><div class=\"userCol2\"><input type=\"text\" ";
#line 25 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (NAME(username));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t<div class=\"userCol1\">Email Address:</div><div class=\"userCol2\"><input type=\"text\" ";
#line 26 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (NAME(email));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t<div class=\"userCol1\">Password:</div><div class=\"userCol2\"><input type=\"password\" ";
#line 27 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (NAME(password));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t<div class=\"userCol1\">Confirm Password:</div><div class=\"userCol2\"><input type=\"password\" ";
#line 28 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (NAME(password2));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t<div class=\"userCol1\">";
#line 29 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (me.captcha.htmlQuestion());
	responseStream << "</div><div class=\"userCol2\">";
#line 29 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (me.captcha.htmlAnswer());
	responseStream << "</div>\n";
	responseStream << "\t\t\t\t<div class=\"userCol1\"></div><div class=\"userCol2\"><input type=\"submit\" value=\"Register\"></div>\n";
	responseStream << "\t\t\t\t<div class=\"userStatus\"><span class=\"userError\">";
#line 31 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
	responseStream << (me["status"]);
	responseStream << "</span></div>\n";
	responseStream << "\t\t\t</form><!--Forgot your password?-->\n";
	responseStream << "\t\t";
#line 33 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
ELSE	responseStream << "\n";
	responseStream << "\t\t\t<h1>You are already registered.</h1>\n";
	responseStream << "\t\t";
#line 35 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
ENDIF	responseStream << "\n";
	responseStream << "\t";
#line 36 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 38 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_BEGIN("navigation")	responseStream << "";
	// begin include src/view/tile/navigation.html
	responseStream << "\n";
	responseStream << "\t<div id=\"toolbar\">\n";
	responseStream << "\t</div>\n";
	responseStream << "\t<ul id=\"list\">\n";
	responseStream << "\t\t";
#line 5 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/navigation.html"
FOREACH(entry, me.sidebar())	responseStream << "\n";
	responseStream << "\t\t\t<li><a href=\"";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/navigation.html"
	responseStream << (entry.url);
	responseStream << "\" ";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/navigation.html"
	responseStream << (me.checkPath(entry.url) ? "class='active'" : "");
	responseStream << "><span>";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/navigation.html"
	responseStream << (entry.title);
	responseStream << "</span></a></li>\n";
	responseStream << "\t\t";
#line 7 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/tile/navigation.html"
ENDFOR	responseStream << "\n";
	responseStream << "\t</ul>\n";
	responseStream << "";
	// end include src/view/tile/navigation.html
	responseStream << "";
#line 38 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 39 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_BEGIN("footer")	responseStream << "";
	// begin include src/view/tile/footer.html
	responseStream << "\t\n";
	responseStream << "\t<span>Copyright © 2015 [There could be your company].</span>\n";
	responseStream << "";
	// end include src/view/tile/footer.html
	responseStream << "";
#line 39 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 41 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Registration.c"
TEMPLATE("html/template.html")	responseStream << "\n";
	responseStream << "";
}
