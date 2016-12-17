#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct CourseCatalog {
    char courseDivision[3];
    int courseDepartment, courseNumber, creditInt, creditDecimal;
    char courseTitle[33];
};

struct LinkedList {
    char grade[3];
    int year;
    char semester;
    struct CourseCatalog* cc;
    struct LinkedList* next;
};

int lineNum(FILE* fptr);
void loadData(FILE* fptr, struct CourseCatalog* cc, int count);
struct CourseCatalog * compareInfo(char* userInput, struct CourseCatalog* cc, int count);
int findCourse(struct CourseCatalog * cptr, struct LinkedList * transcript, int yr, char sm);
void courseIdentifier(char buffer[]);
int display(struct LinkedList * ts);
int compareSemester(int givenYear, char givenSem, int presentYear, char presentSem); 
void removeCourse(int year, char semester, struct LinkedList** transcript, struct CourseCatalog * cc);
int matchCourse(int givenYear, char givenSem, int presentYear, char presentSem, struct CourseCatalog * cc, struct LinkedList * p);
void addCourse(int year, char semester, char* grade, struct LinkedList** transcript,
                       struct CourseCatalog * cc);
double calculateGPA(struct LinkedList * transcript);
void storeInput(char temp[]);
void freeNode(struct LinkedList * transcript);  

