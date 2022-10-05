#include "util.h"
#include <iostream>

void testParseStringToWords(std::string input);
template <typename T>
void printSet(std::set<T> s);
template <typename T>
void testSetOperations(std::set<T> s1, std::set<T> s2);

int main() {
    // Expected output: [men]
    testParseStringToWords("Men's");
    // No output expected
    testParseStringToWords("J.");
    // Expected output: [ll]
    testParseStringToWords("I'll");
    // Expected output: [abcdef, sdlkfjsd]
    testParseStringToWords("abcdef.sdlkfjsd");
    // Expected output: [hello, world]
    testParseStringToWords("Hello world");

    // Expected output: intersection [2,20], union [1,2,3,4,6,10,20,30,40,60]
    testSetOperations(std::set<int> {1,2,3,10,20,30}, std::set<int> {2,4,6,20,40,60});
}

void testParseStringToWords(std::string input) {
    using namespace std;
    set<string> parsed = parseStringToWords(input);
    cout << "Testing: " << input << endl;
    printSet(parsed);
    cout << endl;
}

template <typename T>
void testSetOperations(std::set<T> s1, std::set<T> s2) {
    std::set<T> intersect = setIntersection(s1, s2);
    std::cout << "Testing intersect" << std::endl;
    printSet(intersect);

    std::set<T> unionSets = setUnion(s1, s2);
    std::cout << "Testing union" << std::endl;
    printSet(unionSets);
    std::cout << std::endl;
}

template <typename T>
void printSet(std::set<T> s) {
    for (typename std::set<T>::iterator it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << std::endl;
    }
}