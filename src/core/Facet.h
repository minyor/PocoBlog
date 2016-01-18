//
// Some simple web components
// like paginator, table or captcha
//
// Copyright (c) 2016, minyor.
//
// License:	BSD
//


#ifndef CORE_FACET_H
#define CORE_FACET_H


#include <core/Header.h>
#include <core/db/Sql.h>


#ifndef NULL
	#define NULL 0
#endif


namespace core
{
	namespace facet
	{
		class CaptchaCalc
		{
			std::string _name, _sum;
			std::string _num1, _num2;

		public:
			CaptchaCalc();
			~CaptchaCalc();

		public:
			void refresh(std::uint32_t base1 = 10, std::uint32_t base2 = 10);
			std::string htmlUse();
			std::string htmlQuestion();
			std::string htmlAnswer();

		public:
			__inline bool operator ==(const std::string &val) const { return _sum == val; }
			__inline bool operator !=(const std::string &val) const { return _sum != val; }
			__inline const std::string &name() const { return _name; }
			__inline const std::string &num1() const { return _num1; }
			__inline const std::string &num2() const { return _num2; }

		};

		class Paginator
		{
			std::int64_t _limit, _offset, v_limit, v_offset;
			std::int32_t _rowsCount, _sides, _page, _pages;
			std::int32_t _prev, _next, _first, _last;
			bool _hasMore, _pageChanged;

		public:
			core::Vector<std::int32_t> indices;

		public:
			Paginator();
			~Paginator();

		public:
			void reset();
			void doPaging(std::int64_t rowsCount, std::int64_t limit = INTMAX(64));
			void doExtending(std::int64_t rowsCount, std::int64_t limit = INTMAX(64));

		public:
			void page(std::int64_t val);
			void extend();

		public:
			__inline void sides(std::int32_t val) { _sides = val; }
			__inline std::int32_t sides() const { return _sides; }

			__inline std::int64_t limit() const { return v_limit; }
			__inline std::int64_t offset() const { return v_offset; }
			__inline std::int64_t page() const { return _page+1; }
			__inline std::int64_t pages() const { return _pages; }
			__inline std::int64_t prev() const { return _prev; }
			__inline std::int64_t next() const { return _next; }
			__inline std::int64_t first() const { return _first; }
			__inline std::int64_t last() const { return _last; }
			__inline bool hasMore() const { return _hasMore; }

		};

		class List
		{
		public:
			struct Row {
				std::string title;
				std::string value;
				__inline Row(std::string title, std::string value) : title(title), value(value) {}
			};

			core::Vector<Row> rows;
			std::string selected;
			std::string prompt;

		public:
			List();
			~List();

		public:
			void clear();
			void add(std::string title, std::string value);

		};

		class Table
		{
			std::int32_t _sort;
			bool _rowsChecked, _showHeader, _showCheckboxes, _visibleOnly, _hideEmptyCollumns;

		public:
			typedef int AnySqlRow;
			struct Row {
				bool checked;
				core::Vector<std::string> data;
				__inline Row(core::Vector<std::string> data) : checked(false), data(data) {}
			};

			core::Vector<std::string> header;
			core::Vector<Row> rows;

		public:
			Table();
			~Table();

		public:
			void clear();
			void set(core::Vector<AnySqlRow> &sqlRows, const core::db::Table &table);
			template<typename T> void set(core::Vector<T> sqlRows) {
				set((core::Vector<AnySqlRow> &)sqlRows, server().sql().table(*sqlRows()[0]));
			}

		public:
			void check(std::size_t index);
			void uncheck(std::size_t index);
			void toggle(std::size_t index);
			void checkAll();
			void uncheckAll();
			void toggleAll();

		public:
			__inline void sort(std::int32_t val) { _sort = val; }
			__inline std::int32_t sort() const { return _sort; }

			__inline bool rowsChecked() const { return _rowsChecked; }

			__inline void showHeader(bool val) { _showHeader = val; }
			__inline bool showHeader() const { return _showHeader; }

			__inline void showCheckboxes(bool val) { _showCheckboxes = val; }
			__inline bool showCheckboxes() const { return _showCheckboxes; }

			__inline void visibleOnly(bool val) { _visibleOnly = val; }
			__inline bool visibleOnly() const { return _visibleOnly; }

			__inline void hideEmptyCollumns(bool val) { _hideEmptyCollumns = val; }
			__inline bool hideEmptyCollumns() const { return _hideEmptyCollumns; }

		};
	}
}


#endif // CORE_FACET_H
