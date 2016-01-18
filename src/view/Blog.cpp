#include "Blog.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"


#include "core/Tag.h"
#include "ctrl/form/Blog.h"
#line 4 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PAGE(Blog, CLASS(ctrl::form::Blog))

void BlogHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");

#line 6 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
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
#line 8 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
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
	responseStream << "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"markitup/skins/markitup/style.css\" />\n";
	responseStream << "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"markitup/sets/bbcode/style.css\" />\n";
	responseStream << "\t\t<script type=\"text/javascript\" src=\"js/jquery-1.4.3.min.js\"></script>\n";
	responseStream << "\t\t<script type=\"text/javascript\" src=\"markitup/jquery.markitup.js\"></script>\n";
	responseStream << "\t\t<script type=\"text/javascript\" src=\"markitup/sets/bbcode/set.js\"></script>\n";
	responseStream << "\t\t<script language=\"javascript\">\n";
	responseStream << "\t\t$(document).ready(function()\t{\n";
	responseStream << "\t\t\t$('#bbcode_blog').markItUp(myBbcodeSettings);\n";
	responseStream << "\t\t\t$('#emoticons a').click(function() {\n";
	responseStream << "\t\t\t\temoticon = $(this).attr(\"title\");\n";
	responseStream << "\t\t\t\t$.markItUp( { replaceWith:emoticon } );\n";
	responseStream << "\t\t\t});\n";
	responseStream << "\t\t});\n";
	responseStream << "\t\t</script>\n";
	responseStream << "\t";
#line 24 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 26 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
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
#line 26 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 27 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
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
#line 27 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 28 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
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
#line 28 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 30 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TILE_BEGIN("content")	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- Create categories chain -->\n";
	responseStream << "\t\t<a class=\"categoryChain\" href=\"";
#line 33 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (page.path());
	responseStream << "?c=0\">root</a>\n";
	responseStream << "\t\t";
#line 34 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
FOREACHI(cat, me.categoryChain)	responseStream << "\n";
	responseStream << "\t\t\t : <a class=\"categoryChain\" href=\"";
#line 35 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (page.path());
	responseStream << "?c=";
#line 35 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (cat.id());
	responseStream << "\">";
#line 35 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.format(cat.title()));
	responseStream << "</a>\n";
	responseStream << "\t\t";
#line 36 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDFOR	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- Sorting method selector -->\n";
	responseStream << "\t\t";
#line 39 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
COPY_BEGIN("sortingMethodSelector")	responseStream << "\n";
	responseStream << "\t\t\t<div class=\"userCol1\">Sort by</div><div class=\"userCol2\">\n";
	responseStream << "\t\t\t\t<select onchange=\"location = '*paginate?s='.concat(this.value);\">\n";
	responseStream << "\t\t\t\t\t";
#line 42 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
OPTIONS(me.sortModes)	responseStream << "\n";
	responseStream << "\t\t\t\t</select>\n";
	responseStream << "\t\t\t</div>\n";
	responseStream << "\t\t";
#line 45 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
COPY_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- Paginator -->\n";
	responseStream << "\t\t";
#line 48 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
COPY_BEGIN("paginator")	responseStream << "\n";
	responseStream << "\t\t\t<div class=\"userCol1\">\n";
	responseStream << "\t\t\t\t<a class=\"paginatorChain\" href=\"*paginate?p=";
#line 50 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.paginator.first());
	responseStream << "\">First</a>\n";
	responseStream << "\t\t\t\t<a class=\"paginatorChain\" href=\"*paginate?p=";
#line 51 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.paginator.prev());
	responseStream << "\">Prev</a>\n";
	responseStream << "\t\t\t\t";
#line 52 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
FOREACH(ind, me.paginator.indices)	responseStream << "\n";
	responseStream << "\t\t\t\t\t<a class=\"paginatorChain";
#line 53 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (ind==me.paginator.page()?" paginatorCurrent":"");
	responseStream << "\" href=\"*paginate?p=";
