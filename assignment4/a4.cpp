// Assignment 4
// a4.cpp: Performance comparison between AVLTree, BST, SplayTree
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SplayTree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main() {
    cout << "\nComparing AVL Tree, Binary Search Tree, and Splay Tree performance ..." << endl;

    // Define constants for set sizes
    const int n1 = 10;
    // const int n1 = 100000;
    const int n2 = 2 * n1;
    
    cout << "Creating a vector with size " << n2 << endl;
    
    // Create a vector of specified size
    vector<int> vec(n2);
    
    // Fill vec with numbers from 0 to (n2 - 1)
    cout << "Filling vec with numbers from 0 to " << (n2 - 1) << endl;
    for (int i = 0; i < n2; i++) {
        vec[i] = i;
    }
    
    // Randomly shuffle vec
    cout << "Set2: Randomly shuffling vec ..." << endl;
    random_device rd;
    mt19937 g(rd());
    shuffle(vec.begin(), vec.end(), g);
    
    // Set1 = vec[vec[i]]
    cout << "Set1: { vec[ vec[ i ] ] } for i = 0, 1, 2, ..., " << (n1 - 1) << endl;

    // Create instances of the three tree types
    cout << "Creating 6 tree instances (2 of each) ..." << endl;
    AvlTree<int> avlt1, avlt2;
    BinarySearchTree<int> bst1, bst2;
    SplayTree<int> splyt1, splyt2;
    
    // Create vector to store duration measurements
    vector<double> dur(12);
    
    // Insert set1 into avlt1 and measure time
    cout << "Building AVLTree1 from set1 ..." << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n1; i++) {
        avlt1.insert(vec[vec[i]]);
    }
    auto end = high_resolution_clock::now();
    dur[0] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Insert set1 into bst1 and measure time
    cout << "Building BinarySearchTree1 from set1 ..." << endl;
    start = high_resolution_clock::now();
    for (int i = 0; i < n1; i++) {
        bst1.insert(vec[vec[i]]);
    }
    end = high_resolution_clock::now();
    dur[1] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Insert set1 into splyt1 and measure time
    cout << "Building SplayTree1 from set1 ..." << endl;
    start = high_resolution_clock::now();
    for (int i = 0; i < n1; i++) {
        splyt1.insert(vec[vec[i]]);
    }
    end = high_resolution_clock::now();
    dur[2] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Insert set2 (vec) into avlt2 and measure time
    cout << "Building AVLTree2 from set2 ..." << endl;
    start = high_resolution_clock::now();
    for (int value : vec) {
        avlt2.insert(value);
    }
    end = high_resolution_clock::now();
    dur[3] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Insert set2 (vec) into bst2 and measure time
    cout << "Building BinarySearchTree2 from set2 ..." << endl;
    start = high_resolution_clock::now();
    for (int value : vec) {
        bst2.insert(value);
    }
    end = high_resolution_clock::now();
    dur[4] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Insert set2 (vec) into splyt2 and measure time
    cout << "Building SplayTree2 from set2 ..." << endl;
    start = high_resolution_clock::now();
    for (int value : vec) {
        splyt2.insert(value);
    }
    end = high_resolution_clock::now();
    dur[5] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Run counteven() on avlt1 and measure time
    cout << "Performing traversal on AVLTree1 ..." << endl;
    start = high_resolution_clock::now();
    avlt1.counteven();
    end = high_resolution_clock::now();
    dur[6] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Run counteven() on bst1 and measure time
    cout << "Performing traversal on BinarySearchTree1 ..." << endl;
    start = high_resolution_clock::now();
    bst1.counteven();
    end = high_resolution_clock::now();
    dur[7] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Run counteven() on splyt1 and measure time
    cout << "Performing traversal on SplayTree1 ..." << endl;
    start = high_resolution_clock::now();
    splyt1.counteven();
    end = high_resolution_clock::now();
    dur[8] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Run counteven() on avlt2 and measure time
    cout << "Performing traversal on AVLTree2 ..." << endl;
    start = high_resolution_clock::now();
    avlt2.counteven();
    end = high_resolution_clock::now();
    dur[9] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Run counteven() on bst2 and measure time
    cout << "Performing traversal on BinarySearchTree2 ..." << endl;
    start = high_resolution_clock::now();
    bst2.counteven();
    end = high_resolution_clock::now();
    dur[10] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Run counteven() on splyt2 and measure time
    cout << "Performing traversal on SplayTree2 ..." << endl;
    start = high_resolution_clock::now();
    splyt2.counteven();
    end = high_resolution_clock::now();
    dur[11] = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Print info about set1 and trees
    cout << "\n==========================================================\n";
    cout << "Printing trees containing set1 elements (n1 = " << n1 << ")" << endl;
    cout << "set1 contents: ";
    for (int i = 0; i < n1; i++) {
        cout << vec[vec[i]];
        if (i < n1 - 1) cout << ", ";
    }
    cout << endl << endl;
    
    // Print AVL Tree 1
    cout << "AVLTree1:" << endl;
    avlt1.tdisplay();
    cout << endl;
    
    // Print Binary Search Tree 1
    cout << "BinarySearchTree1:" << endl;
    bst1.tdisplay();
    cout << endl;
    
    // Print Splay Tree 1
    cout << "SplayTree1:" << endl;
    splyt1.tdisplay();
    cout << endl;
    
    // Print info about set2 and trees
    cout << "\n==========================================================\n";
    cout << "Printing trees containing set2 elements (n2 = " << n2 << ")" << endl;
    cout << "set2 contents: ";
    for (int i = 0; i < n2; i++) {
        cout << vec[i];
        if (i < n2 - 1) cout << ", ";
    }
    cout << endl << endl;
    
    // Print AVL Tree 2
    cout << "AVLTree2:" << endl;
    avlt2.tdisplay();
    cout << endl;
    
    // Print Binary Search Tree 2
    cout << "BinarySearchTree2:" << endl;
    bst2.tdisplay();
    cout << endl;
    
    // Print Splay Tree 2
    cout << "SplayTree2:" << endl;
    splyt2.tdisplay();
    cout << endl;

    // Print summary table of all measurements
    cout << "\n=======================Shadi Zidany=======================";
    cout << "\n========================000000000=========================";
    cout << "\n==========================cmptid==========================\n\n";
    cout << "Data Structures: AVL Tree, Binary Search Tree (BST), Splay Tree\n";
    cout << "Set Sizes: n1 = " << n1 << ", n2 = " << n2 << endl;
    cout << "\nSummary of Time Measurements (in millisecond):\n\n"; // ms
    cout << setw(30) << left << "Operation" << setw(15) << "AVL Tree" << setw(15) << "BST" << setw(15) << "Splay Tree" << endl;
    cout << string(75, '-') << endl;
    cout << fixed << setprecision(2); // Set fixed notation with 2 decimal places
    cout << setw(30) << "Insert set1" << setw(15) << dur[0] << setw(15) << dur[1] << setw(15) << dur[2] << endl;
    cout << setw(30) << "Insert set2" << setw(15) << dur[3] << setw(15) << dur[4] << setw(15) << dur[5] << endl;
    cout << setw(30) << "Traversal set1" << setw(15) << dur[6] << setw(15) << dur[7] << setw(15) << dur[8] << endl;
    cout << setw(30) << "Traversal set2" << setw(15) << dur[9] << setw(15) << dur[10] << setw(15) << dur[11] << endl;

    cout << endl;
    return 0;
}