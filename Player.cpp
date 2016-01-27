/*
 Authors: Carlie Abraham, Brian Lam, Adam Sandor
 Date: 4/5/15
 Lab: Lab 3.
 Purpose: Represent the players in the game and can rank their respective hands.
 
 */

#include "stdafx.h"
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "card.h"
#include "Hand.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <typeinfo>
#include "player.h"

using namespace std;

//constructor for player
Player::Player(string plName) : name(plName), won(winLoss::initialWin), lost(winLoss::initialLoss), numChips(20) {
    hand = {};
    
    
    try {
        ifstream filereading;
        filereading.open(plName, ios::in);
        vector<Card> tempcards;
        if (filereading.is_open()) {
            string line;
            while (std::getline(filereading, line)) { //reads entire line
                if (line.size() == index::zero) { //skip empty line
                    continue;
                }
                else{
                    stringstream ss(line);
                    string playerinfo;
                    string playerName;
                    int numWon;
                    int numLost;
                    
                    int chips;
                    
                    ss >> playerName;
                    plName = playerName;
                    ss >> numWon;
                    if (typeid(numWon) != typeid(int)) {
                        throw(fileError::numWonNotInt);
                    }
                    won = numWon;
                    ss >> numLost;
                    if (typeid(numLost) != typeid(int)) {
                        throw(fileError::numLostNotInt);
                    }
                    lost = numLost;
                    
                    
                    ss >> chips;
                    if (typeid(chips) != typeid(int)) {
                        throw(fileError::numChipsNotInt);
                    }
                    numChips = chips;
                    
                }
            }
        }
        else {
            throw (fileError::fileReadError);
        }
    } //end try
    catch (...) {
        //could not open file, or get wins, or get losses.
        won = winLoss::initialWin;
        lost = winLoss::initialLoss;
        name = plName;
    }
    
}

ostream& operator<<(ostream& os, const Player& player) {
    os << player.name << " " << player.won << " " << player.lost << endl;
    
    return os;
}

bool poker_rankTemp(shared_ptr<Player> pl1, shared_ptr<Player> pl2){
    if (pl1 == nullptr){
        return false;
    }
    if (pl2 == nullptr){
        return true;
    }
    return poker_rank(pl1->hand, pl2->hand);
}
