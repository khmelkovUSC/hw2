#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);
private:
    // Stores each distinct product once
    std::vector<Product*> products_;
    // Stores a mapping of individual keywords, and all products with that keyword
    std::map<std::string, std::vector<Product*>> productsTerms_;
    std::vector<User*> users_;
    std::map<std::string, std::queue<Product*>> usersCarts_;
};

#endif