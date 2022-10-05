#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

class Movie : public Product {
public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    
    // Return all searchable keywords of the object, for indexing
    std::set<std::string> keywords() const;

    // Output all info about the object in the user interface format
    std::string displayString() const;

    // Output all info about the object in the text database format
    void dump(std::ostream& os) const;
private:
    std::string genre_;
    std::string rating_;
};


#endif