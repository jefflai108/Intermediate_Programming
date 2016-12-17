/* Intermediate Programming 
 * hw4 header file 
 * Cheng-I Lai 
 * clai24 
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>

using namespace std;

class Bigram {
public:
    inline Bigram();
    void readInput();
    void display();
    void reverseDisplay();
    void countDisplay();
private:
    typedef map<pair<string, string>, int> MyBigram;
    MyBigram myBigram;
};

class GenerateText {
public:
    inline GenerateText();
    void getInput();
    void produce (int choice);

private:
    string model, s1, s2;
    int d;
    typedef map<pair<string, string>, int> MyBigram;
    typedef map<string, vector<string> > FindBigram;
    MyBigram myBigram;
    FindBigram findBigram;
};


