/*
 Authors: Carlie Abraham, Brian Lam, Adam Sandor
 
 Date: 4/5/15
 Lab: Lab 3.
 
 */

#pragma once

#include <string>
#include <memory>
#include "Hand.h"
using namespace std;

class Hand;
enum winLoss{
    increment = 1,
    initialWin = 0,
    initialLoss = 0
};
enum fileError{
    numWonNotInt,
    numLostNotInt,
    fileReadError,
    numChipsNotInt
};

struct Player {
    
    unsigned int numChips;
    bool noMoreBetsThisRound = false;
    bool betEnough = false;//this is fine
    
    string name;
    Hand hand;
    unsigned int won;
    unsigned int lost;
	bool foldOrAllIn = false;
	bool fold = false;
    
    Player(string plName);
};

ostream& operator<<(ostream& os, const Player& player);
bool poker_rankTemp(shared_ptr<Player> pl1, shared_ptr<Player> pl2);
