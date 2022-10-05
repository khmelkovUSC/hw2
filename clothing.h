#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product {
public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    
    // Return all searchable keywords of the object, for indexing
    std::set<std::string> keywords() const;

    // Output all info about the object in the user interface format
    std::string displayString() const;

    // Output all info about the object in the text database format
    void dump(std::ostream& os) const;
private:
    std::string size_;
    std::string brand_;
};


#endif