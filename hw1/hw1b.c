/* Homework 1b, 600.120 
 * Cheng-I Lai (Jeff) 
 * 6/02/2016
 * clai24 
 * clai24@jhu.edu 
 * */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <ctype.h> 

#define MAXLINE 2500 

void courseInfo(unsigned int course); 

int main() 
{ 
    int k, val; 
    unsigned int Course[MAXLINE]; // Store integers from courseInts.txt 
    
    FILE* fin = fopen("courseInts.txt", "r"); // input file mechanism
    if (fin == NULL) { 
        puts("falied to open file"); 
        exit(1); 
    } 
    
    // store the integers in the array Course 
    k = 0; // number of integers in courseInts.txt 
    val = 0; 
    while (fscanf(fin, "%d", &val) != EOF) { 
      Course[k] = val; 
      k++; 
    }

    // print out the user interface 
    char s[5]; 
    do { 
        printf("n - display the total number of courses\nd - list all courses from a particular department\nl - list all courses with a particular letter grade");
        printf("\nc - list all courses with at least a specified number of credits\ng - compute the GPA of all the courses with letter grades");
        printf("\nq - quit the program\nEnter letter of choice -> ");  
        
        scanf("%s", s); 
        char c = s[0];

        if (c == 'n' || c == 'N') { // display total number of courses in the Course string 
            printf("%d\n", k); 
        } else if (c == 'd' || c == 'D') { // list all course from a particular department 
            printf("What's your course department number? ");
            unsigned int s; 
            scanf("%u", &s);
            for (int l=0; l<k; l++) { // loop over every integer in the array 
                if ((Course[l] & (0x3FF << 19)) == (s << 19)) {  
                    // convert binary form to course information by calling helper function e.g. "EN.600.120B+3.5"
                    courseInfo(Course[l]);
                }
            } 
        } else if (c == 'l' || c == 'L') { // list all courses with a particular letter grade 
            printf("What's your grade? e.g. Enter \"A+\" or \"b-\": "); 
            unsigned int mask; 
            char grade[3]; // store user input 
            scanf("%s", grade);
            grade[2] = '\0'; // append NULL character 
           
            mask = 0; // determine the mask 
            switch (toupper(grade[0])) { 
                case 'A': break; 
                case 'B': mask |= (1 << 6); break; 
                case 'C': mask |= (2 << 6); break; 
                case 'D': mask |= (3 << 6); break;
                case 'F': mask |= (4 << 6); break; 
                case 'I': mask |= (5 << 6); break;
                case 'S': mask |= (6 << 6); break;
                case 'U': mask |= (7 << 6); break;
            } 
            switch (grade[1]) { 
                case '+': break;
                case '-': mask |= (1 << 4); break;
                case '/': mask |= (2 << 4); break;
            } 
            // bitmask operation 
            for (int l=0; l<k; l++) { // loop over every integer in the array 
                if ((Course[l] & (0x1F << 4)) == mask) { 
                    courseInfo(Course[l]); 
                }
            }
        } else if (c == 'c' || c == 'C') { // list all courses with at least a specified number of credits 
            printf("What's your credit? "); 
            unsigned int mask; 
            char credit[4]; // store user input 
            scanf("%s", credit); 
            credit[3] = 0; // append NULL character 

            mask = 0; // determine the mask 
            switch (credit[0]) { 
                case '0': break; 
                case '1': mask |= (1 << 1); break;
                case '2': mask |= (2 << 1); break; 
                case '3': mask |= (3 << 1); break; 
                case '4': mask |= (4 << 1); break; 
                case '5': mask |= (5 << 1); break;
            }
            switch (credit[2]) { 
                case '0': mask |= 0; break;
                case '5': mask |= 1; break;
            }
            
            // bitmask operation 
            for (int l=0; l<k; l++) { // loop over every integer in the array 
                if ((Course[l] & 0xF) >= mask) { // treat Course[l] as a number 
                    courseInfo(Course[l]);
                }
            }
        } else if (c == 'g' || c == 'G') { // compute culmulative GPA (skip course grades 'I', 'S', 'U')
            double totalCredit; 
            double sum; // sum of grade * credit 
            double gpa; 
            totalCredit = 0; 
            sum = 0; 

            for (int l=0; l<k; l++) { // loop over every integer in the array 
                // bitmask operation
                double  grade = 0.0;
                int count = 0; //  eliminate I,S,U
                switch ((Course[l] >> 6) & 0x7) { // determine the grade 
                    case 0: 
                        if (((Course[l] >> 4) & 2) == 2) 
                            grade = 4.0;
                        else if (((Course[l] >> 4) & 1) == 1) 
                            grade = 3.7; 
                        else 
                            grade = 4.0; 
                        count = 1;
                        break;
                    case 1: 
                        if (((Course[l] >> 4) & 2) == 2) 
                            grade = 3.0; 
                        else if (((Course[l] >> 4) & 1) == 1)
                            grade = 2.7;  
                        else 
                            grade = 3.3; 
                        count = 1;
                        break;
                    case 2: 
                        if (((Course[l] >> 4) & 2) == 2) 
                            grade = 2.0;
                        else if (((Course[l] >> 4) & 1) == 1) 
                            grade = 1.7; 
                        else 
                            grade = 2.3;
                        count = 1; 
                        break;
                    case 3: 
                        if (((Course[l] >> 4) & 2) == 2) 
                            grade = 1.0;
                        else if (((Course[l] >> 4) & 1) == 1) 
                            grade = 0.7;
                        else 
                            grade = 1.3; 
                        count = 1; 
                        break;
                    case 4: 
                        grade = 0.0; 
                        count = 1; 
                        break;
                }            
                switch ((Course[l] >> 1) & 0x7) { // determine the credit                 
                    case 0: 
                        if (Course[l] & 1) {
                            sum += grade * 0.5; 
                            totalCredit += count * 0.5; 
                        } else {
                            sum += grade * 0.0; 
                            totalCredit += count * 0.0;
                        }
                        break;
                    case 1: 
                        if (Course[l] & 1) {
                            sum += grade * 1.5; 
                            totalCredit += count * 1.5;
                        } else { 
                            sum += grade * 1.0;
                            totalCredit += count * 1.0;
                        }
                        break;
                    case 2: 
                        if (Course[l] & 1) {
                            sum += grade * 2.5;
                            totalCredit += count * 2.5;
                        } else { 
                            sum += grade * 2.0; 
                            totalCredit += count * 2.0;
                        }
                        break;
                    case 3: 
                        if (Course[l] & 1) {
                            sum += grade * 3.5; 
                            totalCredit += count * 3.5;
                        } else { 
                            sum += grade * 3.0; 
                            totalCredit += count * 3.0;
                        }
                        break;
                    case 4: 
                        if (Course[l] & 1) {
                            sum += grade * 4.5; 
                            totalCredit += count * 4.5; 
                        } else {
                            sum += grade * 4.0; 
                            totalCredit += count * 4.0;
                        }
                        break;
                    case 5: 
                        if (Course[l] & 1) {
                            sum += grade * 5.5; 
                            totalCredit += count * 5.5;
                        } else {
                            sum += grade * 5.0; 
                            totalCredit += count * 5.0; 
                        }
                        break;
                }
            } // end of for loop 

            gpa = sum / totalCredit; 
            printf("The average GPA is %.2f\n", gpa); 
        } else if (c == 'q' || c == 'Q') { // Quit the program 
            puts("See you next time."); 
            exit(1);
        } 

    } while (1); // program will keep running until user input q or Q
    return 0; 
}