#line 53 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (ind);
	responseStream << "\">";
#line 53 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (ind);
	responseStream << "</a>\n";
	responseStream << "\t\t\t\t";
#line 54 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDFOR	responseStream << "\n";
	responseStream << "\t\t\t\t<a class=\"paginatorChain\" href=\"*paginate?p=";
#line 55 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.paginator.next());
	responseStream << "\">Next</a>\n";
	responseStream << "\t\t\t\t<a class=\"paginatorChain\" href=\"*paginate?p=";
#line 56 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.paginator.last());
	responseStream << "\">Last</a>\n";
	responseStream << "\t\t\t</div>\n";
	responseStream << "\t\t";
#line 58 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
COPY_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- Emoticons -->\n";
	responseStream << "\t\t";
#line 61 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
COPY_BEGIN("emoticons")	responseStream << "\n";
	responseStream << "\t\t\t<div id=\"emoticons\">\n";
	responseStream << "\t\t\t\t";
#line 63 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
FOREACH(emo, core::server().conf().emoticons())	responseStream << "\n";
	responseStream << "\t\t\t\t\t<a href=\"#\" onclick=\"return false;\" title=\"";
#line 64 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (emo.name);
	responseStream << "\"><img src=\"";
#line 64 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (emo.src);
	responseStream << "\" /></a>\n";
	responseStream << "\t\t\t\t";
#line 65 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDFOR	responseStream << "\n";
	responseStream << "\t\t\t</div>\n";
	responseStream << "\t\t";
#line 67 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
COPY_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- Search Results mode -->\n";
	responseStream << "\t\t";
#line 71 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(me.mode() == me.MODE_SEARCH)	responseStream << "\n";
	responseStream << "\t\t\t";
#line 72 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(me.searchResults->size())	responseStream << "\n";
	responseStream << "\t\t\t\t<h1>Search Results:</h1>\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Add sorting method selector -->\n";
	responseStream << "\t\t\t\t";
#line 76 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PASTE("sortingMethodSelector")	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Print list of Search Results -->\n";
	responseStream << "\t\t\t\t";
#line 79 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
FOREACH(blog, me.searchResults)	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"blogListRow\">\n";
	responseStream << "\t\t\t\t\t\t<a class=\"postRowWhole\" href=\"";
#line 81 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (page.path());
	responseStream << "?b=";
#line 81 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (blog.id());
	responseStream << "\">";
#line 81 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (blog.title());
	responseStream << "</a>\n";
	responseStream << "\t\t\t\t\t</div>\n";
	responseStream << "\t\t\t\t";
#line 83 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDFOR	responseStream << "\n";
	responseStream << "\t\t\t";
#line 84 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ELSE	responseStream << "\n";
	responseStream << "\t\t\t\t<h1>Nothing Found</h1>\n";
	responseStream << "\t\t\t\tSorry, but nothing matched your search criteria.\n";
	responseStream << "\t\t\t";
#line 87 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Show more results button -->\n";
	responseStream << "\t\t\t";
#line 90 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(me.paginator.hasMore())	responseStream << "\n";
	responseStream << "\t\t\t\t<form method=\"POST\" action=\"*paginate\">";
#line 91 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\"><input type=\"submit\" value=\"Show More\"></div><div class=\"userCol2\"></div>\n";
	responseStream << "\t\t\t\t</form>\n";
	responseStream << "\t\t\t";
#line 94 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\t\t";
#line 95 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- Blog mode -->\n";
	responseStream << "\t\t";
#line 99 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(me.mode() == me.MODE_BLOG)	responseStream << "\n";
	responseStream << "\t\t\t<!-- Add blog node to category chain -->\n";
	responseStream << "\t\t\t : ";
#line 101 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.format(me.blog.title()));
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Pring blog title, date, username, rating and content -->\n";
	responseStream << "\t\t\t<h1>";
#line 104 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.format(me.blog.title()));
	responseStream << "</h1>\n";
	responseStream << "\t\t\t<i><b>Posted: </b>";
