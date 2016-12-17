#include <cstdio> 
#include <iostream> 
#include <map> 
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std; 

#define POSITION(x,y) (7-y)*8+x
#define TR -7
#define TL -9
#define BR 9
#define BL 7

class BoardC;

class Checker { 
private: 
    int mPlayer;
    bool mKing; 
    BoardC* mBoard; 

public:
    Checker() {}; 
    Checker (int player, bool king, BoardC *b) : mPlayer(player), mKing(king), mBoard(b) {}
    void crown() { mKing = true; } 
    bool isKing() { return mKing; }
    int getPlayer() { return mPlayer; }
    char str();
    int orientation(string move, int player);
    int ifOpponent(int x, int y, string move, int player);
}; 

class BoardC { 
private: 
    typedef map<int, Checker> TheBoard; 
    TheBoard mBoard; 

public:    
    BoardC();
    void change(int position, int player, bool king);   
    int ifLeft(int player);
    Checker* at(int position);
    char strAt(int position);
    void displayBoard();
    int availability(int position, int player);
    bool ifJump(int player); 
    int crownded(int x, int y, string move, int player);
    int validity(int x, int y, string move, int player); 
    int makeMove (int x, int y, string move, int player, bool deter);
    void flip(int position);
    void moveChecker(int position1, int position2);
    int legit(int position, int direction);
    void save(string filename, int count1, int count2); 
    void load(string filename, int &playerTurn, int &count1, int &count2);
};

