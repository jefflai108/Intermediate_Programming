/*
 * 600.120 Intermediate Programming 
 * homework 2 
 * Cheng-I Lai 
 * clai24 
*/

#include "dnasearch.h" 

#define MAXDATA 15000 

int main(int argc, char** argv) 
{ 
    char buffer[100000]; 
    char data[MAXDATA+1]; 
    char pattern[MAXDATA+1]; 
    //int patternNum; // number of different pattern from user input 

    if (argc == 1) { 
        puts("No argument provided"); 
        exit(1); 
    } 
    FILE* fptr = fopen(argv[1], "r"); 
    if (fptr == NULL) { 
        puts("Failed to open file"); 
        return 1; 
    }

    // function to store input file in array data and check if its valid 
    if (validText(fptr, data)) 
        ; 
    else { 
        puts("The text file is invalid."); 
        return 1; 
    }
    
    // store user input in an array and return number of different patterns 
    char y;
    while (scanf("%c", &y) != EOF) { 
      if(isspace(y)) 
        continue; 
      pattern[MAXDATA] = '\0'; 
      int index = 0; 
      while (!isspace(y)) { 
        if (index >= MAXDATA) { 
          puts("The pattern you input is invalid."); 
          return 1; 
        }
        pattern[index] = y; 
        index++; 
        scanf("%c", &y); 
      }
      // skip the white spaces 
      //while (isspace(y)) 
        //scanf("%c", &y); 
      if (validPattern(pattern, data)) 
            ; 
      else { 
          puts("The pattern you input is invalid."); 
          return 1; 
      }

      if (patternMatch(pattern, data, buffer)) { 
          puts(buffer);  
      } else { 
          printf("%s Not found", pattern); 
      }
      printf("\n");
      memset(pattern, 0, sizeof(pattern)); 
    }
    
    fclose(fptr); 
    return 0;
} 


