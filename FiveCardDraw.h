/*
Authors: Carlie Abraham, Brian Lam, Adam Sandor
Date: 4/5/15
Lab: Lab 3.

*/

#pragma once
#include "Hand.h"
#include "Game.h"
#include "Player.h"
#include <memory>
#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
//#include "PokerGame.h"


using namespace std;

class FiveCardDraw : public Game {

public:
	FiveCardDraw();
	virtual int before_turn(Player & pl); //=0 to make the method pure virtual
	virtual int turn(Player & pl);
	virtual int after_turn(Player & pl);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
	

	//int pot;//ADAM
	//vector<int> amountBetPerPlayer;




protected:
	Deck discardDeck;

};
