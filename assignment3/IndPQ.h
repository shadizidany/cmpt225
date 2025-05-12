// Assignment 3A
// IndPQ.h: Indexed priority queue implementation using a binary heap and hash table
#ifndef INDPQ_H
#define INDPQ_H
#include <iostream>
#include <vector>
#include <functional>
#include <string>
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
// An Indexed Priority Queue implementation that supports direct access to elements by their IDs
class IndPQ {
    private:
        // Binary heap implementation with mapping support for O(log n) operations
        template <typename Object, typename Comparable>
        class BinaryHeap {
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
                                currentPos = (currentPos + offset) % array.size();
                                offset += 2;
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
                        explicit HashTable(int size = 11) : array(nextPrime(size)) {
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
                        // Returns the value associated with a given key
                        const Image& getImage(const HashedKey& x) const {
                            return array[findPos(x)].second;
                        }
                        // Updates the position value for a given key in the hash table
                        void updateImage(const HashedKey& x, const Image& y) {
                            array[findPos(x)].second = y;
                        }
                        // Displays detailed hash table state including empty and deleted slots
                        void ddisplay() const {
                            cout << "[ ";
                            for (size_t i = 0; i < array.size(); i++) {
                                cout << i << ":";
                                switch (array[i].info) {
                                    case EMPTY: cout << "__";
                                                break;
                                    case ACTIVE: cout << "\033[32m" << "<" << *array[i].first << "," << array[i].second << ">" << "\033[0m";
                                                 break; // \033[32m sets text color to green. \033[0m resets text color to default
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
                // Entry structure for the binary heap, storing both the element and its priority
                struct HeapEntry {
                    Object element;
                    Comparable priority;
                };
                size_t currentSize = 0; // Number of elements in heap
                vector<HeapEntry> array; // The heap array
                HashTable<Object, size_t> map; // Hash map for O(1) lookups by element value
        
                // Establish heap order property from an arbitrary arrangement of items. Runs in linear time.
                void buildHeap() {
                    for (size_t i = currentSize; i > 0; i--) {
                        map.insert(array[i].element, i);
                        if (i <= currentSize/2) {
                            percolateDown(i);
                        }
                    }
                }
        
                // Internal method to percolate up in the heap. hole is the index at which the percolate begins.
                void percolateUp(size_t hole) {
                    array[0] = std::move(array[hole]);
                    for (; array[0].priority < array[hole/2].priority; hole /= 2) {
                        array[hole] = std::move(array[hole/2]);
                        map.updateImage(array[hole].element, hole);
                    }
                    array[hole] = std::move(array[0]);
                    map.updateImage(array[hole].element, hole);
                }

                // Internal method to percolate down in the heap. hole is the index at which the percolate begins.
                void percolateDown(size_t hole) {
                    size_t child;
                    array[0] = std::move(array[hole]);
                    for (; hole*2 <= currentSize; hole = child) {
                        child = hole*2;
                        if (child != currentSize && array[child+1].priority < array[child].priority) {
                            child++;
                        }
                        if (array[child].priority < array[0].priority) {
                            array[hole] = std::move(array[child]);
                            map.updateImage(array[hole].element, hole);
                        }
                        else {
                            break;
                        }
                    }
                    array[hole] = std::move(array[0]);
                    map.updateImage(array[hole].element, hole);
                }

            public:
                // Constructor initializes an empty binary heap with specified initial capacity
                explicit BinaryHeap(int capacity = 10) : array(capacity), map(capacity*2) {}
        
                // Checks if the heap is empty (contains no elements)
                bool isEmpty() const {
                    return currentSize == 0;
                }
        
                // Returns a reference to the element with minimum priority without removing it
                const Object& findMin() const {
                    return array[1].element;
                }

                // Insert item e with priority p, not allowing duplicates.
                template <typename ObjectType, typename ComparableType>
                void insert(ObjectType&& e, ComparableType&& p) {
                    if (map.insert(std::forward<ObjectType>(e), currentSize+1)) {
                        if (++currentSize == array.size()) {
                            array.resize(2 * array.size());
                        }
                        array[currentSize].element = std::forward<ObjectType>(e);
                        array[currentSize].priority = std::forward<ComparableType>(p);
                        percolateUp(currentSize);
                    }
                }

                // Updates the priority of the specified element, maintaining heap property
                bool updatePriority(const Object& e, const Comparable& p) {
                    bool b = map.contains(e);
                    if (b) {
                        int hole = map.getImage(e);
                        if (p < array[hole].priority) {
                            array[hole].priority = p;
                            percolateUp(hole);
                        }
                        else if (p != array[hole].priority) {
                            array[hole].priority = p;
                            percolateDown(hole);
                        }
                    }
                    return b;
                }

                // Removes and returns a reference to the element with minimum priority
                Object& deleteMin() {
                    if (!isEmpty()) {
                        map.remove(array[1].element);
                        array[0] = std::move(array[1]);
                        array[1] = std::move(array[currentSize]);
                        array[currentSize--] = std::move(array[0]);
                        percolateDown(1);
                    }
                    return array[currentSize+1].element;
                }

                // Removes all elements from the heap and resets the size
                void makeEmpty() {
                    currentSize = 0;
                    map.makeEmpty();
                }

                // Returns the current number of elements in the heap
                int getSize() const {
                    return currentSize;
                }

                // Displays the contents of the priority queue in sorted order by priority
                void display() {
                    cout << "{ ";
                    if (currentSize > 0) {
                        int tmp = currentSize;
                        for (;;) {
                            cout << "(" << *deleteMin() << "," << array[currentSize+1].priority << ")";
                            if (currentSize) cout << ", ";
                            else break;
                        }
                        currentSize = tmp;
                        buildHeap();
                    }
                    cout << " }" << endl;
                }

                // Detailed display of heap and hash table structure for debugging
                void ddisplay() const {
                    cout << "[ 0:__, ";
                    for (size_t i = 1; i < array.size(); i++) {
                        cout << i << ":";
                        if (i <= currentSize) {
                            cout << "\033[32m" << "(" << *array[i].element << "," << array[i].priority << ")" << "\033[0m";
                        }
                        else cout << "__";
                        if (i != array.size()-1) {
                            cout << ", ";
                        }
                    }
                    cout << " ] // size=" << currentSize << endl;
                    map.ddisplay();
                }
        };
        // Internal binary heap using string pointers as elements and integers as priorities
        BinaryHeap<const std::string*, int> heap;
    public:
        // constructor creating an empty IndPQ.
        IndPQ() : heap() {}

        // Insert taskid with priority p.
        void insert(const std::string& taskid, int p) {
            heap.insert(&taskid, p);
        }

        // Remove and return (a reference to) a task ID with smallest priority.
        std::string& deleteMin() {
            return const_cast<std::string&>(*heap.deleteMin());
        }

        // Return (a reference to) a task ID with the smallest priority.
        std::string& getMin() {
            return const_cast<std::string&>(*heap.findMin());
        }

        // change the priority for taskid to p.
        void updatePriority(const std::string& taskid, int p) {
            heap.updatePriority(&taskid, p);
        }

        // remove taskid from the PQ
        void remove(const std::string& tid) {
            if (heap.updatePriority(&tid, -1)) {
                heap.deleteMin();
            }
        }

        // Return true if the PQ is empty, otherwise false.
        bool isEmpty() {
            return heap.isEmpty();
        }

        // Return the number of tasks in the PQ.
        int size() {
            return heap.getSize();
        }

        // Remove all tasks from the PQ.
        void clear() {
            heap.makeEmpty();
        }

        // prints out the queue contents.
        void display() {
            heap.display();
        }

        // prints out a representation of the data structures.
        void ddisplay() {
            heap.ddisplay();
        }
};
#endif