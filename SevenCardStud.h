#pragma once

#include "Game.h"
#include "Hand.h"

class SevenCardStud : public Game {
    
public:
    SevenCardStud();
    
    
    
    virtual int before_turn(Player & pl); //=0 to make the method pure virtual
    virtual int turn(Player & pl);
    virtual int after_turn(Player & pl);
    virtual int before_round();
    virtual int round();
    virtual int after_round();


	int SevenCardStud::before_turn1();
	int SevenCardStud::before_turn234();
	int SevenCardStud::before_turn5();

	int numCardsDealtPerPerson = 3;
    
    void printHands(Player & pl);
	int compareHands( Hand h1,  Hand h2);//ADAm
	bool diffCardHere(Hand h1, Hand h2);
    
    
protected:
    size_t dealerPos;
    Deck discardDeck;
};
