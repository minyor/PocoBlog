#include "User.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"


#include "core/Tag.h"
#include "ctrl/form/User.h"
#line 4 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
PAGE(User, CLASS(ctrl::form::User))

void UserHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");

#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
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
#line 8 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_BEGIN("head")	responseStream << "\n";
	responseStream << "\t\t";
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
	responseStream << "\n";
	responseStream << "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"css/calendar.css\">\n";
	responseStream << "\t\t<script type='text/javascript' src='js/calendar.js'></script>\n";
	responseStream << "\t\t<script type='text/javascript' src='js/countries.js'></script>\n";
	responseStream << "\t";
#line 13 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 15 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_BEGIN("topbar")	responseStream << "";
	// begin include src/view/tile/topbar.html
	responseStream << "\n";
	responseStream << "\t";
#line 2 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
IF(user)	responseStream << "\n";
	responseStream << "\t\t<div id=\"session\">\n";
	responseStream << "\t\t\t<span class=\"topbar\">\n";
	responseStream << "\t\t\t\t<a class=\"topbar\" href=\"/User\"><span class=\"topbar\">\n";
	responseStream << "\t\t\t\t\t";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
IF(user.group() == user.ADMIN)	responseStream << "#";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
	responseStream << (user.username());
	responseStream << "#";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
ELSE	responseStream << "[";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
	responseStream << (user.username());
	responseStream << "]";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
ENDIF	responseStream << "\n";
	responseStream << "\t\t\t\t</span></a>\n";
	responseStream << "\t\t\t\t<a class=\"topbar\" href=\"/*logout\">Sign out</a>\n";
	responseStream << "\t\t\t</span>\n";
	responseStream << "\t\t</div>\n";
	responseStream << "\t";
#line 11 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
ELSE	responseStream << "\n";
	responseStream << "\t\t<script type=\"text/javascript\"> function submitSigninForm() { document.forms[\"signinForm\"].submit(); } </script>\n";
	responseStream << "\t\t<form id=\"signinForm\" class=\"ignore\" method=\"POST\" action=\"*login\">";
#line 13 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t<div id=\"session\">\n";
	responseStream << "\t\t\t\t<span class=\"topbar\">\n";
	responseStream << "\t\t\t\t\t<input class=\"topbar\" type=\"text\" ";
#line 16 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
	responseStream << (NAME(username));
	responseStream << " placeholder=\"Username...\" style=\"width: 100px;\" onkeypress=\"if(event.keyCode==13) submitSigninForm();\">\n";
	responseStream << "\t\t\t\t\t<input class=\"topbar\" type=\"password\" ";
#line 17 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
	responseStream << (NAME(password));
	responseStream << " placeholder=\"Password...\" style=\"width: 100px;\" onkeypress=\"if(event.keyCode==13) submitSigninForm();\">\n";
	responseStream << "\t\t\t\t\t<!--<a class=\"topbar\" href=\"/Login\">Sign In</a>-->\n";
	responseStream << "\t\t\t\t\t<a class=\"topbar\" href=\"javascript:submitSigninForm()\">Log in</a>\n";
	responseStream << "\t\t\t\t\t<a class=\"topbar\" href=\"/Registration\">Sign up</a>\n";
	responseStream << "\t\t\t\t</span>\n";
	responseStream << "\t\t\t</div>\n";
	responseStream << "\t\t</form>\n";
	responseStream << "\t";
#line 24 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/topbar.html"
ENDIF	responseStream << "\n";
	responseStream << "";
	// end include src/view/tile/topbar.html
	responseStream << "";
#line 15 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 16 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
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
#line 9 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/header.html"
	responseStream << (NAME(query));
	responseStream << " placeholder=\"Search...\" style=\"width: 170px;\" onkeypress=\"if(event.keyCode==13) submitSearchForm();\">\n";
	responseStream << "\t\t\t\t<a class=\"toolbar\" href=\"javascript:submitSearchForm()\">Find</a>\n";
	responseStream << "\t\t\t</span>\n";
	responseStream << "\t\t</div>\n";
	responseStream << "\t</form>\t\n";
	responseStream << "";
	// end include src/view/tile/header.html
	responseStream << "";
#line 16 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 17 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_BEGIN("menu")	responseStream << "";
	// begin include src/view/tile/menu.html
	responseStream << "\n";
	responseStream << "\t<ul id=\"menu\">\n";
	responseStream << "\t\t";
