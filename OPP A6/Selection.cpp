#include "Selection.hpp"

void Selection::add(const Country& country)
{
    _countries.push_back(country);
}

const Country& Selection::get(size_t i) const
{
    if (i >= _countries.size()) {
        throw std::out_of_range("Invalid index value.");
    }
    return _countries[i];
}

void Selection::save(const std::string& csv_file_name) const
{
    std::ofstream ofs(csv_file_name);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }
    for (const auto& country : _countries) {
        ofs << country << '\n';
    }
}

void Selection::load(const std::string& csv_file_name)
{
    std::ifstream ifs(csv_file_name);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open file for reading.");
    }
    _countries.clear();
    Country temp;
    while (ifs >> temp) {
        _countries.push_back(temp);
    }
}