#line 105 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (core::to_string(me.blog.date()));
	responseStream << " by ";
#line 105 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.blog.post().user().username());
	responseStream << "</i>\n";
	responseStream << "\t\t\t<br /><a class=\"postRowValue\" href=\"*ratePost?p=";
#line 106 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.blog.post().id());
	responseStream << "\">";
#line 106 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.blog.post().rated() ? "&#x2935" : "&#x2934");
	responseStream << "+";
#line 106 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.blog.post().rating());
	responseStream << "</a>\n";
	responseStream << "\t\t\t";
#line 107 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(user.group() == user.ADMIN)	responseStream << "\n";
	responseStream << "\t\t\t\t<div>\n";
	responseStream << "\t\t\t\t\t<a class=\"postRowOptionR\" href=\"*removeBlog?b=";
#line 109 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.blog.id());
	responseStream << "\" onclick=\n";
	responseStream << "\t\t\t\t\t\t\"return confirm('Are you sure you want to remove this blog?');\"><i>Remove</i></a>\n";
	responseStream << "\t\t\t\t\t<a class=\"postRowOptionR\" href=\"#\" onclick=\"createEditBlogBlock(this.parentNode, ";
#line 111 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.blog.id());
	responseStream << ", ";
#line 111 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.blog.post().id());
	responseStream << "); return false;\"><i>Edit</i></a>\n";
	responseStream << "\t\t\t\t</div>\n";
	responseStream << "\t\t\t";
#line 113 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\t\t\t<br />";
#line 114 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.format(me.blog.post().content(), true));
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Add sorting method selector -->\n";
	responseStream << "\t\t\t";
#line 117 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PASTE("sortingMethodSelector")	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Add Comment button -->\n";
	responseStream << "\t\t\t<form method=\"POST\" action=\"#\">";
#line 120 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t<div class=\"userCol1\"><input type=\"submit\" value=\"Add Comment\" onclick=\"createReplyBlock(null, 0, ''); deleteThis(this); return false;\"></div>\n";
	responseStream << "\t\t\t\t<div class=\"userCol2\"></div>\n";
	responseStream << "\t\t\t</form>\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Container for cloning Reply Section into -->\n";
	responseStream << "\t\t\t<div id=\"replyBlockRoot\"></div>\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Print Comments tree -->\n";
	responseStream << "\t\t\t";
#line 129 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TREE_FOREACH(post, me.posts)	responseStream << "\n";
	responseStream << "\t\t\t\t<div class='";
#line 130 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (post.parentId() ? "postChildRow" : "postRow");
	responseStream << "'>\n";
	responseStream << "\t\t\t\t\t<i><b>Posted: </b>";
#line 131 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (core::to_string(post.date()));
	responseStream << " by ";
#line 131 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (post.user().username());
	responseStream << "</i>\n";
	responseStream << "\t\t\t\t\t<br />";
#line 132 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.format(post.content()));
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<br /><a class=\"postRowValue\" href=\"*ratePost?p=";
#line 133 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (post.id());
	responseStream << "\">";
#line 133 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (post.rated() ? "&#x2935" : "&#x2934");
	responseStream << "+";
#line 133 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (post.rating());
	responseStream << "</a>\n";
	responseStream << "\t\t\t\t\t<a class=\"postRowValue\" href=\"#\" onclick=\"createReplyBlock(this.parentNode, ";
#line 134 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (post.id());
	responseStream << ", '";
#line 134 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (post.user().username());
	responseStream << "'); return false;\"><i>Reply</i></a>\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t\t";
#line 136 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(user.id() == post.user().id() || user.group() == user.ADMIN)	responseStream << "\n";
	responseStream << "\t\t\t\t\t\t<div>\n";
	responseStream << "\t\t\t\t\t\t\t<a class=\"postRowOptionR\" href=\"*removePost?p=";
