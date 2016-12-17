/* Intermediate Programming 
 * hw3 main 
 * Cheng-I Lai 
 * clai24 
 */

#include "hw3_function.h"

int main(int argc, char* argv[])
{
    char s[10]; // for user input
    if (argc == 1) {
        puts("Please provide a file.");
        return 1;
    }
    if (argv[1] == NULL) {
        puts("File is not valid.");
        return 1;
    }

    // Create Catalog by creating an dynamic array to store all the course information
    FILE* fptr = fopen(argv[1], "r");
    int lines = lineNum(fptr);
    struct CourseCatalog* cc =  malloc(sizeof(struct CourseCatalog) * lines);
    fclose(fptr);

    // open file again, load data into Catalog
    FILE* fptr2 = fopen(argv[1], "r");
    loadData(fptr2, cc, lines);
    fclose(fptr2);

    // initialize the linked list (student transcript)
    struct LinkedList* transcript = NULL;

    // User interface
    do {
        printf("Please enter your choice: ");
        fgets(s, 5, stdin);
        char c = s[0];
        c = toupper(c); // case insensitive
        if (c == 'Q') {
            freeNode(transcript); // free all allocated memory
            return 0;
        } else if (c == 'P') { // print out all course information
            struct CourseCatalog* cptr = cc;
            for (int i = 0; i < lines; i++) {
                printf("%s.%d.%d %d.%d %s\n", cptr->courseDivision, cptr->courseDepartment, cptr->courseNumber,
                       cptr->creditInt, cptr->creditDecimal, cptr->courseTitle);
                ++cptr;
            }
            printf("\n");
        } else if (c == 'C') { // Display information on a specific course
            char buffer[50];
            courseIdentifier(buffer);
            struct CourseCatalog* cptr = compareInfo(buffer, cc, lines);
            if (cptr == NULL)
                puts("absent\n");
            else
                printf("%d.%d %s\n\n", cptr->creditInt, cptr->creditDecimal, cptr->courseTitle);
        } else if (c == 'T') { // Update the title of a specific course
            char buffer[50];
            courseIdentifier(buffer);
            printf("Please enter the desired course title (32 characters max): ");
            char newT[33];
            fgets(newT, 33, stdin);  // store user input in a string
            storeInput(newT);
            struct CourseCatalog* cptr = compareInfo(buffer, cc, lines);
            if (cptr == NULL)
                puts("absent\n");
            else { // change to the desired course title
                strcpy(cptr->courseTitle, newT);
                puts("updated\n");
            }
        } else if (c == 'R') { // Update the credit assignment of a specific course
            char buffer[50], temp[5];
            courseIdentifier(buffer);
            printf("Please enter the desired credit assignment: ");
            int integer, decimal;
            fgets(temp, 5, stdin); // store user input
            storeInput(temp);
            integer = temp[0] - '0';
            decimal = temp[2] - '0';
            struct CourseCatalog* cptr = compareInfo(buffer, cc, lines);
            if (cptr == NULL)
                puts("absent\n");
            else { // change to the desired credit assignment
                cptr->creditInt = integer;
                cptr->creditDecimal = decimal;
                puts("updated\n");
            }
        } else if (c == 'A') { // Add a course to the student transcript
            char buffer[50], temp[50];
            courseIdentifier(buffer);
            int yr;
            char sm, Gg[3];
            printf("Please enter the semester and grade (yyyy.s Gg): ");
            fgets(temp, 50, stdin); // store user input
            storeInput(temp);
            sscanf(temp, "%4d.%1c %2s", &yr, &sm, Gg);
            Gg[3] = 0;
            struct CourseCatalog* cptr = compareInfo(buffer, cc, lines);
            if (cptr == NULL)
                puts("invalid\n");
            else { // the course user entered is valid
                if (findCourse(cptr, transcript, yr, sm) == 1)
                    puts("present\n"); // course is in the transcript already
                else { // course is not in the transcript, so add to it
                    addCourse(yr, sm, Gg, &transcript, cptr);
                    puts("added\n"); // course added to the transcript
                }
            }
        } else if (c == 'D') { // remove a course from the student transcript
            char buffer[50], temp[50];
            courseIdentifier(buffer);
            int yr;
            char sm;
            printf("Please enter the semester (yyyy.s): ");
            fgets(temp, 50, stdin); // store user input
            storeInput(temp);
            sscanf(temp, "%4d.%1c", &yr, &sm);
            struct CourseCatalog* cptr =  compareInfo(buffer, cc, lines);
            if (cptr == NULL)
                puts("invalid\n");
            else { // the course user entered is valid
                if (findCourse(cptr, transcript, yr, sm) == 0)
                    puts("absent\n"); // course is not in the transcript
                else { // course is in the transcript, so remove from it
                    removeCourse(yr, sm, &transcript, cptr);
                    puts("removed\n"); // course removed from  the transcript
                }
            }
        } else if (c == 'I') { // Display the current transcript
            if (display(transcript) == 0)
                puts("transcript empty\n");
        } else if (c == 'G') { // computer the cumulative GPA for the student
            printf("%.2f\n\n", calculateGPA(transcript));
        } else {
            puts("Invalid menu choice.\n");
        }
    } while (1);

    return 0;
}

