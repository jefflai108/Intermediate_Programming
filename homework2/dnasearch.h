/*
 * 600.120 Intermediate Programming 
 * homework 2 
 * Cheng-I Lai 
 * clai24 
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 

#define MAXSIZE 15000

int validText(FILE *fptr, char data[MAXSIZE]); 
int validPattern(char input[], char text[]);
int patternMatch(char pattern[], char text[], char buffer[]); 
