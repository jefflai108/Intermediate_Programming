# Intermediate Programming 
# hw4 Makefile 
# Cheng-I Lai 
# clai24 

CXX = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic

all: hw4a hw4b test_hw4a test_hw4b
	
# Links the hw4a executable 
hw4a: hw4a.o 
	$(CXX) -o hw4a hw4a.o  

# Compiles hw4a.c into an object file 
hw4a.o: hw4a.cpp header_hw4.h 
	$(CXX) $(CFLAGS) -c hw4a.cpp 

# Links the hw4b executable 
hw4b: hw4b.o 
	$(CXX) -o hw4b hw4b.o  

# Compiles hw4b.c into an object file 
hw4b.o: hw4b.cpp header_hw4.h 
	$(CXX) $(CFLAGS) -c hw4b.cpp 

# Links the executable
test_hw4a: test_hw4a.o 
	$(CXX) -o test_hw4a test_hw4a.o 

# Compiles test_hw4a.cpp into an object file
test_hw4a.o: test_hw4a.cpp header_hw4.h
	$(CXX) $(CFLAGS) -c test_hw4a.cpp 

# Links the executable
test_hw4b: test_hw4b.o 
	$(CXX) -o test_hw4b test_hw4b.o 

# Compiles test_hw4b.cpp into an object file
test_hw4b.o: test_hw4b.cpp header_hw4.h
	$(CXX) $(CFLAGS) -c test_hw4b.cpp 

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o test_hw4b hw4b test_hw4a hw4a 
	
