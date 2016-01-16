#ifndef CORE_HEADER_H
#define CORE_HEADER_H


#include "Poco/Nullable.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/Data/Session.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"

#include <string>
#include <map>
#include <stack>
#include <vector>
#include <memory>
#include <mutex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <stdio.h>
#include <typeinfo>


#ifdef _MSC_VER
	#define crossinline __forceinline
#else
	#define crossinline inline __attribute__((always_inline))
#endif

#ifdef __inline
	#undef __inline
#endif
#define __inline crossinline


template<typename T> struct __hide_type_unref { typedef T Type; };
template<typename T> struct __hide_type_unref<T&> { typedef T Type; };


#define INTMAX(_bit) std::int##_bit##_t(std::uint##_bit##_t(-1)/2)

#define __hide_conc(_1, _2) __hide_conc2(_1, _2)
#define __hide_conc2(_1, _2) _1##_2


//#define printff printf
#define printff(...)


#include <model/User.h>
#include <core/Server.h>
#include <core/Facet.h>


#endif // CORE_HEADER_H
