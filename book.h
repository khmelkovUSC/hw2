#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product {
public:
    Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);

    // Return all searchable keywords of the object, for indexing
    std::set<std::string> keywords() const;

    // Output all info about the object in the user interface format
    std::string displayString() const;

    // Output all info about the object in the text database format
    void dump(std::ostream& os) const;
private:
    std::string isbn_;
    std::string author_;
};


#endif