#include "Selection.hpp"

void Selection::add(int id, spcCountrySpec spec)
{
    if (_count < Selection::MAX_COUNT)
    {
        Country new_item(id, spec);
        // Check for duplicates before adding
        if (search(new_item).get_id() == 0) // Assuming default Country has id 0
        {
            _items[_count] = new_item;
            _count++;
        }
    }
}

Country Selection::search(const Country& query) const
{
    auto query_spec_p{ query.get_spec() };

    for (size_t i{ 0 }; i < _count; i++)
    {
        if (0 != query.get_id() && query.get_id() != _items[i].get_id())
            continue;

        auto item_spec_p{ _items[i].get_spec() };

        if (query_spec_p && item_spec_p && item_spec_p->matches(*query_spec_p))
            return _items[i]; // the first object with matching specification
    }

    return Country{};
}

Country Selection::search(const CountrySpec& query_spec) const
{
    for (size_t i{ 0 }; i < _count; i++)
    {
        auto item_spec_p{ _items[i].get_spec() };

        if (item_spec_p && item_spec_p->matches(query_spec))
            return _items[i]; // the first object with matching specification
    }

    return Country{};
}