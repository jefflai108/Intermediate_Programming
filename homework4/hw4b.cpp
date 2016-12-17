/* Intermediate Programming 
 * hw4b main 
 * Cheng-I Lai 
 * clai24 
 */ 

#include "header_hw4.h"

inline GenerateText::GenerateText() {}
void GenerateText::getInput()
{
    while (cin >> s1) {
        cin >> s2;
        cin >> d;
        myBigram[ {s1, s2}] = d;
    }
    for (MyBigram::iterator it = myBigram.begin(); it != myBigram.end(); it++) {
        string firstWord = it->first.first;
        vector<string> bigramVector;
        for (MyBigram::iterator itr = myBigram.begin(); itr != myBigram.end(); itr++) // create the vector
            if (itr->first.first == firstWord)
                bigramVector.push_back(itr->first.second);
        findBigram[firstWord] = bigramVector;
    }
}
void GenerateText::produce (int choice)
{
    model = "<START>";
    srand(3535);
    for (int i = 0; i < choice; i++) {
        model = "<START>";
        while (model != "<END>") {
            cout << model << " ";
            vector<string> bigramVector;
            vector<int> probability;
            for (FindBigram::iterator it = findBigram.begin(); it != findBigram.end(); it++)
                if (it->first == model)
                    bigramVector = it->second;
            //int size = bigramVector.size();
            for (vector<string>::iterator vit = bigramVector.begin(); vit != bigramVector.end(); vit++) {
                for (MyBigram::iterator mit = myBigram.begin(); mit != myBigram.end(); mit++) {
                    if (mit->first.first == model && mit->first.second == *vit)
                        probability.push_back(mit->second);
                }
            }
            int sum = 0;
            for (vector<int>::iterator vit = probability.begin(); vit != probability.end(); vit++)
                sum += *vit;
            int num = rand() % sum;
            int temp = 0, count = 0;
            for (vector<int>::iterator vit = probability.begin(); vit != probability.end(); vit++) {
                temp += *vit;
                if (num < temp) {
                    model = bigramVector[count];
                    break;
                }
                count++;
            }
        }// end while
        cout << "<END>" << endl;
    } // end for loop i
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        cout << "No argument provided." << endl;
        return 1;
    }
    int choice = atoi(argv[1]);
    GenerateText generateText;
    generateText.getInput();
    generateText.produce(choice);
}
