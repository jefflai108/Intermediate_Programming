Intermediate Programming 
Final Project Checker 
Cheng-I Lai 
clai24

CHECKER DESIGN: 
Two classes: BoardC class and Checker class. BoardC class process most of the information and functionality, where Checker class contians the characteristic of the checker object. The two class forms a has-a relationship. Checker objects are store in a map data structure in the board class. The reason to choose map as the data structure is that it's easier to access value (position and the corresponding Checker object), and memory allocation is already taken care of.

Checker class has two variables to specify which player it belongs to and whether it's a king or not. Checker class also encompass relevant funciton associated with checker object. Function ifOpponent takes user input and determines if there is an opponent around the checker. Function str returns the symbol that represents the checker object on the display. Function orientation takes user input and determiens which direction the checker is heading to (top right, top left, bottom right, bottom left). Function crown flips the regular piece of checker to king. 

BoardC class has a map data structure that stores the checker objects. Some major functions: validity, availability, moveChecker, crowned, save/load. Validity checks whether a move is valid or not. Availability checks whether there's a possible move/jump. Crowned checks if a checker will be crowned. 

Drive class is consist of two do-while loop. The outer do while loop deals with switching player and turn. The inner do-while loop deals with same player same turn, with validity funciton at the bgeinning and availability function at the end. There are also helper function to deal with board toggling and user input. 

CHECKER LANGUAGE FEATURES: 
BoadC class contains Checker class, storing the checker object in a map. The key is the position (0 to 63), which can be calculated from x, y coordinate user input.

CHECKER COMPLETENESS: 


