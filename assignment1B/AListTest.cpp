// Assignment 1B
// AListTest.cpp: Test program for AList class to verify its functionality

#include "AList.h"

int main() {
    cout << endl << "--- Testing AList Implementation ---" << endl;

    // Create an AList of integers
    AList<int> list;

    cout << endl << "Step 1: Initial state of the list." << endl;
    cout << endl << "Displaying list contents:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();

    // Test adding elements to the right
    cout << endl << "Step 2: Adding 42, 17, 88 to the right." << endl;
    list.addRight(42);
    list.addRight(17);
    list.addRight(88);
    cout << endl << "Displaying list contents after adding to the right:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();

    // Test adding elements to the left
    cout << endl << "Step 3: Adding 23, 9 to the left." << endl;
    list.addLeft(23);
    list.addLeft(9);
    cout << endl << "Displaying list contents after adding to the left:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();

    // Test removing elements from the right
    cout << endl << "Step 4: Removing one element from the right." << endl;
    cout << "        Removed element: " << list.removeRight() << endl;
    cout << endl << "Displaying list contents after removing from the right:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();

    // Test removing elements from the left
    cout << endl << "Step 5: Removing one element from the left." << endl;
    cout << "        Removed element: " << list.removeLeft() << endl;
    cout << endl << "Displaying list contents after removing from the left:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();

    // Test clearing the list
    cout << endl << "Step 6: Clearing the list." << endl;
    list.clear();
    cout << endl << "Displaying list contents after clearing:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();

    cout << endl << "--- End of Test Program ---" << endl << endl;
    return 0;
}