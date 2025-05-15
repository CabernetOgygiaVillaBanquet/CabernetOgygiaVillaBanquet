#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <sstream>

class Collectible
{
public:
    Collectible() =default;

    Collectible(std::string name)
    {
        // TODO: :::
    }

    std::string get_name() const
    {
        return _name;
    }

    virtual operator std::string() const =0;

private:
    std::string _name{};
};

Collectible::operator std::string() const
{
    return "Name: '" /* TODO: .. */ "'";
}


class Book : public Collectible
{
public:
    Book(std::string name, std::string author, int year)
        // TODO: ..
    {
        // TODO: :::
    }

    operator std::string() const // TODO: ..
    {
       return Collectible::operator std::string() + ", "
              "Author: '" /* TODO: .. */ "', "
              "Year: " + std::to_string(_year);
    }
    // :::
private:
    std::string _author{};
    unsigned short _year{};
};


class Collection
{
public:
    static const size_t MAX_SIZE{ 20 };

    void collect(std::shared_ptr<Collectible> item)
    {
        // TODO: :::
    }

    std::shared_ptr<Collectible> get(size_t i) const
    {
        // TODO: :::
        return this->_items[i];
    }

    operator std::string() const
    {
        std::stringstream ss;
        
        for (auto i{ 0U }; i < this->_count; i++)
            ss << (std::string)*this->_items[i] << "\n";

        return ss.str();
    }

private:
    std::shared_ptr<Collectible> _items[MAX_SIZE];
    size_t _count{ 0 };
};


int main()
{
    Collection my_books;

    try
    {
        my_books.collect(std::shared_ptr<Book>(new Book{"", "A.Author1", 2005}));
    }
    catch (const std::exception & ex)
    {
        std::cerr << "Caught exception:" << ex.what() << "\n";
    }
    
    my_books.collect(std::shared_ptr<Book>(new Book{"Book1", "A.Author1", 2023}));
    my_books.collect(std::shared_ptr<Book>(new Book{"Book2", "A.Author2", 2025}));
    
    std::cout << (std::string)my_books << "\n";
    
    try
    {
        std::cout << (std::string)*my_books.get(10) << "\n";
    }
    catch (const std::exception & ex)
    {
        std::cerr << "Caught exception:" << ex.what() << "\n";
    }

    std::cout << (std::string)*my_books.get(0) << "\n";
    
    std::cout << "OK\n";

    return 0;
}