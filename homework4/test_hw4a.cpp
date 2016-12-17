/* Intermediate Programming 
 * hw4a unit test
 * Cheng-I Lai 
 * clai24 
 */

#include "header_hw4.h" 

inline Bigram::Bigram() {}
void Bigram::readInput()
{
    string s1 = "<START>", s2;
    while (cin >> s2) {
        pair<string, string> p(s1, s2);
        MyBigram::iterator it = myBigram.find(p);
        if (it == myBigram.end())
            myBigram[p] = 1;
        else
            it->second++;
        s1 = s2;
    }
    myBigram[ {s1, "<END>"}] = 1;
}
void Bigram::display()
{
    for (MyBigram::iterator it = myBigram.begin(); it != myBigram.end(); ++it)
        cout << it->first.first << " " << it->first.second << " " << it->second << "\n";
}
void Bigram::reverseDisplay()
{
    for (MyBigram::reverse_iterator itr = myBigram.rbegin(); itr != myBigram.rend(); ++itr)
        cout << itr->first.first << " " << itr->first.second << " " << itr->second << "\n";
}
void Bigram::countDisplay()
{
    typedef multimap<int, pair<string, string> > TempBigram;
    TempBigram tempBigram;
    for (MyBigram::iterator it = myBigram.begin(); it != myBigram.end(); ++it) {
        tempBigram.insert({it->second, it->first}); // user insert instead
    }

    for (TempBigram::iterator rti = tempBigram.begin(); rti != tempBigram.end(); ++rti)
        cout << rti->second.first << " " << rti->second.second << " " << rti->first << "\n";
}

int main() 
{   
    // readInput 
    Bigram myBigram1; 

    // display, reverseDisplay, countDisplay
    Bigram myBigram2;
    pair<string, string> p{"one one", "one two"}; 
    myBigram2[p] = 1; 
    myBigram2[{"two one", "two two"}] = 2; 
    myBigram2[{"three one", "three two"}] = 3;
    myBigram2.display(); 
    myBigram2.reverseDisplay();
    myBigram2.countDisplay();
}


