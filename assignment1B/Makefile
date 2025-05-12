# Assignment 1B
# Makefile for compiling and running AList tests

# Define the target executable and its dependencies
AListTest: AListTest.cpp AList.h
	g++ -Wall AListTest.cpp -o AListTest

# Compile individual test programs for AList operations
addLeftTest: addLeftTest.cpp AList.h
	g++ -Wall addLeftTest.cpp -o addLeftTest

addRightTest: addRightTest.cpp AList.h
	g++ -Wall addRightTest.cpp -o addRightTest

removeLeftTest: removeLeftTest.cpp AList.h
	g++ -Wall removeLeftTest.cpp -o removeLeftTest

removeRightTest: removeRightTest.cpp AList.h
	g++ -Wall removeRightTest.cpp -o removeRightTest

# Compile all test executables
all: AListTest addLeftTest addRightTest removeLeftTest removeRightTest

# Run all test executables for AList operations
run: addLeftTest addRightTest removeLeftTest removeRightTest
	-./addLeftTest
	-./addRightTest
	-./removeLeftTest
	-./removeRightTest

# Clean up compiled executables
clean:
	rm -f AListTest addLeftTest addRightTest removeLeftTest removeRightTest