# Intermediate Programming 
# hw3 Makefile 
# Cheng-I Lai 
# clai24 

CC = gcc
FLAGS = -std=c99 -Wall -Wextra -pedantic -Wconversion -g

all: hw3 test_hw3

# Links the hw3 executable 
hw3: hw3.o hw3_function.o 
	$(CC) -o hw3 hw3.o hw3_function.o 

# Compiles hw3.c into an object file 
hw3.o: hw3.c hw3_function.h 
	$(CC) $(CFLAGS) -c hw3.c 

# Links the test_dnasearch executable
test_hw3: test_hw3.o hw3_function.o
	$(CC) -o test_hw3 test_hw3.o hw3_function.o

# Compiles dnasearch.c into an object file
hw3_function.o: hw3_function.c hw3_function.h
	$(CC) $(CFLAGS) -c hw3_function.c

# Compiles test_dnasearch.c into an object file
test_hw3.o: test_hw3.c hw3_function.h
	$(CC) $(CFLAGS) -c test_hw3.c

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o test_hw3 hw3
	
