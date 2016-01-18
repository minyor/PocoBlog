//
// Some simple web components
// like paginator, table or captcha
//
// Copyright (c) 2016, minyor.
//
// License:	BSD
//


#include <Poco/Random.h>
#include <Poco/Crypto/RSADigestEngine.h>
#include <Poco/SharedPtr.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/MailMessage.h>

#include <sstream>
#include <iomanip>

#include <core/Header.h>
#include <core/Facet.h>


using namespace core::facet;


CaptchaCalc::CaptchaCalc()
{
	refresh();
}
CaptchaCalc::~CaptchaCalc()
{
}
void CaptchaCalc::refresh(std::uint32_t base1, std::uint32_t base2)
{
	Poco::Random random; random.seed();
	std::uint32_t v1 = random.next(base1 - 1) + 1;
	std::uint32_t v2 = random.next(base2 - 1) + 1;
	_name = util::Hash::salt(5);
	_num1 = std::to_string(v1);
	_num2 = std::to_string(v2);
	_sum = std::to_string(v1 + v2);
}
std::string CaptchaCalc::htmlUse()
{
	return std::string("\
		<script type='text/javascript'>\
			function userAddValidation(question)\
			{\
				var scriptTag = document.getElementsByTagName('script');\
				var parent = scriptTag[scriptTag.length - 1].parentNode;\
				parent.innerHTML = '';\
				if(question === true) parent.innerHTML = '" + num1() + " + " + num2() + " = ';\
				else {\
					var input = document.createElement('input');\
					input.type = 'text'; input.name = '" + name() + "'; input.style.width = 40;\
					parent.appendChild(input);\
				}\
			}\
		</script>\
	");
}
std::string CaptchaCalc::htmlQuestion()
{
	return "<script type='text/javascript'>userAddValidation(true);</script>";
}
std::string CaptchaCalc::htmlAnswer()
{
	return "<script type='text/javascript'>userAddValidation(false);</script>";
}


Paginator::Paginator()
{
	_limit = 10;
	_offset = 0;
	v_limit = _limit;
	v_offset = _offset;
	_rowsCount = 1;
	_sides = 3;

	_pages = 1;
	_pageChanged = false;
	reset();
}
Paginator::~Paginator()
{
}
void Paginator::reset()
{
	if(_pageChanged) return;
	_page = 0;
}
void Paginator::doPaging(std::int64_t rowsCount, std::int64_t limit)
{
	if(_pages == INTMAX(32)) reset();
	_pageChanged = false;

	_rowsCount = rowsCount;
	_limit = v_limit = limit == INTMAX(64) ? _limit : (limit < 1 ? 1 : limit);

	_pages = (_rowsCount > 0 ? _rowsCount - 1 : _rowsCount) / _limit + 1;
	//_page = _page < _pages ? _page : (_pages-1);
	_offset = v_offset = _limit * _page;

	_first = 0;
	_last = _pages - 1;
	_prev = _page - 1; _prev = _prev < _first ? _first : _prev;
	_next = _page + 1; _next = _next < _pages ? _next : _last;
	_first += 1; _last += 1; _prev += 1; _next += 1;

	std::int32_t indCount = _sides * 2 + 1, firstInd = _page - _sides, lastInd = firstInd + indCount;
	if(firstInd < 0) { indCount -= (0 - firstInd); firstInd = 0; }
	if(lastInd > _pages) { indCount -= (lastInd - _pages); }
	indices = NULL;
	for(std::int32_t i=0; i<indCount; ++i) indices.add(new std::int32_t(firstInd + i + 1));
}
void Paginator::doExtending(std::int64_t rowsCount, std::int64_t limit)
{
	if(_pages != INTMAX(32)) reset();
	_pageChanged = false;

	std::int64_t oldRowsCount = _rowsCount;
	_rowsCount = rowsCount;
	_limit = limit == INTMAX(64) ? _limit : (limit < 1 ? 1 : limit);

	_pages = INTMAX(32);
	_offset = _limit * _page;
	v_offset = 0; v_limit = _limit + _offset;
	_hasMore = !(v_limit > oldRowsCount && _rowsCount < v_limit);
}
void Paginator::page(std::int64_t val)
{
	val -= 1;
	//_page = val < 0 ? 0 : (val < _pages ? val : (_pages-1));
	_page = val;
	_pageChanged = true;
}
void Paginator::extend()
{
	//if(_page < (_pages-1)) ++_page;
	++_page;
	_pageChanged = true;
}


List::List()
{
}
List::~List()
{
}

void List::clear()
{
	rows = NULL;
	selected = "";
}
void List::add(std::string title, std::string value)
{
	rows.add(new Row(title, value));
}


Table::Table()
{
	_showHeader = true;
	_showCheckboxes = true;
	_visibleOnly = true;
	_hideEmptyCollumns = false;

	clear();
}
Table::~Table()
{
}

void Table::clear()
{
	_sort = 0;
	_rowsChecked = false;
	header = NULL;
	rows = NULL;
}

void Table::set(core::Vector<AnySqlRow> &sqlRows, const core::db::Table &table)
{
	header = table.headerNames(_hideEmptyCollumns);

	bool reloadRows = sqlRows->size() != rows->size();
	if(reloadRows) { rows = NULL; _rowsChecked = false;
		for(std::uint32_t i=0; i<sqlRows->size(); ++i) rows.add(new Row(table.data(&(*sqlRows()[i]), _visibleOnly)));
	}
	else { _rowsChecked = true;
		for(std::uint32_t i=0; i<sqlRows->size(); ++i) {
			rows()[i]->data = table.data(&(*sqlRows()[i]), _visibleOnly);
			_rowsChecked = !rows()[i]->checked ? false : _rowsChecked;
		}
	}
}

void Table::check(std::size_t index)
{
	if(index >= rows->size()) return;
	rows()[index]->checked = true;
}
void Table::uncheck(std::size_t index)
{
	if(index >= rows->size()) return;
	rows()[index]->checked = false;
}
void Table::toggle(std::size_t index)
{
	if(index >= rows->size()) return;
	rows()[index]->checked = !rows()[index]->checked;
}
void Table::checkAll()
{
	_rowsChecked = false;
	toggleAll();
}
void Table::uncheckAll()
{
	_rowsChecked = true;
	toggleAll();
}
void Table::toggleAll()
{
	_rowsChecked = !_rowsChecked;
	for(std::uint32_t i=0; i<rows->size(); ++i) rows()[i]->checked = _rowsChecked;
}