#line 138 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (post.id());
	responseStream << "\" onclick=\n";
	responseStream << "\t\t\t\t\t\t\t\t\"return confirm('Are you sure you want to remove this comment?');\"><i>Remove</i></a>\n";
	responseStream << "\t\t\t\t\t\t\t<a class=\"postRowOptionR\" href=\"#\" onclick=\"createEditBlock(this.parentNode, ";
#line 140 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (post.id());
	responseStream << "); return false;\"><i>Edit</i></a>\n";
	responseStream << "\t\t\t\t\t\t</div>\n";
	responseStream << "\t\t\t\t\t";
#line 142 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t\t";
#line 144 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TREE_CHILDREN	responseStream << "\n";
	responseStream << "\t\t\t\t</div>\n";
	responseStream << "\t\t\t";
#line 146 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TREE_ENDFOR	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Show more comments button -->\n";
	responseStream << "\t\t\t";
#line 149 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(me.paginator.hasMore())	responseStream << "\n";
	responseStream << "\t\t\t\t<form method=\"POST\" action=\"*paginate\">";
#line 150 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\"><input type=\"submit\" value=\"Show More\"></div><div class=\"userCol2\"></div>\n";
	responseStream << "\t\t\t\t</form>\n";
	responseStream << "\t\t\t";
#line 153 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Reply Section template (Invisible, for clonning only) -->\n";
	responseStream << "\t\t\t<div id=\"replyBlock\" style=\"display: none;\">\n";
	responseStream << "\t\t\t\t<form method=\"POST\" action=\"*newPost\">";
#line 158 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<input type=\"hidden\" class=\"ParentPostIdPar\" ";
#line 159 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (NAME(pp));
	responseStream << ">\n";
	responseStream << "\t\t\t\t\t";
#line 160 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(!user)	responseStream << "<div class=\"userCol1\">Email Address:</div><div class=\"userCol2\"><input type=\"text\" ";
#line 160 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (NAME(email));
	responseStream << "></div>";
#line 160 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"userStatus\"><textarea name=\"content\" class=\"ParentPostContent\">";
#line 161 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me["content"]);
	responseStream << "</textarea></div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\"><!-- Add Emoticons -->";
#line 162 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PASTE("emoticons")	responseStream << "</div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol2\"><input type=\"submit\" class=\"ParentPostCancel\" onclick=\"deleteHtmlBlock(this); return false;\" value=\"Cancel\">\n";
	responseStream << "\t\t\t\t\t\t<input type=\"submit\" value=\"Add Comment\"></div>\n";
	responseStream << "\t\t\t\t</form>\n";
	responseStream << "\t\t\t\t<div class=\"userStatus\"><span class=\"userError\">";
#line 166 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me["status"]);
	responseStream << "</span></div>\n";
	responseStream << "\t\t\t</div>\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Edit Comment Section template (Invisible, for clonning only) -->\n";
	responseStream << "\t\t\t<div id=\"editBlock\" style=\"display: none;\">\n";
	responseStream << "\t\t\t\t<form method=\"POST\" action=\"*editPost\">";
#line 171 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<input type=\"hidden\" class=\"ParentPostIdPar\" ";
#line 172 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (NAME(p));
	responseStream << ">\n";
	responseStream << "\t\t\t\t\t<div class=\"userStatus\"><textarea name=\"content\" class=\"ParentPostContent\">";
#line 173 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me["content"]);
	responseStream << "</textarea></div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\"><!-- Add Emoticons -->";
#line 174 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PASTE("emoticons")	responseStream << "</div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol2\"><input type=\"submit\" class=\"ParentPostCancel\" onclick=\"deleteHtmlBlock(this); return false;\" value=\"Cancel\">\n";
	responseStream << "\t\t\t\t\t\t<input type=\"submit\" value=\"Save\"></div>\n";
	responseStream << "\t\t\t\t</form>\n";
	responseStream << "\t\t\t\t<div class=\"userStatus\"><span class=\"userError\">";