void courseInfo(unsigned int course) 
{   // convert the given unsigned integer back to course information using bit mask 
    // print out course informaiton at the end of the function
    
    char lg, sign, credit1, credit2;    
    char cc[4]; // course code 
    char dep[4]; // department code 
    char div[3]; // division code 

    switch (course & 1) { // get credit2
        case 0: credit2 = '0'; break;
        case 1: credit2 = '5'; break;
    } 
    course >>= 1; // right shift to get rid of credit2 
    switch (course & (1 | (1 << 1) | (1 << 2))) { // get credit1
        case 0: credit1 = '0'; break;             
        case 1: credit1 = '1'; break; 
        case 2: credit1 = '2'; break; 
        case 3: credit1 = '3'; break; 
        case 4: credit1 = '4'; break;
        case 5: credit1 = '5'; break; 
    } 
    course >>= 3; // right shift to get rid of credit1 
    switch (course & (1 | (1 << 1))) { // get sign 
        case 0: sign = '+'; break;   
        case 1: sign = '-'; break; 
        case 2: sign = '/'; break; 
    } 
    course >>= 2; // right shift to get rid of sign 
    switch (course & (1 | (1 << 1) | (1 << 2))) { // get course grade 
        case 0: lg = 'A'; break; 
        case 1: lg = 'B'; break;
        case 2: lg = 'C'; break; 
        case 3: lg = 'D'; break; 
        case 4: lg = 'F'; break;
        case 5: lg = 'I'; break;
        case 6: lg = 'S'; break; 
        case 7: lg = 'U'; break;
    }
    course >>= 3; // right shift to get rid of course grade 
    sprintf(cc, "%03d", course & (0xFF | (1 << 8) | (1 << 9))); // store the course grade in a string 
    cc[3] = '\0'; // append NULL character 
    course >>= 10; // right shift to get rid of course grade 
    sprintf(dep, "%03d", course & (0xFF | (1 << 8) | (1 << 9))); // store the department grade in a string 
    dep[3] = '\0'; // append NULL character 
    course >>= 10; // right shift to get rid of department code 
    switch (course & (1 | (1 << 1) | (1 << 2))) { // get division number 
        case 0: strcpy(div, "ME"); break;
        case 1: strcpy(div, "BU"); break;
        case 2: strcpy(div, "ED"); break;
        case 3: strcpy(div, "EN"); break;
        case 4: strcpy(div, "AS"); break;
        case 5: strcpy(div, "PH"); break; 
        case 6: strcpy(div, "PY"); break;
        case 7: strcpy(div, "SA"); break;
    }
    div[2] = '\0'; // append NULL character 

    printf("%s.%s.%s%c%c%c.%c\n", div, dep, cc, lg, sign, credit1, credit2); // printout the course Info
}

