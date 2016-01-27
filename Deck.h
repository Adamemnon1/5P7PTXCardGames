
//
//  Deck.h
//  Lab2
//
//  Created by Carlie Abraham on 2/28/15.
//  Copyright (c) 2015 Carlie Abraham. All rights reserved.
//

#ifndef __Lab2__Deck__
#define __Lab2__Deck__

#include "Card.h"
#include "Hand.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <iterator>
#include <memory>
using namespace std;

//enums for a game of poker
enum gameOfPoker {
    sizeOfHand5 = 5,
    numberOfHands = 9,
    sizeOfHand7 = 7
};

//forward declaration
class Hand;

//deck error messages
enum deckErrMsg {
    deckSuccess = 0,
    deckEmptyFile = 22,
    deckFileDidNotOpen = 33,
};


//declares a class Deck
//a destructor is not neccesary because we are not dealing with dynamic memory allocation
//or inheretance/polymorphism. We only need a destructor upon termination of code, which is done
//automatically
class Deck{
    //friend methods that allow access to private member variables
    friend ostream & operator<<(ostream & out, const Deck & deck);
    friend Hand & operator<<(Hand & h, Deck & d);
    
private:
    vector<Card> deck;

public:
    Deck();			//Default constructor
    Deck(string fileName); // constructor
    int load(string fileName); //load method
    void shuffle(); //shuffle method
    int size() const; //size of deck method
    void add_card(Card c); //adds a card
};

//ostream operator that prints out the contents of the deck to the output stream
ostream & operator<<(ostream & out, const Deck & deck);

#endif /* defined(__Lab2__Deck__) */

