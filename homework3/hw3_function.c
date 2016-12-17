/* Intermediate Programming 
 * hw3 functions 
 * Cheng-I Lai 
 * clai24
 */

#include "hw3_function.h" 

        void freeNode(struct LinkedList * transcript) { // free all allocated memory 
                struct LinkedList * cursor = transcript; 
                struct LinkedList * p;
                while (cursor->next != NULL) { 
                        p = cursor; 
                        cursor = cursor->next; 
                        free(p); 
                } 
        } 

        void storeInput(char temp[]) { 
            int length = strlen(temp); 
            if (temp[length-1] == '\n') 
                temp[length-1] = 0; // get rid of new lines character 
        } 

        double calculateGPA(struct LinkedList * transcript) { 
            // calculate the GPA, round it to 2 decimal and print it. 
            double gpa, creditSum = 0.0, sum = 0.0, credit, creditInt, creditDecimal; 
            if (transcript == NULL) { 
                return 0.00; 
            }
            while (transcript != NULL) { 
                creditInt = (double)transcript->cc->creditInt; 
                creditDecimal = (double)transcript->cc->creditDecimal;
                credit = creditInt + creditDecimal/10.0;
                switch (transcript->grade[0]) { 
                    case 'A': 
                        if (transcript->grade[1] == '-') 
                            sum += credit * 3.7;                       
                        else 
                            sum += credit * 4.0; 
                        break;
                    case 'B': 
                        if (transcript->grade[1] == '+') 
                            sum += credit * 3.3; 
                        else if (transcript->grade[1] == '/') 
                            sum += credit * 3.0; 
                        else 
                            sum += credit * 2.7; 
                        break;
                    case 'C':
                        if (transcript->grade[1] == '+') 
                            sum += credit * 2.3; 
                        else if (transcript->grade[1] == '/') 
                            sum += credit * 2.0; 
                        else 
                            sum += credit * 1.7; 
                        break;
                    case 'D': 
                        if (transcript->grade[1] == '+') 
                            sum += credit * 1.3; 
                        else if (transcript->grade[1] == '/') 
                            sum += credit * 1.0; 
                        else 
                            sum += credit * 0.7; 
                        break;
                    case 'F': 
                        sum += 0.0; 
                        break;
                }
                creditSum += credit; 
                transcript = transcript->next; 
            }
            gpa = sum / creditSum; 
            return  gpa;
        }

        int findCourse(struct CourseCatalog * cptr, struct LinkedList * transcript, int yr, char sm) { 
            // find if a coruse is already present in the transcript 
            // return 1 if present, otherwise return 0
            while (transcript != NULL) { 
                if (transcript->cc == cptr && transcript->year == yr && transcript->semester == sm)
                    return 1; 
                transcript = transcript->next;
            } 
            return 0; // didn't find the course in the transcript 
        }   

        void courseIdentifier(char buffer[]) { 
            // ask user for course identifier and store it in a buffer 
            printf("Please enter the course identifier (xx.ddd.nnn): ");
            fgets(buffer, 50, stdin);  
        } 

         int display(struct LinkedList * ts) {
            // print all the courses in the transcript, with yyyy.s and Gg. Return the number of courses in the transcript 
            int count = 0; 
            while (ts != NULL) {
                struct CourseCatalog *cptr = ts->cc; 
                printf("%s.%d.%d %d.%d %s %d.%c %s\n", cptr->courseDivision, cptr->courseDepartment, cptr->courseNumber, cptr->creditInt, cptr->creditDecimal, cptr->courseTitle, ts->year, ts->semester, ts->grade); 
                ts = ts->next;
                count++;
            }
            printf("\n"); 
            return count; 
        }

        void removeCourse(int year, char semester, struct LinkedList** transcript, struct CourseCatalog * cc) {
            // Remove the corresponding entry from the transcript list. Print "removed" if the course was removed
            struct LinkedList* p = *transcript;
            struct LinkedList* q = p;

            while (p != NULL && matchCourse(year, semester, p->year, p->semester, cc, p)) {
                q = p;
                p = p->next;
            }
            if (p == NULL) {
                return; 
            }
            if (p == *transcript)
                *transcript = p->next;
            else
                q->next = p->next;
            free(p);
        }
         
        int matchCourse(int givenYear, char givenSem, int presentYear, char presentSem, struct CourseCatalog * cc, struct LinkedList * p) { 
            // find matching course in the same semester year. If matches return 0, otherwise return 1 
            if (givenYear == presentYear && givenSem == presentSem && p->cc == cc) 
                return 0; 
            else
                return 1; 
        } 

        int compareSemester(int givenYear, char givenSem, int presentYear, char presentSem) {  
            // compare semester and year. If the given time is earlier than the present time return 0
            // otherwise return 1
            if (givenYear > presentYear) 
                return 1; 
            else if (givenYear < presentYear) 
                return 0; 
            else { // compare spring or fall in the sams year 
                if (givenSem == 'F' && presentSem == 'S') 
                    return 1; 
                else if (givenSem == 'S' && presentSem == 'F') 
                    return 0; 
                else // same semester year 
                    return 1; // since courses are sorted in the order they're added, 
                              // so if the given course is in the same semester year, then return 1 and advance the pointer
            }
        }

         void addCourse(int year, char semester, char* grade, struct LinkedList** transcript,
                       struct CourseCatalog * cc) {
            // Add the corresponding entry to the transcript list. Print "added" if the course was added,
            //and print "present" if the course was already in the transcript
            struct LinkedList* p = *transcript;
            struct LinkedList* q = p;
            while (p != NULL && compareSemester(year, semester, p->year, p->semester)) {
                q = p;
                p = p->next;
            }
            struct LinkedList* elem = malloc(sizeof(struct LinkedList));
            elem->year = year;
            elem->semester = semester;
            strcpy(elem->grade, grade);
            elem->cc= cc;
                
            if (p == *transcript) {
                *transcript = elem;
                elem->next = p;
            } else {
                elem->next = p;
                q->next = elem;
            }
        }

        int lineNum(FILE * fptr) {
            // return number of lines in the file
            char str[100]; // buffer
            int count = 0;
            while (fgets(str, 100, fptr) != NULL) // chnge it to fgets
                count++;
            return count;
        }

        void loadData(FILE * fptr, struct CourseCatalog * cc, int count) {
            // Create Catalog, load data from file into character array cc
            for (int i = 0; i < count; i++) { // read data from file and store in array
                cc->courseDivision[2] = 0;
                cc->courseTitle[32] = 0; // append NULL character
                fscanf(fptr, "%2s.%d.%d %d.%d ", cc->courseDivision, &cc->courseDepartment, &cc->courseNumber,
                       &cc->creditInt, &cc->creditDecimal);
                fgets(cc->courseTitle, 33, fptr);
                storeInput(cc->courseTitle);
                ++cc; // advance the pointer
            }
        }

        struct CourseCatalog * compareInfo(char* userInput, struct CourseCatalog* cc, int count) {
            // Given a course identifier (xx.ddd.nnn) as input, print the corresponding credit assignmnt and course title from the catalog
            // return the pointer
            char xx[3];
            int cd, cn;
            xx[0] = *userInput;
            userInput++; 
            xx[1] = *userInput;
            userInput++; 
            xx[2] = 0;
            userInput++; // skip .
            char ddd[4];
            for (int i = 0; i < 3; i++) { 
                ddd[i] = *userInput; 
                userInput++;
            }
            ddd[3] = 0;
            cd = atoi(ddd); 
            userInput++; // skip .
            char nnn[4];
            for (int i = 0; i < 3; i++) { 
                nnn[i] = *userInput;
                userInput++; 
            }
            nnn[3] = 0;
            cn = atoi(nnn);
  
            for (int i = 0; i < count; i++) {
                if (strcmp(cc->courseDivision, xx) == 0 && cc->courseDepartment == cd &&
                        cc->courseNumber == cn) // matches
                    return cc;
                ++cc; // advance the pointer
            }
            return NULL;
        }
