# Define the target executable and its dependencies
AListTest: AListTest.cpp AList.h
	g++ -Wall AListTest.cpp -o AListTest

# The 'all' target depends on the executable target
all: AListTest

# Clean target to remove the compiled executable
clean:
	rm -f AListTest