#line 178 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me["status"]);
	responseStream << "</span></div>\n";
	responseStream << "\t\t\t</div>\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- Edit Blog Section template (Invisible, for clonning only) -->\n";
	responseStream << "\t\t\t<div id=\"editBlogBlock\" style=\"display: none;\">\n";
	responseStream << "\t\t\t\t<form method=\"POST\" action=\"*editBlog\">";
#line 183 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t\t<input type=\"hidden\" class=\"ParentPostIdPar\" ";
#line 184 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (NAME(b));
	responseStream << ">\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\">Title:</div><div class=\"userCol2\"><input type=\"text\" class=\"EditBlogTitle\" ";
#line 185 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (NAME(title));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userStatus\"><textarea name=\"content\" class=\"ParentPostContent\">";
#line 186 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me["content"]);
	responseStream << "</textarea></div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol1\"><!-- Add Emoticons -->";
#line 187 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PASTE("emoticons")	responseStream << "</div>\n";
	responseStream << "\t\t\t\t\t<div class=\"userCol2\"><input type=\"submit\" class=\"ParentPostCancel\" onclick=\"deleteHtmlBlock(this); return false;\" value=\"Cancel\">\n";
	responseStream << "\t\t\t\t\t\t<input type=\"submit\" value=\"Save\"></div>\n";
	responseStream << "\t\t\t\t</form>\n";
	responseStream << "\t\t\t\t<div class=\"userStatus\"><span class=\"userError\">";
#line 191 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me["status"]);
	responseStream << "</span></div>\n";
	responseStream << "\t\t\t</div>\n";
	responseStream << "\t\t";
#line 193 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t<!-- Blog/Category listing mode -->\n";
	responseStream << "\t\t";
#line 197 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(me.mode() == me.MODE_CATEGORY)	responseStream << "\n";
	responseStream << "\t\t\t<p>\n";
	responseStream << "\t\t\t\t<!-- Add sorting method selector -->\n";
	responseStream << "\t\t\t\t";
#line 200 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PASTE("sortingMethodSelector")	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Draw paginator -->\n";
	responseStream << "\t\t\t\t";
#line 203 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PASTE("paginator")	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Print list of Categories -->\n";
	responseStream << "\t\t\t\t";
#line 206 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
FOREACH(cat, me.categories)	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"categoryListRow\">\n";
	responseStream << "\t\t\t\t\t\t<a class=\"postRowWhole\" href=\"";
#line 208 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (page.path());
	responseStream << "?c=";
#line 208 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (cat.id());
	responseStream << "\">";
#line 208 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.format(cat.title()));
	responseStream << "</a>\n";
	responseStream << "\t\t\t\t\t\t";
#line 209 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(user.group() == user.ADMIN)	responseStream << "\n";
	responseStream << "\t\t\t\t\t\t\t<a class=\"postRowOption\" href=\"*removeCategory?c=";
#line 210 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (cat.id());
	responseStream << "\" onclick=\n";
	responseStream << "\t\t\t\t\t\t\t\t\"return confirm('Are you sure you want to remove this category?');\"><i>Remove</i></a>\n";
	responseStream << "\t\t\t\t\t\t";
#line 212 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\t\t\t\t\t</div>\n";
	responseStream << "\t\t\t\t";
#line 214 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDFOR	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Print list of Blogs -->\n";
	responseStream << "\t\t\t\t";
#line 217 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
FOREACH(blog, me.blogs)	responseStream << "\n";
	responseStream << "\t\t\t\t\t<div class=\"blogListRow\">\n";
	responseStream << "\t\t\t\t\t\t<a class=\"postRowWhole\" href=\"";
#line 219 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (page.path());
	responseStream << "?b=";
#line 219 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (blog.id());
	responseStream << "\">";
#line 219 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me.format(blog.title()));
	responseStream << "</a>\n";
	responseStream << "\t\t\t\t\t\t";
#line 220 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(user.group() == user.ADMIN)	responseStream << "\n";
	responseStream << "\t\t\t\t\t\t\t<a class=\"postRowOption\" href=\"*removeBlog?b=";
