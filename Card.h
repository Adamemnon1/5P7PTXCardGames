//
//  Card.h
//  Lab2
//
//  Created by Carlie Abraham on 2/28/15.
//  Copyright (c) 2015 Carlie Abraham. All rights reserved.
//

#ifndef __Lab2__Card__
#define __Lab2__Card__

#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

//creates enumerations for the suit and value of a card, as well as the error messages and other variables u
enum suit { club, diamond, heart, spade };
enum value { two = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };
enum errorMsg {
    tooFewArguments = 1,
    success = 0,
    onlyShuffleEntered = 2,
    toManyShuffleCodes = 3,
    tooManyArguments = 5,
    unexpectedError = 6,
    notEnoughCards = 7,
    incorrectShuffleCode = 8,
    handsNotCorrectSize = 44,
    noCardsLeft = 455,
    badGameName = 68,
	playerAlreadyPlaying = 69,
	tooFewPlayers=70
};
enum handCodes{
    emptyHand = 0,
    firstHand = 1,
    handSize = 5,
};
enum order{
    first,
    second,
    third,
    fourth,
    fifth,
    sixth,
    seventh,
};
enum pairs{
    noPairs = 0,
    onePair = 1,
    twoPairs = 2
};


//creats a struct for a card
struct Card{
    suit s;
    value v;
    bool operator< (const Card &) const;
    string toString();
    
    
    bool isVisible= false;
};


//declares functions parseCards, printDeck, determineRank and usageMsg

int printDeck(const vector<Card> & deck);
void usageMsg(string programName, string error);
void printMessage(string message);
void printError(string errorMessage);

#endif /* defined(__Lab2__Card__) */
