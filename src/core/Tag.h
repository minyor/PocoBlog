//
// Custom tags for facets
//
// Copyright (c) 2016, minyor.
//
// License:	BSD
//


#ifndef CORE_TAG_H
#define CORE_TAG_H


#include <core/Header.h>
#include <model/User.h>
#include <core/Page.h>
#include <core/Server.h>
#include <core/db/Sql.h>


#define __hide_handler_PAGE(_type, _handler) namespace core { namespace pages {\
	class Page##_handler : public core::Page {\
		public: Poco::Net::HTTPRequestHandler *newHandler() { return new _handler; }\
	};\
	struct Init##_handler {\
		static const char *path;\
		static NewClass newClass;\
		static void init() {\
			core::Page *page = new Page##_handler;\
			page->path(path ? std::string(path) : std::string("/") + #_type);\
			page->newClass(newClass); server().addPage(page);\
		}\
		Init##_handler() { server().addInit(&init); }\
	}; const char *Init##_handler::path = NULL; NewClass Init##_handler::newClass = NULL;\
	static Init##_handler __initPageHandler;\
}}

#define PAGE(_type, ...) __hide_handler_PAGE(_type, _type##Handler) __VA_ARGS__ \
namespace core { namespace pages { typedef __hide_PageClass __hide_UsePageClass; }}

#define PATH(_path) static const char *initPagePath = (core::pages::__initPageHandler.path = _path);


typedef core::Form __hide_PageClass;
#define CLASS(_type) namespace core { namespace pages {\
	typedef _type __hide_PageClass;\
	static void *__hide_handler_newClass() { return new _type; }\
	static bool __hide_handler_init_newClass() { core::pages::__initPageHandler.newClass = &__hide_handler_newClass; return true; }\
	static bool __initClassHandler = __hide_handler_init_newClass();\
}}


#define SESSION\
	auto mePtr = core::server().session(request, response);\
	auto &me = (core::pages::__hide_UsePageClass &)mePtr->form();\
	auto &ctrl = me.ctrl();\
	auto &user = ctrl.user();\
	auto &page = ctrl.page();\
	core::TemplateMap templateMap;\
	core::TemplateMap instanceMap;\
	(void)ctrl; (void)me; (void)user; (void)page; (void)templateMap; (void)instanceMap;


#define NAME(_name) me.htmlTagPar(#_name)
#define CSRF me.htmlCSRF()


#define IF(_cond) if(_cond) {
#define ELIF(_cond) } else if(_cond) {
#define ELSE } else {
#define ENDIF }


#define FOREACH(_var, _in) { auto cont = _in; for(std::int64_t i=0; i<cont->size(); ++i) { auto &_var = *cont()[i];
#define FOREACHI(_var, _in) { auto cont = _in; for(std::int64_t i=cont->size(); i>0; --i) { auto &_var = *cont()[i - 1];
#define ENDFOR } }


#define TREE_FOREACH(_var, _in) { auto cont = _in; typedef __hide_tree_node<__hide_type_unref<decltype(cont)>::Type> T;\
	std::stack<T> stack; stack.push(T(&cont));\
	for(auto *s = &stack.top(); !stack.empty(); s = &stack.top()) { ++s->ind;\
		if(s->ind >= s->tree->me().size()) { stack.pop(); if(s->tree == &cont) continue; }\
		else { auto &_var = *s->tree->me()[s->ind];
#define TREE_CHILDREN\
			if(s->tree->me()[s->ind].children) { stack.push(T(&s->tree->me()[s->ind].children)); continue; }\
		}
#define TREE_ENDFOR } }


#define TILE_BEGIN(_name) {\
	templateMap[_name] = std::shared_ptr<core::TemplateStream>(new core::TemplateStream);\
	auto &responseStream = *templateMap[_name];
#define TILE_END }
#define TEMPLATE(_path) me.htmlTemplate(_path, __FILE__, templateMap, responseStream);


#define COPY_BEGIN(_name) {\
	instanceMap[_name] = std::shared_ptr<core::TemplateStream>(new core::TemplateStream);\
	auto &responseStream = *instanceMap[_name];
#define COPY_END }
#define PASTE(_name) me.htmlInstance(_name, __FILE__, instanceMap, responseStream);


#define OPTIONS(_list) { auto list = _list;\
						IF(list.selected.empty())\
	responseStream << "		<option value=\"\" selected='selected'>" << list.prompt << "</option>";\
						ENDIF\
						FOREACH(row, list.rows)\
	responseStream << "		<option value=\"" << row.value << "\" " << ((!list.selected.empty() && list.selected==row.value)?"selected='selected'":"") << ">" << row.title << "</option>";\
						ENDFOR\
}


#define TABLE(_cell, _tbl) { auto tbl = _tbl;\
	responseStream << "	<table>";\
							IF(tbl.showHeader())\
	responseStream << "			<tr>";\
									IF(tbl.showCheckboxes())\
	responseStream << "					<th><input type='checkbox' " << (tbl.rowsChecked()?"checked='checked'":"") << " onclick=\"location = '*selectUser?a=1';\"></th>";\
									ENDIF\
									FOREACH(column, tbl.header)\
										IF(!tbl.hideEmptyCollumns() || !column.empty())\
	responseStream << "						<th><a href=\"*paginate?s=" << (abs(tbl.sort())==(i+1)?-tbl.sort():(i+1)) << "\">";\
	responseStream << "							" << column << (abs(tbl.sort())==(i+1)?(tbl.sort()<0?"&#x2191":"&#x2193"):"");\
	responseStream << "						</a></th>";\
										ENDIF\
									ENDFOR\
	responseStream << "			</tr>";\
							ENDIF\
							FOREACH(row, tbl.rows)\
	responseStream << "			<tr>";\
									IF(tbl.showCheckboxes())\
	responseStream << "					<td><input type='checkbox' " << (row.checked?"checked='checked'":"") << " onclick=\"location = '*selectUser?r=" << i << "';\"></td>";\
									ENDIF\
									FOREACH(_cell, row.data)\
										IF(!tbl.hideEmptyCollumns() || !tbl.header()[i]->empty())\
	responseStream << "						<td>";
#define ENDTABLE\
	responseStream << "						</td>";\
										ENDIF\
									ENDFOR\
	responseStream << "			</tr>";\
							ENDFOR\
	responseStream << "	</table>";\
}


template<typename T> struct __hide_tree_node { T *tree; size_t ind;
	__inline __hide_tree_node(T *tree = NULL) : tree(tree), ind(size_t(-1)) {}
};


#endif // CORE_TAG_H
