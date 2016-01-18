#include "Documentation.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"


#include "core/Tag.h"
#line 3 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
PAGE(Documentation)

void DocumentationHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");

#line 5 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
SESSION	std::ostream& responseStream = response.send();
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
#line 7 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
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
#line 7 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 8 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
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
#line 8 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 9 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
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
#line 9 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 10 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
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
#line 10 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 12 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TILE_BEGIN("content")	responseStream << "\n";
	responseStream << "\t\t<h1>Documentation</h1>\n";
	responseStream << "\t\t<p>\n";
	responseStream << "\t\t\tnot implemented yet.\n";
	responseStream << "\t\t</p>\n";
	responseStream << "\t";
#line 17 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 19 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
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
#line 19 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 20 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TILE_BEGIN("footer")	responseStream << "";
	// begin include src/view/tile/footer.html
	responseStream << "\t\n";
	responseStream << "\t<span>Copyright © 2015 [There could be your company].</span>\n";
	responseStream << "";
	// end include src/view/tile/footer.html
	responseStream << "";
#line 20 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 22 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Documentation.c"
TEMPLATE("html/template.html")	responseStream << "\n";
	responseStream << "";
}
