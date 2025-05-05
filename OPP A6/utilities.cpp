#include "utilities.hpp"

#include <iostream>
#include <iomanip> // for std::put_time()

constexpr auto ymd_format{ "%Y-%m-%d" }; // %F - for ISO 8601 date, %R for time

// helper functions
std::string to_string(year_month_day ymd);

std::string to_string(year_month_day ymd)
{
    if (!ymd.ok())
        return "0000-00-00";

    std::chrono::system_clock::time_point dt(std::chrono::time_point<std::chrono::system_clock, std::chrono::days>(std::chrono::sys_days{ ymd }));

#ifdef __cpp_lib_format
    return std::format("{:%F}", std::chrono::current_zone()->to_local(dt));
#else
    std::ostringstream oss;
    auto tt{ std::chrono::system_clock::to_time_t(dt) };
    auto lt{ *std::localtime(&tt) };
    oss << std::put_time(&lt, ymd_format);
    return oss.str();
#endif
}


std::ostream& operator<<(std::ostream& os, const year_month_day& ymd)
{
    return os << to_string(ymd);
}

std::istream& operator>>(std::istream& is, year_month_day& ymd)
{
    if (is)
    {
#ifdef _MSC_VER
        // Not implemented by Clang++/G++ compilers:
        std::chrono::from_stream(is, ymd_format, ymd);
#else
        std::tm t{};
        is >> std::get_time(&t, ymd_format);
        if (!is)
            ymd = year_month_day{};
        else
        {
            auto dp{ std::chrono::system_clock::from_time_t(mktime(&t)) };
            ymd = std::chrono::year_month_day{ ceil<days>(dp) };
        }
#endif
    }
    return is;
}