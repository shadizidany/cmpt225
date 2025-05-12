// Assignment 1B
// addRightTest.cpp: Tests AList addRight operation by attempting to exceed capacity (testing assert)

#include "AList.h"

int main() {
    // Program title
    cout << endl << "--- AList addRight Testing Program ---" << endl;

    // Create an instance of AList
    cout << endl << "Step 1: Creating a new AList<int>" << endl;
    AList<int> list;

    // Add 12 elements using addRight
    cout << endl << "Step 2: Adding numbers 1 through 12 using addRight()" << endl;

    for (int i = 1; i <= 12; i++) {
        list.addRight(i);
    }

    // Display the current state of the list
    cout << endl << "Step 3: Displaying the list contents after adding 12 elements:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();

    // Attempt to exceed capacity
    cout << endl << "Step 4: Attempting to add one more element beyond capacity" << endl
         << "The following operation should trigger an assert and terminate the program" << endl
         << "Adding 13 using 'list.addRight(13);' ..." << endl << endl;

    // This should trigger the assert
    list.addRight(13);

    // This line should never be reached due to assert
    cout << endl << "If you see this message, assert failed to catch the error!" << endl;

    return 0;
}