#include "Country.hpp"
#include <iomanip>
#include <cmath>

// Implementation of CountrySpec::send_to
void CountrySpec::send_to(std::ostream& os) const
{
    os << _name << csv_delimiter
        << _population << csv_delimiter
        << _continent << csv_delimiter
        << _independence_date;
}

// Implementation of CountrySpec::recv_from
void CountrySpec::recv_from(std::istream& is)
{
    if (is)
        std::getline(is >> std::ws, _name, csv_delimiter);
    if (is)
        (is >> _population).ignore();
    if (is)
        is >> _continent;
    if (is)
        (is >> _independence_date).ignore();
}

// Overloaded output operator for CountrySpec
std::ostream& operator<<(std::ostream& os, const CountrySpec& spec)
{
    spec.send_to(os);
    return os;
}

// Overloaded input operator for CountrySpec
std::istream& operator>>(std::istream& is, CountrySpec& spec)
{
    spec.recv_from(is);
    return is;
}

// Overloaded output operator for CountrySpec::Continent
std::ostream& operator<<(std::ostream& os, CountrySpec::Continent continent)
{
    return os << CountrySpec::Continent_str[static_cast<size_t>(continent)];
}

// Overloaded input operator for CountrySpec::Continent
std::istream& operator>>(std::istream& is, CountrySpec::Continent& continent)
{
    if (is) {
        std::string tmp;
        std::getline(is, tmp, csv_delimiter);
        if (is) {
            auto found = false;
            auto count = sizeof(CountrySpec::Continent_str) / sizeof(CountrySpec::Continent_str[0]);
            for (size_t i = 0; i < count; i++) {
                if (tmp.length() == CountrySpec::Continent_str[i].length()
                    && 0 == strcasecmp(tmp.c_str(),
                        std::string(CountrySpec::Continent_str[i]).c_str())) {
                    continent = static_cast<CountrySpec::Continent>(i);
                    found = true;
                    break;
                }
            }
            if (!found)
                continent = CountrySpec::Continent::ANY;
        }
    }
    return is;
}

// Implementation of Country::send_to
void Country::send_to(std::ostream& os) const
{
    os << _id << csv_delimiter;
    if (_spec)
        _spec->send_to(os);
    else
        os << "NULL";
}

// Implementation of Country::recv_from
void Country::recv_from(std::istream& is)
{
    if (is)
        (is >> _id).ignore();
    auto temp_spec = std::make_shared<CountrySpec>();
    if (is)
        is >> *temp_spec;
    _spec = temp_spec;
}

// Overloaded output operator for Country
std::ostream& operator<<(std::ostream& os, const Country& item)
{
    item.send_to(os);
    return os;
}

// Overloaded input operator for Country
std::istream& operator>>(std::istream& is, Country& item)
{
    item.recv_from(is);
    return is;
}