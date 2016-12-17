# Intermediate Programming 
# hw4 Makefile 
# Cheng-I Lai 
# clai24 

CXX = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

all: main unit
	
# Links the hw4a executable 
main: main.o class.o
	$(CXX) -o main main.o class.o  

unit: unit.o class.o 
	$(CXX) -o unit unit.o class.o 

unit.o: unit.cpp header.h 
	$(CXX) $(CFLAGS) -c unit.cpp

# Compiles hw4a.c into an object file
main.o: main.cpp header.h 
	$(CXX) $(CFLAGS) -c main.cpp 

# Compiles test_hw4b.cpp into an object file
class.o: class.cpp header.h
	$(CXX) $(CFLAGS) -c class.cpp 

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o main class 
	
