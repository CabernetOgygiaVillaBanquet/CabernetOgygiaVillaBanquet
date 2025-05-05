#pragma once

#include <string>
#include <chrono>
#include <iostream>

using std::chrono::year_month_day;
using namespace std::chrono;

// helper constant
constexpr auto csv_delimiter{ ';' };

std::ostream& operator<<(std::ostream& os, const year_month_day& ymd);
std::istream& operator>>(std::istream& is, year_month_day& ymd);

#ifdef _MSC_VER // Visual C++ ?
#define strcasecmp _stricmp // then use the function _stricmp() 
#else
#include <strings.h> // for strcasecmp() function in POSIX C++
#endif