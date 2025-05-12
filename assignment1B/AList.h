// Assignment 1B
// AList.h: Deque implementation using a circular array

#ifndef ALIST_H
#define ALIST_H
// #define NDEBUG // uncomment to disable assert()
#include <cassert>
#include <iostream>
using namespace std;

template <typename Object>
class AList {
  public:
    // Default constructor initializing an empty list with a capacity of 12
    AList() {
      theCapacity = 12;
      objects = new Object[theCapacity];
      theSize = 0;
      left = 0; // array index of location just before the left-most list element
      right = 1; // array index just past the right-most list element
    }

    // Destructor to deallocate the dynamic array
    ~AList() {
      delete[] objects;
    }

    // Check if the list is empty
    bool empty() const {
      return theSize == 0;
    }

    // Return the number of elements in the list
    int size() const {
      return theSize;
    }

    // Clear the list by resetting indices and size
    void clear() {
      left = theSize = 0;
      right = 1;
    }

    // Operations:

    // Add an element to the left end of the list
    // The list must not be at full capacity (theSize < theCapacity)
    // If the list is full, adding an element will cause an assertion failure
    void addLeft(const Object x) {
      assert(theSize < theCapacity && "Error: Cannot add beyond list capacity");
      theSize++;
      objects[left] = x;
      left = (left - 1 + theCapacity) % theCapacity;
    }

    // Add an element to the right end of the list
    // The list must not be at full capacity (theSize < theCapacity)
    // If the list is full, adding an element will cause an assertion failure
    void addRight(const Object x) {
      assert(theSize < theCapacity && "Error: Cannot add beyond list capacity");
      theSize++;
      objects[right] = x;
      right = (right+1) % theCapacity;
    }

    // Remove and return the element from the right end
    // The list must not be empty (theSize > 0)
    // If the list is empty, attempting to remove an element will cause an assertion failure
    Object removeRight() {
      assert(theSize > 0 && "Error: Cannot remove from an empty list");
      theSize--;
      right = (right - 1 + theCapacity) % theCapacity;
      return objects[right];
    }

    // Remove and return the element from the left end
    // The list must not be empty (theSize > 0)
    // If the list is empty, attempting to remove an element will cause an assertion failure
    Object removeLeft() {
      assert(theSize > 0 && "Error: Cannot remove from an empty list");
      theSize--;
      left = (left+1) % theCapacity;
      return objects[left];
    }

    // Display the contents of the list
    void display() const {
      if (!theSize) {
        cout << "List is Empty" << endl;
      }
      else {
        int i = (left+1) % theCapacity;
        do {
          cout << "objects[" << i << "]: " << objects[i] << endl;
          i = (i+1) % theCapacity;
        } while (i != right);
      }
    }

    // Display the entire array and relevant variables for debugging
    void ddisplay() const {
      cout << "theCapacity: " << theCapacity << endl
           << "theSize: "     << theSize     << endl
           << "left: "        << left        << endl
           << "right: "       << right       << endl
           << "---------------"              << endl;
      for (int i = 0; i < theCapacity; i++) {
        cout << "objects[" << i << "]: " << objects[i] << endl;
      }
    }

  private:
    int left;
    int right;
    int theSize;
    int theCapacity;
    Object* objects;
};

#endif