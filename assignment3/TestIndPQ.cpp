// Assignment 3A
// TestIndPQ.cpp: Test driver for IndPQ class
#include "IndPQ.h"

int main() {
    std::cout << "\n===== TESTING IndPQ CLASS =====\n" << std::endl;

    // 1. Test constructor
    std::cout << "1. Testing IndPQ constructor:" << std::endl;
    std::cout << "   Creating empty priority queue..." << std::endl;
    IndPQ pq;
    std::cout << "   Actual structure:" << std::endl;
    pq.ddisplay();
    std::cout << std::endl;

    // 2. Test insert()
    std::cout << "2. Testing insert():" << std::endl;
    std::vector<std::string> tasks(10);
    for (int i = 0; i < 10; i++) {
        tasks[i] = "Task" + std::to_string(i);
    }
    
    std::cout << "   Inserting 10 tasks with priorities matching their indices..." << std::endl;
    for (int i = 9; i >= 0; i--) {
        std::cout << "   Inserting: " << tasks[i] << " with priority " << i << std::endl;
        pq.insert(tasks[i], i);
    }
    
    std::cout << "\n   Priority queue structure after insertions:" << std::endl;
    pq.ddisplay();
    std::cout << "\n   Priority queue contents (sorted by priority):" << std::endl;
    pq.display();
    std::cout << std::endl;

    // 3. Test updatePriority()
    std::cout << "3. Testing updatePriority():" << std::endl;
    std::cout << "   Updating Task0 priority from 0 to 9" << std::endl;
    pq.updatePriority(tasks[0], 9);
    std::cout << "   Updating Task9 priority from 9 to 0" << std::endl;
    pq.updatePriority(tasks[9], 0);
    std::cout << "   Attempting to update non-existent Task10 priority to 10 (should do nothing)" << std::endl;
    std::string nonExistent = "Task10";
    pq.updatePriority(nonExistent, 10);
    
    std::cout << "\n   Priority queue structure after priority updates:" << std::endl;
    pq.ddisplay();
    std::cout << std::endl;

    // 4. Test getMin()
    std::cout << "4. Testing getMin():" << std::endl;
    std::string& minTask = pq.getMin();
    std::cout << "   Minimum task (should be Task9): " << minTask << std::endl;
    std::cout << "   Comparing with vector element: " << tasks[9] << std::endl;
    std::cout << "   Values match: " << (minTask == tasks[9] ? "Yes" : "No") << std::endl;
    std::cout << "   Same memory location: " << (&minTask == &tasks[9] ? "Yes" : "No") << std::endl;
    
    std::cout << "   Appending '9' to the returned reference..." << std::endl;
    minTask += "9";
    std::cout << "   Modified task in vector: " << tasks[9] << std::endl;
    std::cout << "   Current minimum task (should be Task99): " << pq.getMin() << std::endl;
    std::cout << "   This shows the PQ stores pointers to original strings" << std::endl;
    std::cout << std::endl;

    // 5. Test deleteMin()
    std::cout << "5. Testing deleteMin():" << std::endl;
    std::cout << "   Adding '1' to Task1..." << std::endl;
    tasks[1] += "1";
    std::cout << "   Task1 is now: " << tasks[1] << std::endl;
    
    std::cout << "   Calling deleteMin() first time..." << std::endl;
    pq.deleteMin();
    std::cout << "   Calling deleteMin() second time..." << std::endl;
    std::string& deleted = pq.deleteMin();
    std::cout << "   Second deleteMin result (should be Task11): " << deleted << std::endl;
    std::cout << "   Comparing with vector element: " << tasks[1] << std::endl;
    std::cout << "   Values match: " << (deleted == tasks[1] ? "Yes" : "No") << std::endl;
    std::cout << "   Same memory location: " << (&deleted == &tasks[1] ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    // 6. Test remove()
    std::cout << "6. Testing remove():" << std::endl;
    std::cout << "   Removing Task3, Task5, and Task7..." << std::endl;
    pq.remove(tasks[3]);
    pq.remove(tasks[5]);
    pq.remove(tasks[7]);
    std::cout << "   Priority queue structure after removals:" << std::endl;
    pq.ddisplay();
    std::cout << std::endl;

    // 7. Test clear()
    std::cout << "7. Testing clear():" << std::endl;
    std::cout << "   Clearing the priority queue..." << std::endl;
    pq.clear();
    
    std::cout << "   Size after clearing (should be 0): " << pq.size() << std::endl;
    std::cout << "   Is empty? (should be true): " << (pq.isEmpty() ? "true" : "false") << std::endl;
    
    std::cout << "   Attempting to remove Task8 (should do nothing)..." << std::endl;
    pq.remove(tasks[8]);
    
    std::cout << "   Attempting to update Task4 priority to 0 (should do nothing)..." << std::endl;
    pq.updatePriority(tasks[4], 0);
    
    std::cout << "   Original Task2 string (should be unchanged): " << tasks[2] << std::endl;
    
    std::cout << "   Priority queue structure after clearing:" << std::endl;
    pq.ddisplay();
    
    return 0;
}