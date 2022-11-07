#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
    Product(category, name, price, qty), size_(size), brand_(brand) {

}

// Return all searchable keywords of the object, for indexing
std::set<std::string> Clothing::keywords() const {
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> brand = parseStringToWords(brand_);
    std::set<std::string> results = setUnion(name, brand);
    return results;
}

// Output all info about the object in the user interface format
std::string Clothing::displayString() const {
    std::string display = "";
    display += name_;
    display += "\n";
    display += "Size: " + size_ + " Brand: " + brand_;
    display += "\n";
    // Round off the price to 2 decimal points
    std::string price = std::to_string(int(price_)) + ".";
    if (int(price_*1000+0.001)%10 >= 5) price += std::to_string((int(price_*100+0.001)%100 + 1));
    else price += std::to_string(int(price_*100+0.001)%100);

    display += price + " " + std::to_string(qty_) + " left.";
    display += "\n";
    return display;
}

// Output all info about the object in the text database format
void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}