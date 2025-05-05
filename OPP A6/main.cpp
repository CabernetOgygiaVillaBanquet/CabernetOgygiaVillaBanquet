#include "Country.hpp"
#include "Selection.hpp"
#include <iostream>
#include <cassert>

void show(const Country& item)
{
    std::cout << item << std::endl;
}

int main()
{
    try {
        Selection sel;

        sel.add(Country(1, std::make_shared<CountrySpec>("France", 67.39, CountrySpec::Continent::EUROPE, std::chrono::July / 14 / 1789)));
        sel.add(Country(2, std::make_shared<CountrySpec>("Japan", 126.3, CountrySpec::Continent::ASIA, std::chrono::May / 3 / 1947)));

        auto file_name = "countries.csv";
        sel.save(file_name);

        Selection loaded_sel(file_name);
        assert(loaded_sel[0].get_id() == 1);

        try {
            loaded_sel.get(10); // Invalid index
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}