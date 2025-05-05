#pragma once

#include "Country.hpp"
#include <stdexcept>
#include <vector>
#include <fstream>

class Selection
{
public:
    Selection() = default;
    Selection(const std::string& csv_file_name) { load(csv_file_name); }

    void add(const Country& country);
    const Country& get(size_t i) const;
    const Country& operator[](size_t i) const { return get(i); }

    void save(const std::string& csv_file_name) const;
    void load(const std::string& csv_file_name);

private:
    std::vector<Country> _countries;
};