#include "Country.hpp"
#include <cmath> // for the function std::abs()

bool CountrySpec::matches(const CountrySpec& otherSpec) const
{
    if (this == &otherSpec) // if comparing to self
        return true;

    auto result{ true };

    // Check each CountrySpec property, e.g.:

    if (result && !otherSpec._name.empty() && _name != otherSpec._name)
        result = false;

    if (result && 0.0 != otherSpec._population && std::abs(_population - otherSpec._population) > 0.005)
        result = false;

    if (result && CountrySpec::Continent::ANY != otherSpec._continent && _continent != otherSpec._continent)
        result = false;

    if (result && otherSpec._independence_date.ok() && _independence_date != otherSpec._independence_date)
        result = false;

    return result;
}