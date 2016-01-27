/*
Authors: Carlie Abraham, Brian Lam, Adam Sandor
Date: 4/5/15
Lab: Lab 3.


*/

#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>
#include "Card.h"
#include "Hand.h"
#include "Player.h"
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include "GameSettings.h"
using namespace std;


class Game {
public:
	Game();
	virtual ~Game();
	static shared_ptr<Game> instance();
	static void start_game(const string & g);
	static void stop_game();
	void add_player(const string & plName);
	int playerCount();
	shared_ptr<Player> find_player(const string & plName);
	static void get_input(string & query);

	virtual int before_turn(Player & pl) = 0; //=0 to make the method pure virtual
	virtual int turn(Player & pl) = 0;
	virtual int after_turn(Player & pl) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
	void checkForNoChips();


	int pot;
	vector<int> amountBetPerPlayer;
	virtual void collectAntes();
	virtual int maxBet(vector<int> vi);
	virtual void betting();
	vector<shared_ptr<Player>> playersStillInRound;


protected:
	static shared_ptr<Game>  gamePointer; //default initialize to null, hopefully.
	Deck deck;
	vector<shared_ptr<Player>> players;
	size_t dealerPos;
};