#line 3 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/menu.html"
FOREACH(entry, me.menu())	responseStream << "\n";
	responseStream << "\t\t\t<li><a href=\"";
#line 4 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/menu.html"
	responseStream << (entry.url);
	responseStream << "\" ";
#line 4 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/menu.html"
	responseStream << (me.checkPath(entry.url) ? "class='active'" : "");
	responseStream << "><span>";
#line 4 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/menu.html"
	responseStream << (entry.title);
	responseStream << "</span></a></li>\n";
	responseStream << "\t\t";
#line 5 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/menu.html"
ENDFOR	responseStream << "\n";
	responseStream << "\t</ul>\n";
	responseStream << "";
	// end include src/view/tile/menu.html
	responseStream << "";
#line 17 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 19 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_BEGIN("content")	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- Paginator -->\n";
	responseStream << "\t\t";
#line 22 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
COPY_BEGIN("paginator")	responseStream << "\n";
	responseStream << "\t\t\t<div class=\"userCol1\">\n";
	responseStream << "\t\t\t\t<a class=\"paginatorChain\" href=\"*paginate?p=";
#line 24 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (me.paginator.first());
	responseStream << "\">First</a>\n";
	responseStream << "\t\t\t\t<a class=\"paginatorChain\" href=\"*paginate?p=";
#line 25 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (me.paginator.prev());
	responseStream << "\">Prev</a>\n";
	responseStream << "\t\t\t\t";
#line 26 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
FOREACH(ind, me.paginator.indices)	responseStream << "\n";
	responseStream << "\t\t\t\t\t<a class=\"paginatorChain";
#line 27 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (ind==me.paginator.page()?" paginatorCurrent":"");
	responseStream << "\" href=\"*paginate?p=";
#line 27 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (ind);
	responseStream << "\">";
#line 27 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (ind);
	responseStream << "</a>\n";
	responseStream << "\t\t\t\t";
#line 28 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
ENDFOR	responseStream << "\n";
	responseStream << "\t\t\t\t<a class=\"paginatorChain\" href=\"*paginate?p=";
#line 29 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (me.paginator.next());
	responseStream << "\">Next</a>\n";
	responseStream << "\t\t\t\t<a class=\"paginatorChain\" href=\"*paginate?p=";
#line 30 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (me.paginator.last());
	responseStream << "\">Last</a>\n";
	responseStream << "\t\t\t</div>\n";
	responseStream << "\t\t";
#line 32 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
COPY_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- User settings mode -->\n";
	responseStream << "\t\t";
#line 36 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
IF(me.mode() == me.MODE_SETTINGS)	responseStream << "\n";
	responseStream << "\t\t\t";
#line 37 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
IF(user)	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t";
#line 39 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
IF(user.group() == user.ADMIN)	responseStream << "\n";
	responseStream << "\t\t\t\t\t<a class=\"paginatorChain\" href=\"";
#line 40 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (page.path());
	responseStream << "?m=users\">&gt; Administer &lt;</a>\n";
	responseStream << "\t\t\t\t";
#line 41 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<h1>Settings</h1>\n";
	responseStream << "\t\t\t\t<form method=\"POST\" action=\"*updateUser\">";
#line 44 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\">FirstName:</div><div class=\"userCol2\"><input type=\"text\" ";
#line 45 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (NAME(firstName));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\">LastName:</div><div class=\"userCol2\"><input type=\"text\" ";
#line 46 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (NAME(lastName));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\">PhoneNumber:</div><div class=\"userCol2\"><input type=\"text\" ";
#line 47 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (NAME(phoneNumber));
	responseStream << "></div>\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\">Country:</div><div class=\"userCol2\"><select id=\"country\" ";
#line 49 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (NAME(country));
	responseStream << "></select></div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\">State:</div><div class=\"userCol2\"><select id=\"state\" ";
#line 50 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (NAME(state));
	responseStream << "></select></div>\n";
	responseStream << "\t\t\t\t\t<script type=\"text/javascript\">populateCountries(\"country\", \"state\", \"";
#line 51 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (me["country"]);
	responseStream << "\", \"";
#line 51 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (me["state"]);
	responseStream << "\");</script>\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\">Birthday:</div><div class=\"userCol2\"><input type=\"text\" id=\"date\" ";
