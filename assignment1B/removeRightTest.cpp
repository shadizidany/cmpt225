// Assignment 1B
// removeRightTest.cpp: Tests AList removeRight operation by attempting to remove from an empty list (testing assert)

#include "AList.h"

int main() {
    // Program title
    cout << endl << "--- AList removeRight Testing Program ---" << endl;
    
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
    
    // Remove elements from right
    cout << endl << "Step 4: Removing elements from the right" << endl;
    cout << "        Removing first element from right: " << list.removeRight() << endl;
    cout << "        Removing second element from right: " << list.removeRight() << endl;
    cout << endl << "List after second removal:" << endl << endl;
    list.display();
    cout << endl << "Displaying debugging information:" << endl << endl;
    list.ddisplay();
    
    // Attempt to remove from empty list
    cout << endl << "Step 5: Attempting to remove from an empty list" << endl;
    cout << "The following operation should trigger an assert and terminate the program" << endl;
    cout << "Removing from right using 'list.removeRight();' ..." << endl << endl;

    // This should trigger the assert
    list.removeRight();

    // This line should never be reached due to assert
    cout << endl << "If you see this message, assert failed to catch the error!" << endl;

    return 0;
}