Intermediate Programming 
hw4 README 
Cheng-I Lai 
clai24

part a design: 
Create a class. Make a function that reads input from stdin and stores the content into a map (use while to keep reading input, use two strings to store into a map). Make a function that display the content of the map using the iterator. Another function iterator in reverse with reverse_iterator. To sort by count, loop through the bigram->count map using an iterator, and insert each element into a reverse multimap. 

part b design: 
Create a class. Make a function that stores the input from stdin into a map using while loop. Store the bigrams for each word into a <string, vector<string> > map, by using an iterator iterator through every word in the original map, while storing each word's bigrams into a vecotr. Finally insert the vector into the map. Make another function that do the generating text algorithm for a given number of times. The text generating algorithm first iterate over the second map created in the first function and pull out the corresponding vector. Loop over this vector and store the count by comparing to the first map created in the first function to a vector. To generate a random number, iterate through the vecotr just created and use modular arithmatic. Iterate thorugh the vecot again, whenever the random just created is smaller than the count, output the corresponding position of the map created in the first funciton to stdout. Update the text generated, execute the while loop again until the text generated = "<END>". 
 
problem:
unit test is a problem, a HUGE one. I know the basic concept that i can check my code's correctness by predicting next generated output by reducing the possible combination of bigrams. I know it's doable, but i have too little time.  

