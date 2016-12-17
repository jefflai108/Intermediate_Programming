/*
 * 600.120 Intermediate Programming 
 * homework 2 
 * Cheng-I Lai 
 * clai24 
*/

#include "dnasearch.h" 

#define MAXSIZE 15000 // maxsize of the input file  

int validText(FILE* fptr, char data[MAXSIZE]) 
{ // store the valid content of the text file into the array data  
  // return 0 if invalid, otherwise return 1  
    int c; 
    int count = 0; // loop over the data array
    int spaceCount = 0; // number of spaces in the text file 
    while ((c = fgetc(fptr)) != EOF) { // get characters from file 
        // check for the validility of the file 
        if (isspace(c)) 
          spaceCount++; 
        else { 
            c = toupper(c); // case insensitive 
            if (c=='A' || c=='C' || c=='T'|| c=='G') { 
                if (count < MAXSIZE) // should be less than 15000
                    data[count] = c;
                count++;
            } else   // characters other than A, C, T, G
                return 0;
        }
    } // end while loop 
    if (count == 0 || count >= MAXSIZE || (spaceCount > ((count+spaceCount)/2)))
        return 0; 
    return 1; 
}

int validPattern(char input[], char data[]) 
{ // check if user input, i.e. pattern,  is valid 
  // return 0 if invalid, otherwise return 1
    int c; 
    int len = strlen(input);
    int len2 = strlen(data); 
    if (len > len2) 
      return 0; 

    for (int i=0; i<len; i++) { // loop over the user input 
        c = toupper(input[i]); 
        if (c!='A' && c!='C' && c!='T' && c!='G') // the array contains characters other than A, C, T, G
            return 0; 
    }
    return 1; 
}

int patternMatch(char pattern[], char text[], char buffer[])
{ // printout the offsets 
  // return 1 if there's a pattern in the text, otherwise return 0
  int lenPattern = strlen(pattern); 
  int lenText = strlen(text); 
  int isMatch = 0; 
  sprintf(buffer, "%s ", pattern); 
  for (int i=0; i<lenPattern; i++) 
    pattern[i] = toupper(pattern[i]); 

  //naive exact matching algorithm 
  for (int i=0; i<=(lenText-lenPattern); i++) { 
    char match = 'T'; 
    for (int j=0; j<lenPattern; j++) { 
      if (pattern[j] != text[i+j]) { 
        match = 'F'; 
      }
    }
    if (match == 'T') {  
      int place = strlen(buffer); 
      sprintf(buffer+ place, "%d ", i);
      isMatch = 1; 
    }
  } // end if
  return isMatch; 
} 


      



  
