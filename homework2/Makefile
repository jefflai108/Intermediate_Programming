CC = gcc
FLAGS = -std=c99 -Wall -Wextra -pedantic -Wconversion -g

all: hw2 test_dnasearch 

# Links the hw2 executable 
hw2: hw2.o dnasearch.o 
	$(CC) -o hw2 hw2.o dnasearch.o 

# Compiles hw2.c into an object file 
hw2.o: hw2.c dnasearch.h 
	$(CC) $(CFLAGS) -c hw2.c 

# Links the test_dnasearch executable
test_dnasearch: test_dnasearch.o dnasearch.o
	$(CC) -o test_dnasearch test_dnasearch.o dnasearch.o

# Compiles dnasearch.c into an object file
dnasearch.o: dnasearch.c dnasearch.h
	$(CC) $(CFLAGS) -c dnasearch.c

# Compiles test_dnasearch.c into an object file
test_dnasearch.o: test_dnasearch.c dnasearch.h
	$(CC) $(CFLAGS) -c test_dnasearch.c

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o test_dnasearch hw2
	
