#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
    Product(category, name, price, qty), genre_(genre), rating_(rating) {

}

// Return all searchable keywords of the object, for indexing
std::set<std::string> Movie::keywords() const {
    return parseStringToWords(genre_);
}

std::string Movie::displayString() const {
    std::string display = "";
    display += name_;
    display += "\n";
    display += "Genre: " + genre_ + " Rating: " + rating_;
    display += "\n";
    // Round off the price to 2 decimal points
    std::string price = std::to_string(int(price_)) + ".";
    if (int(price_*1000)%10 >= 5) price += std::to_string((int(price_*100)%100 + 1));
    else price += std::to_string(int(price_*100)%100);

    display += price + " " + std::to_string(qty_) + " left.";

    return display;
}

// Output all info about the object in the text database format
void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}