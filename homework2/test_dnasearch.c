/*
 * 600.120 Intermediate Programming 
 * homework 2 
 * Cheng-I Lai 
 * clai24 
*/

#include "dnasearch.h" 
#include <assert.h> 

int main() 
{ 
  char data1[] = "ATCG"; 
  char input1[] = "ATCGATCG"; 
  char input2[] = "AgCYu"; 
  char input3[] = "acg";
  char data2[] = "ATCGTACGTA"; 
  char input4[] = "CAGACT"; 
  char input5[] = "CAT AGTCATCGATCGATG";

  assert(validPattern(input1, data1) == 0); 
  assert(validPattern(input2, data1) == 0); 
  assert(validPattern(input3, data1) == 1); 
  assert(validPattern(input4, data2) == 1);
  assert(validPattern(input5, data2) == 0); 

  char text1[] = "ATCGATCGATCG";
  char pattern1[] = "ATCG"; 
  char buffer1[100000]; 
  char text2[] = "ACTGATA"; 
  char pattern2[] = "AGCT"; 
  char buffer2[100000]; 
  char text3[] = "CGATCGTACGTA"; 
  char pattern3[] = "TC"; 
  char buffer3[100000]; 
  char text4[] = "GCATGACATGGTACACTGACGTAC"; 
  char pattern4[] = "GTAC"; 
  char buffer4[100000]; 

  assert(patternMatch(pattern1, text1, buffer1) == 1); 
  assert(strcmp("ATCG 0 4 8 ", buffer1) == 0);
  assert(patternMatch(pattern2, text2, buffer2) == 0);
  assert(patternMatch(pattern3, text3, buffer3) == 1); 
  assert(strcmp("TC 3 ", buffer3) == 0); 
  assert(patternMatch(pattern4, text4, buffer4) == 1); 
  assert(strcmp("GTAC 10 20 ", buffer4) == 0); 

  return 0; 
}
 
