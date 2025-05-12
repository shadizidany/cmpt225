// Assignment 2A
// TestBiMap.cpp: Test Program for BiMap implementation
#include "BiMap.h"
#include <string>

int main() {
    cout << "\n=== Step 1: Testing initial BiMap creation ===\n\n";
    BiMap<char, int> bm;
    cout << "Created BiMap<char,int> with default size (11)\n";
    cout << "\nInitial BiMap state\n\n";
    cout << "Display:\n\n";
    bm.display();
    cout << "\nDetailed display:\n\n";
    bm.ddisplay();

    cout << "\n=== Step 2: Testing insert operations ===\n\n";
    // Regular inserts
    cout << "Inserting pair <A,1>: ";
    cout << (bm.insert('A', 1) ? "SUCCESS" : "FAILED") << endl;
    
    cout << "Inserting pair <B,2>: ";
    cout << (bm.insert('B', 2) ? "SUCCESS" : "FAILED") << endl;
    
    cout << "Inserting pair <C,3>: ";
    cout << (bm.insert('C', 3) ? "SUCCESS" : "FAILED") << endl;

    cout << "Inserting pair <D,4>: ";
    cout << (bm.insert('D', 4) ? "SUCCESS" : "FAILED") << endl;

    cout << "Inserting pair <E,5>: ";
    cout << (bm.insert('E', 5) ? "SUCCESS" : "FAILED") << endl;

    cout << "\nBiMap state after insertion\n\n";
    cout << "Display:\n\n";
    bm.display();
    cout << "\nDetailed display:\n\n";
    bm.ddisplay();

    // Duplicate insert
    cout << "\nTrying to insert duplicate pair <A,1>: ";
    cout << (bm.insert('A', 1) ? "SUCCESS" : "FAILED") << endl;

    // Key collision
    cout << "Trying to insert key collision <B,6>: ";
    cout << (bm.insert('B', 6) ? "SUCCESS" : "FAILED") << endl;

    // Value collision
    cout << "Trying to insert value collision <F,3>: ";
    cout << (bm.insert('F', 3) ? "SUCCESS" : "FAILED") << endl;

    cout << "\nBiMap state after attempting invalid insertion\n\n";
    cout << "Display:\n\n";
    bm.display();
    cout << "\nDetailed display:\n\n";
    bm.ddisplay();

    cout << "\n=== Step 3: Testing contains operations ===\n\n";
    // Testing existing entries
    cout << "Testing containsKey('D'): ";
    cout << (bm.containsKey('D') ? "TRUE" : "FALSE") << endl;
    
    cout << "Testing containsVal(5): ";
    cout << (bm.containsVal(5) ? "TRUE" : "FALSE") << endl;
    
    // Testing non-existing entries
    cout << "Testing containsKey('G'): ";
    cout << (bm.containsKey('G') ? "TRUE" : "FALSE") << endl;

    cout << "Testing containsVal(7): ";
    cout << (bm.containsVal(7) ? "TRUE" : "FALSE") << endl;

    cout << "\n=== Step 4: Testing remove operations ===\n\n";
    // Testing non-existing removals
    cout << "Trying to remove non-existing key <H>: ";
    cout << (bm.removeKey('H') ? "SUCCESS" : "FAILED") << endl;
    
    cout << "Trying to remove non-existing value <8>: ";
    cout << (bm.removeVal(8) ? "SUCCESS" : "FAILED") << endl;

    cout << "\nBiMap state after attempting invalid removals\n\n";
    cout << "Display:\n\n";
    bm.display();
    cout << "\nDetailed display:\n\n";
    bm.ddisplay();

    // Testing valid removals
    cout << "\nRemoving existing key <A>: ";
    cout << (bm.removeKey('A') ? "SUCCESS" : "FAILED") << endl;
    
    cout << "Removing existing value <2>: ";
    cout << (bm.removeVal(2) ? "SUCCESS" : "FAILED") << endl;

    cout << "\nBiMap state after valid removals\n\n";
    cout << "Display:\n\n";
    bm.display();
    cout << "\nDetailed display:\n\n";
    bm.ddisplay();

    cout << "\n=== Step 5: Testing get operations ===\n\n";
    // Testing valid gets
    cout << "Getting value for key <C>: " << bm.getVal('C') << endl;
    cout << "Getting key for value <4>: " << bm.getKey(4) << endl;
    
    // Testing invalid gets (will print garbage values)
    cout << "Getting value for non-existing key <I> (garbage value): " << bm.getVal('I') << endl;
    cout << "Getting key for non-existing value <0> (garbage value): " << bm.getKey(0) << endl;

    cout << "\n=== Step 6: Testing getSize and makeEmpty ===\n\n";
    cout << "Current size of BiMap (number of pairs): " << bm.getSize() << endl;
    
    cout << "Calling makeEmpty()...\n";
    bm.makeEmpty();
    cout << "Size after makeEmpty: " << bm.getSize() << endl;
    
    cout << "\nBiMap state after makeEmpty\n\n";
    cout << "Display:\n\n";
    bm.display();
    cout << "\nDetailed display:\n\n";
    bm.ddisplay();

    cout << "\n=== Step 7: Testing rehash functionality ===\n\n";
    BiMap<string, double> bm2(5);
    cout << "Created new BiMap<string,double> with size 5\n\n";
    
    cout << "Inserting pair <XX,-1.1>: ";
    cout << (bm2.insert("XX", -1.1) ? "SUCCESS" : "FAILED") << endl;
    
    cout << "Inserting pair <YY,-2.2>: ";
    cout << (bm2.insert("YY", -2.2) ? "SUCCESS" : "FAILED") << endl;

    cout << "\nBiMap state before triggering rehash\n\n";
    cout << "Display:\n\n";
    bm2.display();
    cout << "\nDetailed display:\n\n";
    bm2.ddisplay();

    cout << "\nInserting pair <ZZ,0.3> to trigger rehash (\u03BB>0.5): ";
    cout << (bm2.insert("ZZ", 0.3) ? "SUCCESS" : "FAILED") << endl;

    cout << "\nBiMap state after rehash (should be size 11)\n\n";
    cout << "Display:\n\n";
    bm2.display();
    cout << "\nDetailed display:\n\n";
    bm2.ddisplay();

    cout << "\n=== End of Test Program ===\n\n";
    
    return 0;
}