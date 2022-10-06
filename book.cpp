#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) :
    Product(category, name, price, qty), isbn_(isbn), author_(author) {

}

// Return all searchable keywords of the object, for indexing
std::set<std::string> Book::keywords() const {
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> author = parseStringToWords(author_);
    std::set<std::string> results = setUnion(name, author);
    results.insert(isbn_);
    return results;
}

// Output all info about the object in the user interface format
std::string Book::displayString() const {
    std::string display = "";
    display += name_;
    display += "\n";
    display += "Author: " + author_ + " ISBN: " + isbn_;
    display += "\n";
    // Round off the price to 2 decimal points
    std::string price = std::to_string(int(price_)) + ".";
    if (int(price_*1000)%10 >= 5) price += std::to_string((int(price_*100)%100 + 1));
    else price += std::to_string(int(price_*100)%100);

    display += price + " " + std::to_string(qty_) + " left.";
    display += "\n";
    return display;
}

// Output all info about the object in the text database format
void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}