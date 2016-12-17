#include "header.h" 

void BoardState(BoardC board, int &boardState);  
void Surrender(int playerTurn, int count1, int count2, int tempCount);
int askQ(int &playerTurn, int &tempCount, string &s, int &count1, int &count2, BoardC &board, int &boardState); 

int main() 
{ 
    BoardC board;// declare Board class
    int count1 = 1, count2 = 1, playerTurn = 1, tempCount = count1, x, y, boardState = 0; 
    string s, move;

    do { // switch player 
       int tempX = -1, tempY = -1;
       bool deter = board.ifJump(playerTurn); 
       if (deter == 1) 
          cout << "Reminder: " << "Player " <<  playerTurn << " you have to jump!" << endl; 
       do { // same player same turn
            int L = board.ifLeft(playerTurn); 
            if (L == 0) { 
               Surrender(playerTurn, count1, count2, tempCount); 
               return 1; // return to menu choice 
            } 
            int c = askQ(playerTurn, tempCount, s, count1, count2, board, boardState); 
            if (c == 0) return 0; // quit the program  
            else if (c == 1) return 1; // return to menu choice
            else if (c == 2) continue;   
            else if (c == 3) break;   
            x = s.at(0) - '0', y = s.at(1) - '0', move = s.substr(2,2);
            int p = board.validity(x, y, move, playerTurn);
            if (!p || (tempX != -1 && x != tempX) || (tempY != -1 && y != tempY)) { 
               cout << "Invalid move" << endl; // invalid move message 
               continue; 
            }  
            int choice = board.makeMove(x, y, move, playerTurn, deter);
            if (choice == 0) {
               cout << "Invalid move" << endl; // prioritize move over jump 
               continue; 
            } 
            if (choice == 5) { 
               cout << "Jumped!" << endl;
               tempX=x+2, tempY=y+2; 
            } else if (choice == 6) {
               cout << "Jumped!" << endl;
               tempX=x-2, tempY=y+2;
            } else if (choice == 7) {
               cout << "Jumped!" << endl;
               tempX=x+2, tempY=y-2;
            } else if (choice == 8) {
               cout << "Jumped!" << endl;
               tempX=x-2, tempY=y-2;
            } else if (choice == 2) {  
                break; 
            } else if (choice == 3 || choice == 4) {  
                cout << "Crownded a king!" << endl;
                break;
            } else if (choice == 1) { 
                cout << "Jumped!" << endl; 
                break;
            }

            if (board.availability(POSITION(tempX, tempY), playerTurn) == 2) {  
               deter = true; 
            }
            else break; // can't jump afterward
       } while (1);
 
    if (playerTurn == 1) { 
        playerTurn = 2;
        count1++; 
        tempCount = count2; 
    } else {
        playerTurn = 1;
        count2++; 
        tempCount = count1; 
     }        
   } while (1);
}     

void BoardState(BoardC board, int &boardState) 
{ // toggle the board on or off. 
   if (boardState == 0) { 
      boardState = 1; 
      board.displayBoard();
      cout << endl;
      cout << endl;
   } else boardState = 0;  
} 

void Surrender(int playerTurn, int count1, int count2, int tempCount) 
{ 
        if (playerTurn == 1) playerTurn = 2; 
        else playerTurn = 1; 
        if (tempCount == count1) tempCount = count2; 
        else tempCount = count1;                 
        cout << "Player " << playerTurn << " wins on turn " << tempCount  << endl; // Victory message 
}    

int askQ(int &playerTurn, int &tempCount, string &s, int &count1, int &count2, BoardC &board, int &boardState)   
{ // return 0 if quit the program; return 1 if surrender and return to menu choice; return 2 if toggle board 
    if (boardState == 1) {  
        board.displayBoard();
        cout << endl; 
    } 
    cout << "Player " << playerTurn << " Turn " << tempCount  << endl; 
    cin >> s;     
    if (s == "b" || s == "B") { 
        BoardState(board, boardState); 
        return 2;
    }
    if (s == "q" || s == "Q") 
        return 0;
    if (s == "surrender") { 
        Surrender(playerTurn, count1, count2, tempCount); 
        return 1; 
    }
    if (s.at(0) == 'S') { // save to file
       cin >> s;
       board.save(s, count1, count2);
       return 1; 
    } 
    if (s.at(0) == 'L') { // load the file 
      cin >> s;
      board.load(s, playerTurn, count1, count2);
      return 3; 
    } 
    return 4; 
}

