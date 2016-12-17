/* Homework 0, 600.120
 * Cheng-I Lai (Jeff) 
 * 5/28/2016 
 * clai24
 * clai24jhu.edu 
 *  */

#include <stdio.h>
#include <string.h>
#include <ctype.h> 

#define LENGTH 16 // input size 

int main(int argc, char* argv[])
{
    int i, division, j, lg, sign, credit1, credit2; 
    char course[LENGTH]; //stored the argument in a string 
    char *divisionNum[] = {"ME","BU","ED","EN","AS","PH","PY","SA"}; // represent the JHU division hosting a course 
    char div[3]; // stored the division number of the argument in a string 
    char dep[4]; // stored the department code of the argument in a string 
    char cc[4]; // stored the course code of the argument in a string 

    if (argc == 1) { // the command has no other arguments 
        printf("Usage: hw0 XX.###.###Gg#.#\n");
        return 1;  // exit program
    }

    strncpy(course, argv[1], LENGTH);  // copy to course string
    course[LENGTH-1] = '\0';   // make sure last character is null
    printf("course string: %s\n", course);  // echo input

    strncpy(div, course, 2); // copy the first two element of the argument to div[] i.e. EN 
    div[2] = '\0'; // append a null character 

    // determine the division number 
    for (i=0; i<8; i++) {
        if (strcmp(divisionNum[i], div) == 0) { 
            division = i;
            break; 
        }         
    } 
        
    // department code 
    j = 0; 
    while (course[j++] != '.')  
        ; // null statement 
    while (course[j] != '.') { 
        dep[j-3] = course[j];
        j++; 
    } 
    j++;
    dep[3] = '\0'; // apppend a null character 

    // course code 
    while (!(isalpha(course[j]))) {
        cc[j-7] = course[j]; 
        j++; 
    } 
    cc[3] = '\0'; //append a null character 

    // letter grade 
    switch (course[j++]) { 
        case 'A':
            lg = 0; 
            break; 
        case 'B': 
            lg = 1; 
            break; 
        case 'C':
            lg = 2; 
            break; 
        case 'D': 
            lg = 3; 
            break;
        case 'F': 
            lg = 4; 
            break; 
        case 'I': 
            lg = 5; 
            break;
        case 'S': 
            lg = 6;
            break;
        case 'U':
            lg = 7; 
            break;
    }

    // sign 
    switch (course[j++]) { 
        case '+':
            sign = 0; 
            break; 
        case '-': 
            sign = 1; 
            break;
        case '/':
            sign = 2;
            break;
    }

    //credits 
    credit1 = course[j++] - '0';
    j++;
    credit2 = ((course[j] - '0' == 0) ? 0 : 1);
         
    printf("Division: %d\nDepartment: %s\nCourse: %s\nGrade: %d %d\nCredits: %d %d\n",    
         division, dep, cc, lg, sign, credit1, credit2);            
    
    return 0;
}



