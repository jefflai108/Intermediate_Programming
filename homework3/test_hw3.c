/* Intermediate Programming 
 * hw3 unit test 
 * Cheng-I Lai 
 * clai24
 */

#include "hw3_function.h" 
#include <assert.h> 

int main() 
{ /* unit test */
    // test function storeInput 
    char temp[] = "this is a test\n"; 
    storeInput(temp); 
    assert(strlen(temp) == 14); 

    //test function calculateGPA 
    struct LinkedList * ts1 = NULL; 
    assert(calculateGPA(ts1) == 0.00); 
    
    ts1->cc->creditInt = 3; 
    ts1->cc->creditDecimal = 5; 
    strcpy(ts1->grade, "A+");  
    assert(calculateGPA(ts1) == 4.00);

    // test function findCourse 
    struct LinkedList * ts2  = NULL; 
    struct CourseCatalog * cc = {.courseDivision = "EN", .courseDepartment = 600, .courseNumber = 200, .courseCredit = 3, .courseDecimal = 5, .courseTitle = "a class"}; 
    assert(findCourse(cc, ts2) == 0);  

    ts2->cc = cc; 
    assert(fincCourse(cc, ts2_ == 1);

    // test function courseIdentifier 
    char buffer[50]; 
    courseIdentifier(buffer); 

    // test function matchCourse 


    printf("Passed all tests\n"); 
    return 0;
}
