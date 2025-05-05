#pragma once

#include <string>
#include <chrono>
#include <memory>
#include <iostream>
#include "utilities.hpp"

// Forward declaration of CountrySpec
class CountrySpec;

// Alias for shared pointer of constant CountrySpec
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

    void send_to(std::ostream& os) const;
    void recv_from(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const Country& item);
    friend std::istream& operator>>(std::istream& is, Country& item);

private:
    int _id{};
    spcCountrySpec _spec;
};

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
    std::chrono::year_month_day get_independence_date() const { return _independence_date; }

    void send_to(std::ostream& os) const;
    void recv_from(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const CountrySpec& spec);
    friend std::istream& operator>>(std::istream& is, CountrySpec& spec);
    friend std::ostream& operator<<(std::ostream& os, CountrySpec::Continent continent);
    friend std::istream& operator>>(std::istream& is, CountrySpec::Continent& continent);

private:
    std::string _name;
    double _population{};
    Continent _continent{ Continent::ANY };
    std::chrono::year_month_day _independence_date{};
};