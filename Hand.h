//
//  Hand.h
//  Lab2
//
//  Created by Carlie Abraham on 2/28/15.
//  Copyright (c) 2015 Carlie Abraham. All rights reserved.
//

#ifndef __Lab2__Hand__
#define __Lab2__Hand__

#include "Card.h"
#include "Deck.h"
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

//enums that define  the poker hand ranking
enum pokerRank { noRankHand, onePairHand, twoPairHand, threeKindHand, straightHand, flushHand, fullHouseHand, fourKindHand, straightFlushHand };
//indexing enums
enum index{
    negativeOne = -1,
    zero = 0,
    one = 1,
    twoo=2,
    threee =3,
    fourr=4,
    fivee=5,
    sixx=6
};
//forward declaration of deck
class Deck;

//defining class hand
//no destructor is neccesary to define because we are not dealing with dynamic memory allocaiton, nor are we
//dealing with inheretance/polymorphism, we only need to destruct the object upon code termination, which is
//taken care of automatically
class Hand{
    //friend declarations so that Hand's private variables can be used
    friend ostream & operator<<(ostream & out, const Hand & h);
    friend Hand & operator<<(Hand & h, Deck & d);
    friend bool poker_rank(const Hand & h1, const Hand & h2);
    friend pokerRank determineRank(const Hand & pHand); //helper funciton for my own purposes
    
private:
    vector<Card> hand;
    
public:
    //method declarations
    Hand(); // default constructor
    Hand(const Hand & other); // copy constructor
    Hand & operator= (const Hand &other);
    int size() const;
    bool operator==(const Hand &other) const;
    bool operator< (const Hand & other) const;
    string toString() const;
    
    Card operator[](size_t loc);
    void remove_card(size_t loc);
    vector<Card> & getHandVect();
	void addCard(Card & card);
	void sortHand();
    
    
    friend vector<Card> best5Cards(const Hand & h);//ADAM
};
//insertion operators
ostream & operator<<(ostream & out, const Hand & h);
Hand & operator<<(Hand & h, Deck & d);

//poker_rank comparison funcitons and helper methods
bool poker_rank(const Hand & h1, const Hand & h2);
bool compareStraightFlush(vector<Card> h1, vector<Card> h2);
bool compareStraight(vector<Card> h1, vector<Card> h2);
bool compareFlush(vector<Card> h1, vector<Card> h2);
bool compareFourKind(vector<Card> h1, vector<Card> h2);
bool compareFullHouse(vector<Card> h1, vector<Card> h2);
bool compareThreeKind(vector<Card> h1, vector<Card> h2);
bool compareTwoPair(vector<Card> h1, vector<Card> h2);
bool compareOnePair(vector<Card> h1, vector<Card> h2);
bool compareNoRank(vector<Card> h1, vector<Card> h2);
pokerRank determineRank(const Hand & pHand); // added this
pokerRank determineRank(const vector<Card> & pokerHand);
void isFlushOrStraight(vector<Card> hand, bool &, bool &);
void isFourKind(vector<Card> hand, bool & fourKind);
void isFullHouse(vector<Card> hand, bool & fullHouse);
void isThreeKind(vector<Card> hand, bool & threeKind);
void isTwoPairOrOnePair(vector<Card> hand, bool & twoPair, bool & onePair);


vector<Card> best5Cards(const Hand & h);//ADAM

#endif /* defined(__Lab2__Hand__) */
