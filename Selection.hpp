#pragma once

#include "Country.hpp"
#include <memory>

class Selection
{
public:
    static const size_t MAX_COUNT{ 5 };

    Selection() = default;

    size_t get_count() const { return _count; }

    Country get(size_t i) const { return (i < _count) ? _items[i] : Country{}; }

    void add(int id, spcCountrySpec spec);

    Country search(const Country& query) const;
    Country search(const CountrySpec& query_spec) const;

private:
    Country _items[Selection::MAX_COUNT];
    size_t _count{};
};