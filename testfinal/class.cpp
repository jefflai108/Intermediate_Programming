#include "header.h" 

    void BoardC::load(string filename, int &playerTurn, int &count1, int &count2) 
    {   
        string s, dummy;  
        int player, x, y; 
        char c; 
        bool d;
        ifstream myfile (filename);
        if (!myfile.is_open()) return;   
        getline(myfile, s);  
        //getline(myfile, s);
        getline(myfile, s, ' ');
        getline(myfile, s, ' '); 
        getline(myfile, s, ' '); 
        getline(myfile, s, ' ');
        count1 = stoi(s); 
        getline(myfile, s, ' '); 
        getline(myfile, s, ' '); 
        getline(myfile, s, ' '); 
        getline(myfile, s, ' ');
        count2 = stoi(s);
        if (count1 > count2) playerTurn = 1; 
        else playerTurn = 2;
        for (TheBoard::iterator it = mBoard.begin(); it != mBoard.end(); it++) 
            mBoard.erase(it);
        while (getline(myfile, s)) {  
            player = s[0] - '0';
            x = s[2] - '0';
            y = s[4] - '0'; 
            c = s[6]; 
            if (c == 'k') d = true; 
            else d = false; 
            mBoard[POSITION(x,y)] = Checker(player, d, this);
        } 
        myfile.close(); 
    } 

    void BoardC::save(string filename, int count1, int count2) 
    {   
    int x, y; 
    ofstream myfile; 
    myfile.open(filename);
    myfile << "checkers" << endl;
    myfile << "player 1 turn " << count1 << " player 2 turn " << count2 << endl; 
    for (TheBoard::iterator it = mBoard.begin(); it != mBoard.end(); it++) { 
        y = 7-(it->first/8), x = it->first%8; 
        myfile << it->second.getPlayer() << " ";  
        myfile << x << " " << y << " "; 
        if (it->second.isKing()) myfile << "k" << endl; 
        else myfile << "p" << endl; 
    } 
    myfile.close(); 
    } 

    char Checker::str() 
    { //return symbol on the board 
        if (isKing()) {
            if (mPlayer == 1) return 'K'; 
            else return 'Q';
        } else {
            if (mPlayer == 1) return 'O';
            else return 'X';
        }
    }

    int Checker::orientation(string move, int player) { 
    // determine the desired moving direction of the checker  
    // player 1 "r" return 1; player 1 "l" return 2
    // player 2 "r" return 3; player 2 "l" return 4 
    // "tr" return 1; "tl" return 2
    // "br" return 3; "bl" return 4
        if ((move == "r" && player == 1) || (move == "tr")) 
            return 1; 
        else if ((move == "l" && player == 1) || (move == "tl")) 
            return 2; 
        else if ((move == "r" && player == 2) || (move == "br"))
            return 3; 
        else    
            return 4;
    }

    int Checker::ifOpponent(int x, int y, string move, int player) {
    // check if there exists an oppnent in the desired direction 
    // return 1 if there is, else return 0 
        int position = POSITION(x,y);
        
        if (player == 1) { 
            if (orientation(move, player) == 1) {  
               if (mBoard->strAt(position+TR) == 'X' || mBoard->strAt(position+TR) == 'Q') 
                    return 1; 
            } else if (orientation(move, player) == 2) {   
                if (mBoard->strAt(position+TL) == 'X' || mBoard->strAt(position+TL) == 'Q')
                    return 1; 
            } else if (orientation(move, player) == 3) { 
                if (mBoard->strAt(position+BR) == 'X' || mBoard->strAt(position+TR) == 'Q') 
                    return 1; 
            } else { 
                if (mBoard->strAt(position+BL) == 'X' || mBoard->strAt(position+TR) == 'Q') 
                    return 1; 
            }
        } else if (player == 2) { 
            if (orientation(move, player) == 1) {  
                if (mBoard->strAt(position+TR) == 'O' || mBoard->strAt(position+TR) == 'K')
                    return 1; 
            } else if (orientation(move, player) == 2) {   
                if (mBoard->strAt(position+TL) == 'O' || mBoard->strAt(position+TR) == 'K')
                    return 1; 
            } else if (orientation(move, player) == 3) { 
                if (mBoard->strAt(position+BR) == 'O' || mBoard->strAt(position+TR) == 'K') 
                    return 1; 
            } else { 
                if (mBoard->strAt(position+BL) == 'O' || mBoard->strAt(position+TR) == 'K') 
                    return 1; 
            }
        }
        return 0; 
    }

    void BoardC::moveChecker(int position1, int position2) 
    {        
        TheBoard::iterator it = mBoard.find(position1); 
        if (it == mBoard.end()) cout << position1 << "Invalid Move" << endl; 
        else {
            mBoard[position2] = it->second;
            mBoard.erase(it); 
        }
    }

    void BoardC::flip(int position)   
    {
        TheBoard::iterator it = mBoard.find(position); 
        it->second.crown(); 
    }

     int BoardC::makeMove (int x, int y, string move, int player, bool deter) { 
    // perform moves and update to the board accordingly and crown a man to king if necessary 
    // if jump over opponent and available for next move/jump: 5 if TR, 6 if TL, 7 if BR, 8 if BL 
    // 2 if move 
    // return 3 if kill an opponent then crownded, 4 if move and then crownded
    // return 1 if jump over opponent and not available for next move/jump 
        int position = POSITION(x,y); 
        // jump over and kill the opponent 
        if (at(position)->ifOpponent(x, y, move, player) && deter == true) {
            if (at(position)->orientation(move, player) == 1) {  
                if (crownded(x, y, move, player)) {    
                    moveChecker(position, position+TR+TR); 
                    mBoard.erase(position+TR); 
                    flip(position+TR+TR);     
                    return 3; 
                } else { 
                    moveChecker(position, position+TR+TR); 
                    mBoard.erase(position+TR);
                    if (availability(position+TR+TR, player)) return 5; 
                    else return 1; 
                } 
            } else if (at(position)->orientation(move, player) == 2) {  
                if (crownded(x, y, move, player)) {    
                    moveChecker(position, position+TL+TL); 
                    mBoard.erase(position+TL); 
                    flip(position+TL+TL);     
                    return 3; 
                } else { 
                    moveChecker(position, position+TL+TL); 
                    mBoard.erase(position+TL); 
                    if (availability(position+TL+TL, player)) return 6; 
                    else return 1; 
                } 
            } else if (at(position)->orientation(move, player) == 3) {  
                if (crownded(x, y, move, player)) {    
                    moveChecker(position, position+BR+BR); 
                    mBoard.erase(position+BR); 
                    flip(position+BR+BR);     
                    return 3; 
                } else { 
                    moveChecker(position, position+BR+BR); 
                    mBoard.erase(position+BR);
                    if (availability(position+BR+BR, player)) return 7; 
                    else return 1; 
                } 
            } else {  
                if (crownded(x, y, move, player)) {    
                    moveChecker(position, position+BL+BL); 
                    mBoard.erase(position+BL); 
                    flip(position+BL+BL);     
                    return 3; 
                } else { 
                    moveChecker(position, position+BL+BL); 
                    mBoard.erase(position+BL);
                    if (availability(position+BL+BL, player)) return 8; 
                    else return 1; 
                }
            }  
        } else if ((!at(position)->ifOpponent(x, y, move, player)) && deter == false) { // move the checker
            if (at(position)->orientation(move, player) == 1) {  
                if (crownded(x, y, move, player)) {    
                    moveChecker(position, position+TR); 
                    flip(position+TR);     
                    return 4; 
                } else { moveChecker(position, position+TR);}  
            } else if (at(position)->orientation(move, player) == 2) {  
                if (crownded(x, y, move, player)) {    
                    moveChecker(position, position+TL); 
                    flip(position+TL);     
                    return 4; 
                } else moveChecker(position, position+TL);   
            } else if (at(position)->orientation(move, player) == 3) {  
                if (crownded(x, y, move, player)) {    
                    moveChecker(position, position+BR); 
                    flip(position+BR);     
                    return 4; 
                } else moveChecker(position, position+BR); 
            } else {  
                 if (crownded(x, y, move, player)) {    
                    moveChecker(position, position+BL); 
                    flip(position+BL);     
                    return 4; 
                } else moveChecker(position, position+BL); 
            } return 2; 
        } else return 0; 
    }

    bool BoardC::ifJump(int player)
    { // check if there's jump possible. return true if yes, else return false    
        for(TheBoard::iterator it = mBoard.begin(); it != mBoard.end(); it++) { 
            if (player == 1 && (it->second.str() == 'O' || it->second.str() == 'K')) { 
                if (availability(it->first, player) == 2) return true; 
            } else if (player == 2 && (it->second.str() == 'X' || it->second.str() == 'Q')) { 
                if (availability(it->first, player) == 2) return true; 
            }    
        }
        return false; 
    } 

    int BoardC::validity(int x, int y, string move, int player) { 
    // check for validity of the move, return 1 if valid else return 0
        // ground check 
        int position = POSITION(x,y), tempPosi;
        if (x>7 || x<0 || y>7 || y<0) 
            return 0; 
        if (at(position) == NULL) 
            return 0; 
        if (at(position)->getPlayer() != player) 
            return 0;  
        if (at(position)->isKing() == 0) { 
            if (move != "r" && move != "l") return 0;
        } else {   
            if (move != "tr" && move != "tl" && move != "br" && move != "bl") return 0;
        }
        // check out-of-bound condition and if the desired destination is empty 
        // and if a man is killing an opponent king and if a man is killing his teammates  
        if (at(position)->orientation(move, player) == 2) { 
            if (strAt(position) == strAt(position+TL)) return 0; // teammate is on your way!
            if (at(position)->ifOpponent(x, y, move, player)) {
                tempPosi = position + TL; 
                if (!(at(position)->isKing())) { 
                    if (at(tempPosi)->isKing()) return 0; // a man is trying to kill a king  
                }
            } else tempPosi = position; 
            if (tempPosi%8 == 0 || tempPosi < 8 || strAt(tempPosi+TL) != ' ') 
                return 0; // either out-of-bound or desired destination isn't empty 
        } else if (at(position)->orientation(move, player) == 1) { 
            if (strAt(position) == strAt(position+TR)) return 0; 
            if (at(position)->ifOpponent(x, y, move, player)) {  
                tempPosi = position + TR; 
                if (!(at(position)->isKing())) { 
                    if (at(tempPosi)->isKing()) return 0; 
                }
            } else tempPosi = position; 
            if ((tempPosi+1)%8 == 0 || tempPosi < 8 || strAt(tempPosi+TR) != ' ') 
                return 0; 
        } else if (at(position)->orientation(move, player) == 4) { 
            if (strAt(position) == strAt(position+BL)) return 0; 
            if (at(position)->ifOpponent(x, y, move, player)) {  
                tempPosi = position + BL; 
                if (!(at(position)->isKing())) { 
                    if (at(tempPosi)->isKing()) return 0;  
                }
            } else tempPosi = position; 
            if (tempPosi%8 == 0 || tempPosi > 55 || strAt(tempPosi+BL) != ' ')
                return 0;
        } else if (at(position)->orientation(move, player) == 3) { 
            if (strAt(position) == strAt(position+BR)) {return 0;} 
            if (at(position)->ifOpponent(x, y, move, player)) { 
               tempPosi = position + BR;
               if (!(at(position)->isKing())) { 
                    if (at(tempPosi)->isKing()) { return 0; }
                }
            } else tempPosi = position; 
            if ((tempPosi+1)%8 == 0 || tempPosi > 55 || strAt(tempPosi+BR) != ' ') 
            { return 0; } 
        }           
        return 1; 
    }
     
    int BoardC::legit(int position, int direction) 
    { // For availability and crownded, check if next move from the position is valid. return 1 if yes, else return 0 
        int compo = position + direction;
        if (compo > 63 || compo < 0) return 0; 
        if (direction == TR) { 
            if ((position+1)%8 == 0 || (position<8)) return 0;  
        } else if (direction == TL) { 
            if (position%8 == 0 || (position<8)) return 0;  
        } else if (direction == BR) { 
            if ((position+1)%8 == 0 || (position>55)) return 0;  
        } else  {
            if (position%8 == 0 || (position>55)) return 0;  
        } return 1; 
    } 
   
    int BoardC::crownded(int x, int y, string move, int player) { 
    // crown a man to king return 1 if a man is ready to be crownded else return 0 
        int position = POSITION(x,y);
        if (at(position)->isKing())
            return 0; // already a king 
        // reach the opposite side of the board 
        if (at(position)->orientation(move, player) == 1) {  
            if (availability(position, player) == 1 && (position+TR)<8) return 1; 
            if (availability(position, player) == 2 && (position+TR+TR)<8) return 1; 
        } else if (at(position)->orientation(move, player) == 2) { 
            if (availability(position, player) == 1 && (position+TL)<8) return 1; 
            if (availability(position, player) == 2 && (position+TL+TL)<8) return 1; 
        } else if (at(position)->orientation(move, player) == 4) { 
            if (availability(position, player) == 1 && (position+BL)<8) return 1; 
            if (availability(position, player) == 2 && (position+BL+BL)<8) return 1; 
        } else if (at(position)->orientation(move, player) == 3) { 
            if (availability(position, player) == 1 && (position+BR)<8) return 1; 
            if (availability(position, player) == 2 && (position+BR+BR)<8) return 1; 
        }
        return 0; 
    }
    
    int BoardC::ifLeft(int player) { 
    // check if there's any checker left. return 1 if yes, 0 if not 
        for(TheBoard::iterator it = mBoard.begin(); it != mBoard.end(); it++) {  
            if (player == 1 && (it->second.str() == 'O' || it->second.str() == 'K')) return 1; 
            else if (player == 2 && (it->second.str() == 'X' || it->second.str() == 'Q')) return 1;  
        } 
        return 0; 
    } 

    int BoardC::availability(int position, int player) { 
    // check availability for jumping or moving i.e. possibility of making a move 
    // return 1 if next move is available/possible, 2 if next jump is possible  
    // else return 0 
        if (at(position)->isKing()) { 
            // first check if possible to jump 
            if (player == 1) { 
                if (legit(position, TR) && (strAt(position+TR) == 'Q' || strAt(position+TR) == 'X')) { 
                    if (legit(position+TR, TR)) { 
                        if (strAt(position+TR+TR) == ' ') return 2;
                    } 
                } 
                if (legit(position, TL) && (strAt(position+TL) == 'Q' || strAt(position+TL) == 'X')) {  
                    if (legit(position+TL, TL)) { 
                        if (strAt(position+TL+TL) == ' ') return 2;
                    } 
                } 
                if (legit(position, BR) && (strAt(position+BR) == 'Q' || strAt(position+BR) == 'X')) { 
                    if (legit(position+BR, BR)) { 
                        if (strAt(position+BR+BR) == ' ') return 2;
                    } 
                } 
                if (legit(position, BL) && (strAt(position+BL) == 'Q' || strAt(position+BL) == 'X')) { 
                    if (legit(position+BL, BL)) { 
                        if (strAt(position+BL+BL) == ' ') return 2;
                    } 
                } 
            } else if (player == 2) { 
                if (legit(position, TR) && (strAt(position+TR) == 'K' || strAt(position+TR) == 'O')) { 
                    if (legit(position+TR, TR)) { 
                        if (strAt(position+TR+TR) == ' ') return 2;
                    } 
                } 
                if (legit(position, TL) && (strAt(position+TL) == 'K' || strAt(position+TL) == 'O')) { 
                    if (legit(position+TL,TL)) { 
                        if (strAt(position+TL+TL) == ' ') return 2;
                    }
                } 
                if (legit(position, BR) && (strAt(position+BR) == 'K' || strAt(position+BR) == 'O')) { 
                    if (legit(position+BR, BR)) { 
                        if (strAt(position+BR+BR) == ' ') return 2;
                    } 
                } 
                if (legit(position, BL) && (strAt(position+BL) == 'K' || strAt(position+BL) == 'O')) {
                    if (legit(position+BL, BL)) { 
                        if (strAt(position+BL+BL) == ' ') return 2;
                    } 
                } 
            }   
            // can't jump, check if possible to move 
            if (legit(position, TR)) { 
                if (strAt(position+TR) == ' ') return 1;
            } 
            if (legit(position, TL)) { 
                if (strAt(position+TL) == ' ') return 1;
            } 
            if (legit(position, BR)) { 
                if (strAt(position+BR) == ' ') return 1;
            } 
            if (legit(position, BL)) { 
                if (strAt(position+BL) == ' ') return 1;
            }  
        } else { // not a king 
            if (player == 1) {
            // first check if possible to jump 
                if (legit(position, TR) && strAt(position+TR) == 'X') {  
                    if (legit(position+TR, TR)) { 
                        if (strAt(position+TR+TR) == ' ') return 2;
                    }
                } 
                if (legit(position, TL) && strAt(position+TL) == 'X') {  
                   if (legit(position+TL, TL)) {  
                        if (strAt(position+TL+TL) == ' ') return 2;
                    }
                }
            // then check if possible to move 
                if (legit(position, TR)) { 
                    if (strAt(position+TR) == ' ') return 1;
                } 
                if (legit(position, TL)) { 
                    if (strAt(position+TL) == ' ') return 1; 
                }
            } else if (player == 2) { 
                if (legit(position, BR) && strAt(position+BR) == 'O') {  
                    if (legit(position+BR, BR)) { 
                        if (strAt(position+BR+BR) == ' ') return 2;  
                    } 
                } 
                if (legit(position, BL) && strAt(position+BL) == 'O') {  
                    if (legit(position+BL, BL)) {  
                        if (strAt(position+BL+BL) == ' ') return 2;
                    }
                } 
                if (legit(position, BR)) { 
                    if (strAt(position+BR) == ' ') return 1; 
                } 
                if (legit(position, BL)) { 
                    if (strAt(position+BL) == ' ') return 1; 
                }
            }   
       } return 0; 
    }

    BoardC::BoardC() 
    { 
        for (int i=1; i<8; i+=2)  
            mBoard[i] = Checker(2, false, this);
        for (int i=8; i<16; i+=2) 
             mBoard[i] = Checker(2, false, this);
        for (int i=17; i<24; i+=2) 
             mBoard[i] = Checker(2, false, this);
        for (int i=46; i>38; i-=2) 
            mBoard[i] = Checker(1, false, this); 
        for (int i=55; i>47; i-=2) 
            mBoard[i] = Checker(1, false, this); 
        for (int i=62; i>55; i-=2) 
            mBoard[i] = Checker(1, false, this); 
 }
    
    Checker* BoardC::at(int position)
    {
        TheBoard::iterator it = mBoard.find(position);
        if (it == mBoard.end()) return NULL;
        else return &(it->second);
    }
    
    char BoardC::strAt(int position)
    {
        Checker* c = at(position); 
        if (c == NULL && (position > -1) && (position < 64)) {return ' ';} 
        else return c->str();
    }

    void BoardC::displayBoard() 
    {
        int count = 0, number = 7; 
        for(int i=0; i<64; i++) {
            if (count%8 == 0) { 
                cout << to_string(number) << " "; 
                number--; 
            } 
            TheBoard::iterator it = mBoard.find(i);
            if (it != mBoard.end())
                cout << it->second.str();
            else cout << ' ';
            count++;
            if (count%8 == 0) 
                cout << '\n'; 
        }
        cout << "  "; 
        for(int i=0; i<8; i++) 
            cout << to_string(i); 
    }

 

