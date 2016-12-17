#include "header.h" 
#include <cassert> 

int main() 
{ 
    Checker c; 
    assert(c.orientation("r", 1) == 1);
    assert(c.orientation("tr", 2) == 1); 
    assert(c.orientation("tr", 1) == 1);
    assert(c.orientation("l", 2) == 4); 
    assert(c.orientation("br", 2) == 3); 
    cout << "Passed Checker::orientation" << endl; 
    
    BoardC b1; 
    Checker c1(1, false, &b1); 
    Checker c2(1, true, &b1); 
    Checker c3(2, false, &b1); 
    Checker c4(2, true, &b1); 
    assert(c1.str() == 'O'); 
    assert(c2.str() == 'K'); 
    assert(c3.str() == 'X'); 
    assert(c4.str() == 'Q'); 
    cout << "Passed Checker::str" << endl;
    
    BoardC b2; 
    int position1 = POSITION(0,6);
    int position2 = POSITION(3,5);
    int position3 = POSITION(4,0);
    assert(b2.at(position1)->ifOpponent(0, 6, "tr", 2) == 0); 
    assert(b2.at(position2)->ifOpponent(3, 5, "tr", 1) == 1);
    assert(b2.at(position3)->ifOpponent(4, 0, "tl", 2) == 1); 
    cout << "Passed Checker::ifOpponent" << endl;

    BoardC b3; 
    b3.moveChecker(POSITION(2,2), POSITION(3,3)); 
    b3.moveChecker(POSITION(1,5), POSITION(7,0));
    b3.moveChecker(POSITION(4,6), POSITION(0,2)); 
    assert(b3.at(POSITION(3,3))->str() == 'O');
    assert(b3.at(POSITION(7,0))->str() == 'X'); 
    assert(b3.at(POSITION(0,2))->str() == 'X');
    cout << "Passed Board::moveChecker" << endl;

    BoardC b4; 
    b4.flip(POSITION(6,0)); 
    b4.flip(POSITION(2,6)); 
    b4.flip(POSITION(7,7)); 
    assert(b4.at(POSITION(6,0))->isKing() == true); 
    assert(b4.at(POSITION(2,6))->isKing() == true); 
    assert(b4.at(POSITION(7,7))->isKing() == true); 
    cout << "Passed Board::flip" << endl;

    BoardC b5; 
    b5.moveChecker(POSITION(5,7), POSITION(1,3)); 
    assert(b5.makeMove(0,2,"r",1,true) == 1);
    b5.moveChecker(POSITION(3,1), POSITION(7,7));
    assert(b5.makeMove(3,5,"l",2,true) == 8); 
    assert(b5.makeMove(6,2,"r",1,false) == 2);  
    cout << "Passed Board::makeMove" << endl;

    BoardC b6; 
    assert(b6.ifJump(1) == false);  
    assert(b6.ifJump(2) == false);  
    b6.moveChecker(POSITION(7,7), POSITION(1,3));  
    assert(b6.ifJump(1) == true);  
    cout << "Passed Board::ifJump" << endl;

    BoardC b7; 
    assert(b7.validity(-1,10,"r",1) == 0); 
    assert(b7.validity(1,0,"r",1) == 0); 
    assert(b7.validity(0,0,"r",2) == 0);
    assert(b7.validity(0,0,"tr",1) == 0); 
    b7.flip(POSITION(0,2)); 
    assert(b7.validity(0,2,"tr",1) == 1); 
    assert(b7.validity(0,2,"tl",1) == 0); 
    b7.moveChecker(POSITION(0,2), POSITION(0,4)); 
    assert(b7.validity(1,5,"l",2) == 0); 
    b7.moveChecker(POSITION(0,4), POSITION(2,4)); 
    assert(b7.validity(1,5,"r",2) == 0);  
    cout << "Paased Board::validity" << endl;

    BoardC b8; 
    assert(b8.legit(POSITION(0,2), TR) == 1); 
    assert(b8.legit(POSITION(3,5), BL) == 1); 
    cout << "Passed Board::legit" << endl;

    BoardC b9; 
    assert(b9.crownded(2,2,"r",1) == 0);
    b9.moveChecker(POSITION(0,2), POSITION(1,6)); 
    assert(b9.crownded(1,6,"r",1) == 1); 
    cout << "Passed Board::crownded" << endl; 

    BoardC b10; 
    assert(b10.ifLeft(1) == 1); 
    assert(b10.ifLeft(2) == 1); 
    cout << "Passed Board::ifLeft" << endl;
    
    assert(b10.availability(POSITION(0,0), 1) == 0);
    assert(b10.availability(POSITION(4,2), 1) == 1);
    b10.moveChecker(POSITION(7,7), POSITION(5,3));
    assert(b10.availability(POSITION(6,2), 1) == 2); 
    cout << "Passed Board::availability" << endl;
   
    BoardC b11; 
    assert(b11.strAt(POSITION(0,0)) == 'O'); 
    assert(b11.strAt(POSITION(7,7)) == 'X'); 
    cout << "Passed Board::strAt" << endl; 
}

