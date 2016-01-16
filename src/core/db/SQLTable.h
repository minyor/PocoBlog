
#ifndef CORE_DB_SQLTABLE_H
#define	CORE_DB_SQLTABLE_H


#include <core/Server.h>


#define SQLTableBegin(_name, _type) namespace Poco { namespace Data { typedef _type __hide_T_##_name;\
	template <> class TypeHandler<_type> { public: typedef _type T; static std::size_t &size() { static std::size_t _size = 0; return _size; }\
		static std::unique_ptr<core::db::Table> &_table() { static std::unique_ptr<core::db::Table> table = std::unique_ptr<core::db::Table>(new core::db::Table(#_name, typeid(_type).name(), &to_string)); return table; }

#define SQLColumn(_i, _name, _type)\
	static crossinline bool __hide_all_PDTH_##_i(char fnc, std::size_t &pos, const void *var, const void *deflt, AbstractBinder::Ptr pBinder, AbstractExtractor::Ptr pExtr, AbstractPreparator::Ptr pPrep, AbstractBinder::Direction dir) {\
		switch(fnc) {\
			case 0: TypeHandler<decltype((*(T *)var)._name)>::bind(pos++, (*(T *)var)._name, pBinder, dir); break;\
			case 1: TypeHandler<decltype((*(T *)var)._name)>::extract(pos++, (*(T *)var)._name, (*(T *)deflt)._name, pExtr); break;\
			case 2: TypeHandler<decltype((*(T *)var)._name)>::prepare(pos++, (*(T *)var)._name, pPrep); break;\
			case 3: _table()->addColumn(new core::db::Table::Column(#_name, _type)); break;\
			case 4: ToStrData &data = *(ToStrData *)deflt; data.to->add(new std::string((data.table->column(pos++).visible() || !data.visibleOnly) ? core::to_string((*(T *)var)._name) : "")); break;\
		} return true;\
	}

#define SQLTableEnd(_name)\
		static void bind(std::size_t pos, const T& var, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir) { __hide_bep_PDTH(b) }\
		static void extract(std::size_t pos, T& var, const T& deflt, AbstractExtractor::Ptr pExtr) { __hide_bep_PDTH(e) }\
		static void prepare(std::size_t pos, const T& var, AbstractPreparator::Ptr pPrep) { __hide_bep_PDTH(p) }\
		static void to_string(core::Vector<std::string> &to, void *var, const core::db::Table &table, bool visibleOnly) { std::size_t pos = 0; ToStrData data(&to, &table, visibleOnly); while(1) { __hide_bep_PDTH(t); break; } }\
		static void _postInit() { if(core::server().sql().table(#_name)) return; std::size_t pos = 0; while(1) { __hide_bep_PDTH(s); break; } size() = _table()->size(); core::server().sql().addTable(&(*_table())); _table().release(); }\
	};\
	static bool __hide_conc(__hid_sql_INIT_, __LINE__)() { core::server().addSqlInit(&TypeHandler<__hide_T_##_name>::_postInit); return true; }\
	static bool __hide_conc(__hid_sql_init_, __LINE__) = __hide_conc(__hid_sql_INIT_, __LINE__)();\
} }


#define __hide_bepd_PDTH_X(_id) static crossinline bool __hide_all_PDTH_##_id(char fnc, std::size_t &pos, const void *var, const void *deflt, AbstractBinder::Ptr pBinder, AbstractExtractor::Ptr pExtr, AbstractPreparator::Ptr pPrep, AbstractBinder::Direction dir)
#define __hide_bepi_PDTH_X(_id) __hide_bepd_PDTH_X(_id) { return false; }
#define __hide_bepu_PDTH_X(_id) (void)__hide_all_PDTH_##_id;

#define __hide_bepb_PDTH_X(_id) if(_id && !__hide_all_PDTH_##_id(0, pos, &var, NULL, pBinder, NULL, NULL, dir)) return;
#define __hide_bepe_PDTH_X(_id) if(_id && !__hide_all_PDTH_##_id(1, pos, &var, &deflt, NULL, pExtr, NULL, AbstractBinder::Direction::PD_IN)) return;
#define __hide_bepp_PDTH_X(_id) if(_id && !__hide_all_PDTH_##_id(2, pos, &var, NULL, NULL, NULL, pPrep, AbstractBinder::Direction::PD_IN)) return;
#define __hide_beps_PDTH_X(_id) if(_id && !__hide_all_PDTH_##_id(3, pos, NULL, NULL, NULL, NULL, NULL, AbstractBinder::Direction::PD_IN)) break;
#define __hide_bept_PDTH_X(_id) if(_id && !__hide_all_PDTH_##_id(4, pos, var, (const void *)&data, NULL, NULL, NULL, AbstractBinder::Direction::PD_IN)) break;

#define __hide_bep_PDTH(_n) __hide_bep_PDTH_XXX(_n, , ) /*__hide_bep_PDTH_XXX(_n, 10, 1)*/ /*__hide_bep_PDTH_XXX(_n, 20, 2)*/
#define __hide_bep_PDTH_XXX(_n, _id0, _id) __hide_bep_PDTH_XX(_n, _id0) __hide_bep_PDTH_XX(_n, _id##1) __hide_bep_PDTH_XX(_n, _id##2) __hide_bep_PDTH_XX(_n, _id##3) __hide_bep_PDTH_XX(_n, _id##4) __hide_bep_PDTH_XX(_n, _id##5) __hide_bep_PDTH_XX(_n, _id##6) __hide_bep_PDTH_XX(_n, _id##7) __hide_bep_PDTH_XX(_n, _id##8) __hide_bep_PDTH_XX(_n, _id##9)
#define __hide_bep_PDTH_XX(_n, _id) __hide_bep##_n##_PDTH_X(_id##0) __hide_bep##_n##_PDTH_X(_id##1) __hide_bep##_n##_PDTH_X(_id##2) __hide_bep##_n##_PDTH_X(_id##3) __hide_bep##_n##_PDTH_X(_id##4) __hide_bep##_n##_PDTH_X(_id##5) __hide_bep##_n##_PDTH_X(_id##6) __hide_bep##_n##_PDTH_X(_id##7) __hide_bep##_n##_PDTH_X(_id##8) __hide_bep##_n##_PDTH_X(_id##9)

namespace Poco { namespace Data {
	__hide_bep_PDTH(i)
	static bool __hide_bep_PDTH_INIT() { __hide_bep_PDTH(u) return true; }
	static bool __hide_bep_PDTH_init = __hide_bep_PDTH_INIT();
	struct ToStrData {
		core::Vector<std::string> *to; const core::db::Table *table; bool visibleOnly;
		ToStrData(core::Vector<std::string> *to, const core::db::Table *table, bool visibleOnly) :
			to(to), table(table), visibleOnly(visibleOnly) {}
	};
} }


#endif /* CORE_DB_SQLTABLE_H */