#line 221 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (blog.id());
	responseStream << "\" onclick=\n";
	responseStream << "\t\t\t\t\t\t\t\t\"return confirm('Are you sure you want to remove this blog?');\"><i>Remove</i></a>\n";
	responseStream << "\t\t\t\t\t\t";
#line 223 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\t\t\t\t\t</div>\n";
	responseStream << "\t\t\t\t";
#line 225 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDFOR	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t<!-- Draw paginator -->\n";
	responseStream << "\t\t\t\t";
#line 228 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PASTE("paginator")	responseStream << "\n";
	responseStream << "\t\t\t</p>\n";
	responseStream << "\n";
	responseStream << "\t\t\t<!-- New Blog and New Category Sections -->\n";
	responseStream << "\t\t\t";
#line 232 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(user && user.group() == user.ADMIN)	responseStream << "\n";
	responseStream << "\t\t\t\t";
#line 233 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(!me.hasBlogs)	responseStream << "\n";
	responseStream << "\t\t\t\t\t<br /><br /><br />\n";
	responseStream << "\t\t\t\t\t<form method=\"POST\" action=\"*newCategory\">";
#line 235 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t\t\t<div class=\"userCol1\">Title:</div><div class=\"userCol2\"><input type=\"text\" ";
#line 236 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (NAME(title));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t\t\t<div class=\"userCol1\"></div><div class=\"userCol2\"><input type=\"submit\" value=\"Create new category\"></div>\n";
	responseStream << "\t\t\t\t\t</form>\n";
	responseStream << "\t\t\t\t";
#line 239 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t\t\t\t";
#line 241 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
IF(!me.hasCategories)	responseStream << "\n";
	responseStream << "\t\t\t\t\t<br /><br /><br />\n";
	responseStream << "\t\t\t\t\t<!--<textarea id=\"bbcode\" cols=\"80\" rows=\"20\"></textarea>-->\n";
	responseStream << "\t\t\t\t\t<form method=\"POST\" action=\"*newBlog\">";
#line 244 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (CSRF);
	responseStream << "\n";
	responseStream << "\t\t\t\t\t\t<div class=\"userCol1\">Title:</div><div class=\"userCol2\"><input type=\"text\" ";
#line 245 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (NAME(title));
	responseStream << "></div>\n";
	responseStream << "\t\t\t\t\t\t<div class=\"userStatus\"><textarea id=\"bbcode_blog\" name=\"content\">";
#line 246 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me["content"]);
	responseStream << "</textarea></div>\n";
	responseStream << "\t\t\t\t\t\t<div class=\"userCol1\"><!-- Add Emoticons -->";
#line 247 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
PASTE("emoticons")	responseStream << "</div>\n";
	responseStream << "\t\t\t\t\t\t<div class=\"userCol2\"><input type=\"submit\" value=\"Create new blog\"></div>\n";
	responseStream << "\t\t\t\t\t</form>\n";
	responseStream << "\t\t\t\t";
#line 250 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\t\t\t\t<div class=\"userStatus\"><span class=\"userError\">";
#line 251 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
	responseStream << (me["status"]);
	responseStream << "</span></div>\n";
	responseStream << "\t\t\t";
#line 252 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\t\t";
#line 253 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
ENDIF	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 255 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 257 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
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
#line 257 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TILE_END	responseStream << "\n";
	responseStream << "\t";
#line 258 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TILE_BEGIN("footer")	responseStream << "";
	// begin include src/view/tile/footer.html
	responseStream << "\t\n";
	responseStream << "\t<span>Copyright © 2015 [There could be your company].</span>\n";
	responseStream << "";
	// end include src/view/tile/footer.html
	responseStream << "";
#line 258 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TILE_END	responseStream << "\n";
	responseStream << "\n";
	responseStream << "\t";
#line 260 "/media/DATA_1/_/Data/Core/Developing/WebServer/PocoBlog/src/view/Blog.c"
TEMPLATE("html/template.html")	responseStream << "\n";
	responseStream << "";
}
