   /* Homework 0, 600.12
    *
    * (add your vitals here)
    *
    *  */

#include <stdio.h>
#include <string.h>

#define LENGTH 16

   int main(int argc, char* argv[])
   {
      int j=0; 
      char dep[4];
        char course[LENGTH];
          if (argc == 1) {
                 printf("Usage: hw0 XX.###.###Gg#.#\n");
                     return 1;  // exit program
                       }

            strncpy(course, argv[1], LENGTH);  // copy to course string
              course[LENGTH-1] = '\0';   // make sure last character is null
                printf("course string: %s\n", course);  // echo input
   //while (course[j++] != '.') 
     // ;
   j = 3;
   while (course[j] != '.') {
      dep[j-3] = course[j]; 
      j++;
   } 
   dep[3] = 0; 

   printf("%s\n", dep);
        
                  
                     return 0;
                    }
