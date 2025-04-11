#include "Country.hpp"
#include "Selection.hpp"
#include <chrono>
#include <iostream>
#include <cassert> // for assert()

// Show abstraction object properties
void show(const Country& item)
{
    auto is_p{ item.get_spec() }; // retrieve smart pointer

    if (!is_p) // if there is no specification object behind the pointer
        is_p.reset(new CountrySpec()); // then construct the default

    std::cout << item.get_id()
        << " '" << is_p->get_name() << "' "
        << std::fixed << std::setprecision(2) << is_p->get_population()
        << " '" << is_p->get_continent_str() << "' "
        << " " << is_p->get_independence_date()
        << std::endl;
}

Country max_population(const Selection& sel)
{
    Country max_country;
    double max_pop = 0.0;
    for (size_t i = 0; i < sel.get_count(); ++i)
    {
        Country current = sel.get(i);
        if (current.get_spec()->get_population() > max_pop)
        {
            max_pop = current.get_spec()->get_population();
            max_country = current;
        }
    }
    return max_country;
}

double avg_population(const Selection& sel)
{
    double total_pop = 0.0;
    for (size_t i = 0; i < sel.get_count(); ++i)
    {
        total_pop += sel.get(i).get_spec()->get_population();
    }
    return (sel.get_count() > 0) ? total_pop / sel.get_count() : 0.0;
}

int main()
{
    Selection sel;

    // V1: the specification object is constructed separately
    spcCountrySpec france_spec{ new CountrySpec("France", 67.39, CountrySpec::Continent::EUROPE, std::chrono::July / 14 / 1789) };
    sel.add(1, france_spec);

    // V2: the specification object is constructed during passing of an argument
    spcCountrySpec japan_spec = std::make_shared<CountrySpec>("Japan", 126.3, CountrySpec::Continent::ASIA, std::chrono::May / 3 / 1947);
    sel.add(2, japan_spec);

    // V3: constructing and using shared specification between several abstractions
    spcCountrySpec spec_europe{ new CountrySpec("Generic European Country", 80.0, CountrySpec::Continent::EUROPE, std::chrono::January / 1 / 1900) };
    sel.add(3, spec_europe);
    sel.add(4, spec_europe);

    // Validate the count of items
    assert(sel.get_count() == 4);

    // Search in the selection and show the result.
    // Test with different query values.
    Country qry1(2, japan_spec);
    Country result = sel.search(qry1);
    assert(result.get_id() == 2);
    show(result);

    // Search for object with concrete country name:
    Country qry2(0, std::make_shared<CountrySpec>("France", 0.0, CountrySpec::Continent::ANY, std::chrono::year_month_day{}));
    result = sel.search(qry2);
    assert(result.get_spec()->get_name() == "France");
    show(result);

    // Search for object with concrete date of independence:
    Country qry3(0, std::make_shared<CountrySpec>("", 0.0, CountrySpec::Continent::ANY, std::chrono::May / 3 / 1947));
    result = sel.search(qry3);
    assert(result.get_spec()->get_independence_date() == std::chrono::May / 3 / 1947);
    show(result);

    // Search for non-matching object:
    Country qry4(0, std::make_shared<CountrySpec>("Atlantis", 0.0, CountrySpec::Continent::ANY, std::chrono::year_month_day{}));
    result = sel.search(qry4);
    assert(result.get_id() == 0); // Assuming default Country has id 0
    show(result);

    // Search using CountrySpec
    CountrySpec qry_spec{ "Generic European Country", 0.0, CountrySpec::Continent::ANY, std::chrono::year_month_day{} };
    result = sel.search(qry_spec);
    assert(result.get_spec()->get_name() == "Generic European Country");
    show(result);

    // Demonstrate max_population function
    Country max_pop_country = max_population(sel);
    assert(max_pop_country.get_id() == 2);
    std::cout << "Country with the maximum population:\n";
    show(max_pop_country);

    // Demonstrate avg_population function
    double avg_pop = avg_population(sel);
    assert(avg_pop == (67.39 + 126.3 + 80.0 + 80.0) / 4);
    std::cout << "Average population: " << avg_pop << "\n";

    return 0;
}