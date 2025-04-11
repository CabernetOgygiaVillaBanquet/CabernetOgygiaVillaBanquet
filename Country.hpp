#pragma once

#include <string>
#include <chrono>
#include <memory>

class CountrySpec
{
public:
    enum class Continent { ANY, AFRICA, ASIA, EUROPE, NORTH_AMERICA, SOUTH_AMERICA, OCEANIA, ANTARCTICA };
    static constexpr std::string_view Continent_str[] = { "Any", "Africa", "Asia", "Europe", "North America", "South America", "Oceania", "Antarctica" };

    CountrySpec() = default;
    CountrySpec(const std::string& name, double population, Continent continent, std::chrono::year_month_day independence_date)
        : _name{ name }, _population{ population }, _continent{ continent }, _independence_date{ independence_date } {
    }

    std::string get_name() const { return _name; }
    double get_population() const { return _population; }
    Continent get_continent() const { return _continent; }
    std::string_view get_continent_str() const { return Continent_str[static_cast<std::size_t>(_continent)]; }
    std::chrono::year_month_day get_independence_date() const { return _independence_date; }

    bool matches(const CountrySpec& otherSpec) const;

private:
    std::string _name;
    double _population;
    Continent _continent;
    std::chrono::year_month_day _independence_date{};
};

using spcCountrySpec = std::shared_ptr<const CountrySpec>;

class Country
{
public:
    Country() = default;
    Country(int id, spcCountrySpec spec)
        : _id{ id }, _spec{ spec } {
    }

    int get_id() const { return _id; }
    spcCountrySpec get_spec() const { return _spec; }

private:
    int _id;
    spcCountrySpec _spec;
};
