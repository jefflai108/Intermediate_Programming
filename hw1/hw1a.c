/* Homework 1a, 600.120
 * Cheng-I Lai (Jeff) 
 * 5/31/2016 
 * clai24
 * clai24jhu.edu 
 * */

#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 
#define LENGTH 16 // size of each line 

int main(int argc, char* argv[]) 
{ 
    int c; 
    char course[LENGTH]; // stored the argument in a string 

    if (argc == 1) { // the command has no other arguments 
        printf("Usage: hw0 XX.###.###Gg#.#\n");
        return 1;  // exit program
    }
    
    FILE* fout = fopen("courseInts.txt", "w"); 
    FILE* fptr = fopen(argv[1], "r"); // open the file  
    if (fptr == NULL) { // check if its NULL
        puts("failed to open file"); 
        return 1; //exit program
    } 

    do { // super big do-while loop 
        
        unsigned int toBinary; // the binary form 

        // get the course string 
        c = fgetc(fptr); 
        if (feof(fptr)) 
            break; // doen scanning through courseData.txt 
        
        int k = 0; 
        while (c != '\n') { // copy to course string 
            course[k++] = c;
            c = fgetc(fptr); // move the pointer to the next character 
        } 
        course[LENGTH-1] = '\0'; // make sure last character is NULL 
        
        // append hw0 code here 
        int i, division, j, lg, sign, credit1, credit2; 
        char *divisionNum[] = {"ME","BU","ED","EN","AS","PH","PY","SA"}; // represent the JHU division hosting a course 
        char div[3]; // stored the division number of the argument in a string 
        char dep[4]; // stored the department code of the argument in a string 
        char cc[4]; // stored the course code of the argument in a string 

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

        // credits 
        credit1 = course[j++] - '0';
        j++;
        credit2 = ((course[j] - '0' == 0) ? 0 : 1);
        
        // convert to binary from
        toBinary = 0; 
        int depInt, ccInt; 
        depInt = atoi(dep);
        ccInt  = atoi(cc); // convert string to integer 
        
        // store it in toBinary with bitwise operation 
        toBinary = toBinary | (division << 29);
        toBinary = toBinary | (depInt << 19);
        toBinary = toBinary | (ccInt << 9);
        toBinary = toBinary | (lg << 6); 
        toBinary = toBinary | (sign << 4); 
        toBinary = toBinary | (credit1 << 1); 
        toBinary = toBinary | credit2;
     
        fprintf(fout, "%u\n", toBinary); //write to file courseInts.txt        
        
        printf("%s  %u  ", course, toBinary); // echo the input and output to the display
        for (int n=0; n< 32; n++)  { // print out binary form
            if (toBinary & (1 << 31))  
                printf("1"); 
            else   
                printf("0"); 
            toBinary <<= 1;
        } 
        printf("\n"); 

    } while (1); 
    
    fclose(fptr); 
    fclose(fout);
    return 0; 
} 


         
    

