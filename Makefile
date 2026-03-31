CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

BST_OBJ = BST.o
DEMO_EXE = demo
TEST_EXE = test

# Build everything
all: $(DEMO_EXE) $(TEST_EXE)

# Build the module .o from .h and .cpp
$(BST_OBJ): BST.cpp BST.h
	$(CXX) $(CXXFLAGS) -c BST.cpp -o $(BST_OBJ)

# Build demo
$(DEMO_EXE): demo.cpp $(BST_OBJ)
	$(CXX) $(CXXFLAGS) demo.cpp $(BST_OBJ) -o $(DEMO_EXE)

# Run demo
run_demo: $(DEMO_EXE)
	./$(DEMO_EXE)

# Build test
$(TEST_EXE): test.cpp $(BST_OBJ)
	$(CXX) $(CXXFLAGS) test.cpp $(BST_OBJ) -o $(TEST_EXE)

# Run test
run_test: $(TEST_EXE)
	./$(TEST_EXE)

# Clean everything
clean:
	rm -f $(BST_OBJ) $(DEMO_EXE) $(TEST_EXE) log.txt

# Rebuild from scratch
rebuild: clean all

.PHONY: all run_demo run_test clean rebuild