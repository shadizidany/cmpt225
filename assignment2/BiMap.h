// Assignment 2A
// BiMap.h: Bidirectional map implementation using two hash tables for key-value lookups
#ifndef BI_MAP_H
#define BI_MAP_H
#include <iostream>
#include <vector>
#include <functional>
using namespace std;
// Checks if a number is prime
bool isPrime(int n) {
    if(n == 2 || n == 3) {
        return true;
    }
    if(n == 1 || n % 2 == 0) {
        return false;
    }
    for(int i = 3; i*i <= n; i += 2) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}
// Finds the next prime number greater than or equal to n
int nextPrime(int n) {
    if(n % 2 == 0) {
        n++;
    }
    for(; !isPrime(n); n += 2);
    return n;
}
// Bijective Map class 
// Implemented with two hash tables.
template <typename KeyType, typename ValType>
class BiMap {
    private:
        // Generic hash table implementation using quadratic probing for collision handling
        template <typename HashedKey, typename Image>
        class HashTable {
            private:
                // Entry states for hash table slots
                enum EntryType {EMPTY, ACTIVE, DELETED};
                // Structure to store key-value pairs and their state
                struct HashEntry {
                    HashedKey first;
                    Image second;
                    EntryType info;
                    // copy/move constructors are compiler-generated (Rule of Zero)
                };
                // Hash table array and current size counter
                vector<HashEntry> array;
                size_t currentSize;
                // Finds position for a key using quadratic probing
                int findPos(const HashedKey& x) const {
                    static hash<HashedKey> h;
                    int currentPos = h(x) % array.size(), offset = 1;
                    while (array[currentPos].info != EMPTY && array[currentPos].first != x) {
                        currentPos += offset;
                        offset += 2;
                        currentPos = currentPos % array.size();
                    }
                    return currentPos;
                }
                // Doubles table size and rehashes all elements when load factor exceeds 0.5
                void rehash() {
                    vector<HashEntry> temp = std::move(array);
                    array.resize(nextPrime(2*temp.size()));
                    makeEmpty();
                    for (auto& entry : temp) {
                        if (entry.info == ACTIVE) {
                            insert(std::move(entry.first), std::move(entry.second));
                        }
                    }
                }
            public:
                // Constructor initializes hash table with prime size
                explicit HashTable(int size = 101) : array(nextPrime(size)) {
                    makeEmpty();
                }
                // Checks if a key exists in the hash table
                bool contains(const HashedKey& x) const {
                    return array[findPos(x)].info == ACTIVE;
                }
                // Removes all elements from the hash table
                void makeEmpty() {
                    currentSize = 0;
                    for (auto& entry : array) {
                        entry.info = EMPTY;
                    }
                }
                // Inserts a key-value pair into the hash table
                // Single template function handles both copy/move operations instead of overloading
                template <typename Key, typename Value>
                bool insert(Key&& x, Value&& y) {
                    int currentPos = findPos(x);
                    if (array[currentPos].info == ACTIVE) {
                        return false;
                    }
                    if (array[currentPos].info == EMPTY) {
                        currentSize++;
                    }
                    // Perfect forwarding maintains lvalue/rvalue properties of arguments
                    array[currentPos].first = std::forward<Key>(x);
                    array[currentPos].second = std::forward<Value>(y);
                    array[currentPos].info = ACTIVE;
                    if (currentSize > array.size() / 2) {
                        rehash();
                    }
                    return true;
                }
                // Removes a key from the hash table
                bool remove(const HashedKey& x) {
                    int currentPos = findPos(x);
                    if (array[currentPos].info == ACTIVE) {
                        array[currentPos].info = DELETED;
                        return true;
                    }
                    return false;
                }
                // Returns the number of active elements in the hash table
                int getSize() const {
                    int size = 0;
                    if (currentSize > 0) {
                        for (auto& entry : array) {
                            if (entry.info == ACTIVE) {
                                size++;
                            }
                        }
                    }
                    return size;
                }
                // Returns the value associated with a given key
                const Image& getImage(const HashedKey& x) const {
                    return array[findPos(x)].second;
                }
                // Displays all active key-value pairs in <key,value> format
                void display() const {
                    cout << "{ ";
                    if (currentSize > 0) {
                        bool first = true;
                        for (auto& entry : array) {
                            if (entry.info == ACTIVE) {
                                if (!first) {
                                    cout << ", ";
                                }
                                cout << "<" << entry.first << "," << entry.second << ">";
                                first = false;
                            }
                        }
                    }
                    cout << " }" << endl;
                }
                // Displays detailed hash table state including empty and deleted slots
                void ddisplay() const {
                    cout << "[ ";
                    for (size_t i = 0; i < array.size(); i++) {
                        cout << i << ":";
                        switch (array[i].info) {
                            case EMPTY: cout << "__";
                                        break;
                            case ACTIVE: cout << "\033[32m" << "<" << array[i].first << "," // \033[32m sets text color to green
                                                                   << array[i].second << ">" << "\033[0m";
                                         break;                    // \033[0m resets text color to default
                            case DELETED: cout << "\033[31m" << "del" << "\033[0m"; // \033[31m red
                        }
                        if (i < array.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << " ] // \u03BB="; // \u03BB Unicode for lambda
                    printf("%.2f\n", 1.0 * currentSize / array.size());
                }
        };
        // Two hash tables for bidirectional lookups: key<->value mappings
        HashTable<KeyType, ValType> keyToVal;
        HashTable<ValType, KeyType> valToKey;
    public:
        // constructor
        BiMap(int size = 11) : keyToVal(size), valToKey(size) {}
        // remove all pairs
        void makeEmpty() {
            keyToVal.makeEmpty();
            valToKey.makeEmpty();
        }
        // returns the current number of pairs
        int getSize() const {
            return keyToVal.getSize();
        }
        // insert pair <x,y>, return true iff <x,y> was inserted.
        bool insert(const KeyType& x, const ValType& y) {
            if (containsVal(y)) {
                return false;
            }
            return keyToVal.insert(x, y) && valToKey.insert(y, x);
        }
        // returns true if x is the key of a current pair.
        bool containsKey(const KeyType& x) const {
            return keyToVal.contains(x);
        }
        // returns true if y is the value of a current pair.
        bool containsVal(const ValType& y) const {
            return valToKey.contains(y);
        }
        // removes the pair with key x if it exists.
        bool removeKey(const KeyType& x) {
            if (!containsKey(x)) {
                return false;
            }
            return valToKey.remove(keyToVal.getImage(x)) && keyToVal.remove(x);
        }
        // removes the pair with values y if it exists.
        bool removeVal(const ValType& y) {
            if (!containsVal(y)) {
                return false;
            }
            return keyToVal.remove(valToKey.getImage(y)) && valToKey.remove(y);
        }
        // returns the value associated with key x.
        const ValType& getVal(const KeyType& x) const {
            return keyToVal.getImage(x);
        }
        // returns the key associated with value y.
        const KeyType& getKey(const ValType& y) const {
            return valToKey.getImage(y);
        }
        // Displays all active key-value pairs in <key,value> format
        void display() const {
            cout << "forward: "; keyToVal.display();
            cout << "inverse: "; valToKey.display();
        }
        // Displays detailed hash table state including empty and deleted slots
        void ddisplay() const {
            cout << "forward: "; keyToVal.ddisplay();
            cout << "inverse: "; valToKey.ddisplay();
        }
};
#endif