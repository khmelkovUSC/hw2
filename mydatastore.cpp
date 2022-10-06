#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore() : productsTerms_(), usersCarts_() {

}

MyDataStore::~MyDataStore() {
    for (unsigned int i = 0; i<products_.size(); i++) {
        delete products_[i];
    }
    for (unsigned int i = 0; i<users_.size(); i++) {
        delete users_[i];
    }
}

// Adds a product to the data store
void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);
    std::set<std::string> terms = p->keywords();
    // For each of this product's keywords, see if that keyword is already in the map
    for (std::set<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) {
        std::map<std::string, std::vector<Product*>>::iterator match = productsTerms_.find(*it);
        // If the keyword isn't in the map, make a new map entry for that keyword with a Product* vector containing this product as the second
        if (match == productsTerms_.end()) {
                std::pair<std::string, std::vector<Product*>> toInsert = std::make_pair(*it, std::vector<Product*> {p});
                productsTerms_.insert(toInsert);
            }
        // If the keyword is in the map, add this product to its corresponding vector
        else match->second.push_back(p);
    }
}

//Adds a user to the data store
void MyDataStore::addUser(User* u) {
    users_.push_back(u);
    std::pair<std::string, std::queue<Product*>> toInsert = std::make_pair(u->getName(), std::queue<Product*>());
    usersCarts_.insert(toInsert);
}

// Performs a search of products whose keywords match the given "terms"
// type 0 = AND search (intersection of results for each term) while
// type 1 = OR search (union of results for each term)
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> results;
    if (terms.size() == 0) return results;

    if (type == 0) {
        std::vector<std::set<Product*>> hitsPerTerm;
        for (unsigned int i = 0; i<terms.size(); i++) {
            // Check the map for an entry corresponding to the search term
            std::map<std::string, std::vector<Product*>>::iterator match = productsTerms_.find(terms[i]);
            if (match != productsTerms_.end()) {
                std::set<Product*> hitsThisTerm;
                for (unsigned int j = 0; j<match->second.size(); j++) {
                    hitsThisTerm.insert(match->second[j]);
                }
                hitsPerTerm.push_back(hitsThisTerm);
            }
        }
        if (hitsPerTerm.size()>0) {
            std::set<Product*> currentSet = hitsPerTerm[0];
            for (unsigned int i = 1; i<hitsPerTerm.size(); i++) {
                currentSet = setIntersection(currentSet, hitsPerTerm[i]);
            }
            for (std::set<Product*>::iterator it = currentSet.begin(); it != currentSet.end(); ++it) {
                results.push_back(*it);
            }
        }
    } else if (type == 1) {
        for (unsigned int i = 0; i<terms.size(); i++) {
            // Check the map for an entry corresponding to the search term
            std::map<std::string, std::vector<Product*>>::iterator match = productsTerms_.find(terms[i]);
            // If an entry exists, add every product from the corresponding product vector to the results
            if (match != productsTerms_.end()) {
                for (unsigned int j = 0; j<match->second.size(); j++) {
                    // Check if the current Product* is already in the results vector
                    bool present = false;
                    for (unsigned int k = 0; k<results.size(); k++) {
                        if (results[k] == match->second[j]) present = true;
                    }
                    if (present == false) results.push_back(match->second[j]);
                }
            }
        }
    }
    return results;
}

// Reproduce the database file from the current Products and User valuess
void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << "\n";
    for (unsigned int i = 0; i<products_.size(); i++) {
        products_[i]->dump(ofile);
    }
    ofile << "<\\products>" << "\n";
    ofile << "<users>" << "\n";
    for (unsigned int i = 0; i<users_.size(); i++) {
        users_[i]->dump(ofile);
    }
    ofile << "<\\users>" << "\n";
}