#line 53 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (NAME(birthday));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t\t<script type=\"text/javascript\">calendar.set(\"date\");</script>\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\"></div><div class=\"userCol2\"><input type=\"submit\" value=\"Update\"></div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userStatus\"><span class=\"userError\">";
#line 57 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (me["status"]);
	responseStream << "</span></div>\n";
	responseStream << "\t\t\t\t</form>\n";
	responseStream << "\t\t\t";
#line 59 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
ELSE	responseStream << "\n";
	responseStream << "\t\t\t\t<h1>Please register.</h1>\n";
	responseStream << "\t\t\t";
#line 61 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
ENDIF	responseStream << "\n";
	responseStream << "\t\t";
#line 62 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- User listing mode -->\n";
	responseStream << "\t\t";
#line 66 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
IF(me.mode() == me.MODE_USERS)	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t<a class=\"paginatorChain\" href=\"";
#line 68 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (page.path());
	responseStream << "\">&gt; Return to Settings &lt;</a>\n";
	responseStream << "\n";
	responseStream << "\t\t\t<p>\n";
	responseStream << "\t\t\t\t<!-- Draw paginator -->\n";
	responseStream << "\t\t\t\t";
#line 72 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
PASTE("paginator")	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Print table of Users -->\n";
	responseStream << "\t\t\t\t<div class=\"AdminUsersContainer\">\n";
	responseStream << "\t\t\t\t\t";
#line 76 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TABLE(cell, me.userTable)	responseStream << "\n";
	responseStream << "\t\t\t\t\t\t";
#line 77 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
	responseStream << (cell);
	responseStream << "\n";
	responseStream << "\t\t\t\t\t";
#line 78 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
ENDTABLE	responseStream << "\n";
	responseStream << "\t\t\t\t</div>\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Remove user btn -->\n";
	responseStream << "\t\t\t\t<a class=\"postRowOptionR\" href=\"*removeUser\" onclick=\n";
	responseStream << "\t\t\t\t\t\"return confirm('Are you sure you want to remove this user?');\"><i>Remove</i></a>\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Change user group list -->\n";
	responseStream << "\t\t\t\t<div class=\"postRowOptionR\">\n";
	responseStream << "\t\t\t\t\t<select onchange=\"location = '*updateGroup?g='.concat(this.value);\">\n";
	responseStream << "\t\t\t\t\t\t";
#line 88 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
OPTIONS(me.userGroups)	responseStream << "\n";
	responseStream << "\t\t\t\t\t</select>\n";
	responseStream << "\t\t\t\t</div>\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Draw paginator -->\n";
	responseStream << "\t\t\t\t";
#line 93 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
PASTE("paginator")	responseStream << "\n";
	responseStream << "\t\t\t</p>\n";
	responseStream << "\t\t";
#line 95 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 97 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 99 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_BEGIN("navigation")	responseStream << "";
	// begin include src/view/tile/navigation.html
	responseStream << "\n";
	responseStream << "\t<div id=\"toolbar\">\n";
	responseStream << "\t</div>\n";
	responseStream << "\t<ul id=\"list\">\n";
	responseStream << "\t\t";
#line 5 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/navigation.html"
FOREACH(entry, me.sidebar())	responseStream << "\n";
	responseStream << "\t\t\t<li><a href=\"";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/navigation.html"
	responseStream << (entry.url);
	responseStream << "\" ";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/navigation.html"
	responseStream << (me.checkPath(entry.url) ? "class='active'" : "");
	responseStream << "><span>";
#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/navigation.html"
	responseStream << (entry.title);
	responseStream << "</span></a></li>\n";
	responseStream << "\t\t";
#line 7 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/tile/navigation.html"
ENDFOR	responseStream << "\n";
	responseStream << "\t</ul>\n";
	responseStream << "";
	// end include src/view/tile/navigation.html
	responseStream << "";
#line 99 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 100 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_BEGIN("footer")	responseStream << "";
	// begin include src/view/tile/footer.html
	responseStream << "\t\n";
	responseStream << "\t<span>Copyright © 2015 [There could be your company].</span>\n";
	responseStream << "";
	// end include src/view/tile/footer.html
	responseStream << "";
#line 100 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 102 "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.c"
TEMPLATE("html/template.html")	responseStream << "\n";
	responseStream << "";
}
