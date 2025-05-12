// Assignment 1B
// removeLeftTest.cpp: Tests AList removeLeft operation by attempting to remove from an empty list (testing assert)

#include "AList.h"

int main() {
    // Program title
    cout << endl << "--- AList removeLeft Testing Program ---" << endl;

    // Create an instance of AList
    cout << endl << "Step 1: Creating a new AList<int>" << endl;
    AList<int> list;

    // Add two elements using different methods
    cout << endl << "Step 2: Adding two integers" << endl;
    cout << "        Adding 1 to the left" << endl;
    list.addLeft(1);
    cout << "        Adding 2 to the right" << endl;
    list.addRight(2);
    
    // Display initial list
    cout << endl << "Step 3: Displaying initial list contents:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();
    
    // Remove elements from left
    cout << endl << "Step 4: Removing elements from the left" << endl;
    cout << "        Removing first element from left: " << list.removeLeft() << endl;
    cout << "        Removing second element from left: " << list.removeLeft() << endl;
    cout << endl << "List after second removal:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();

    // Attempt to remove from empty list
    cout << endl << "Step 5: Attempting to remove from an empty list" << endl;
    cout << "The following operation should trigger an assert and terminate the program" << endl;
    cout << "Removing from left using 'list.removeLeft();' ..." << endl << endl;

    // This should trigger the assert
    list.removeLeft();

    // This line should never be reached due to assert
    cout << endl << "If you see this message, assert failed to catch the error!" << endl;

    return 0;
}