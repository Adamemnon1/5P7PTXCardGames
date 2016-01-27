/*
Authors: Carlie Abraham, Brian Lam, Adam Sandor
Date: 4/5/15
Lab: Lab 4.
Purpose: The Game begins and ends the poker game.
It also keeps track of the players involved.

*/

#include "stdafx.h"
#include "game.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "fivecarddraw.h"
#include "SevenCardStud.h"

using namespace std;

//Static pointer to refer to the game
shared_ptr<Game> Game::gamePointer = nullptr;

//Default constructor
Game::Game() {
	deck = {};
	players = {};
}

//Returns a pointer to the instance
shared_ptr<Game> Game::instance() {
	if (gamePointer == nullptr){
		//No game has been started
		throw(err_noinstance);
	}
	else{
		return gamePointer;
	}
}

// Start a game - game name passed in as a string
void Game::start_game(const string & g) {
	if (!(gamePointer == nullptr)) {
		// If game has been started, throw an error
		throw(err_gamestarted);
	}
	else if (g == game_fivecarddraw) {
		gamePointer = make_shared<FiveCardDraw>();
	}
	else if (g == game_sevencardstud) {
		gamePointer = make_shared<SevenCardStud>();
	}
	else {
		throw(err_unknowngame);
	}
}

// Display >> onto console and ask for user input. Save to query input.
void Game::get_input(string & query) {
	cin.clear();
	cout << ">> ";
	getline(cin, query);
	cin.clear();
	std::transform(query.begin(), query.end(), query.begin(), ::tolower);
}

void Game::stop_game() {
	if (gamePointer == nullptr) {
		throw(err_nogameprogress);
	}

	//Ask user if they want to start a new game
	string startnewgame;
	cout << question_startnewgame << endl;
	cout << inputlabel;
	get_input(startnewgame);

	while (true) {
		// If so, ask what sort of game.
		if (startnewgame == yesResponse) {
			string gametype;
			cout << question_newgametype << endl;
			//yes
			cout << inputlabel;
			get_input(gametype);


			// See if current players want to stay
			string response;
			cout << leavegamebro << endl;
			get_input(response);
			bool playerExists = true;
			if (response == yesResponse){
				// Prompt for who's leaving the game
				cout << whosleaving << endl;
				string name;
				cin.clear();
				cout << inputlabel;
				getline(cin, name);
				cin.clear();
				shared_ptr<Player> tempPlayer = gamePointer->find_player(name);
				// Try to resolve the player name into a pointer
				if (tempPlayer == nullptr){
					cout << whoutalkingbout << name << period << endl;
					playerExists = false;
				}
				if (playerExists){
					ofstream ofs;
					ofs.open(tempPlayer->name);
					if (ofs.is_open()){
						// Print player's information into a file
						ofs << tempPlayer->name << outerspace << tempPlayer->won << outerspace << tempPlayer->lost << outerspace << tempPlayer->numChips;//ADAM
					}
					ofs.close();
					int index = index::negativeOne;
					for (unsigned int i = index::zero; i < gamePointer->players.size(); i++){
						if (tempPlayer->name == gamePointer->players[i]->name){
							// Find the index where the player is in the vector
							index = i;
						}
					}
					//Remove the player from the game
					gamePointer->players.erase(gamePointer->players.begin() + index);
				}
			}
			do{
				//Player is entering the game. 
				cout << whoscoming << endl;
				cout << inputlabel;
				cin.clear();
				getline(cin, response);
				cin.clear();
				if (response == yesResponse){
					cout << whatshisnamebro << endl;
					string playerName;
					//cout << inputlabel;
					cin.clear();
					cout << inputlabel;
					getline(cin, playerName);
					cin.clear();
					try{
						gamePointer->add_player(playerName);
					}
					catch (char const* message) {
						cout << message << endl;
					}
					catch (...){
						continue;
					}
					cout << playerName << " has been added." << endl;
				}
			} while (response != noResponse);
			if (gamePointer->players.size() < 2) {
				cout << "You have not entered enough players, so the game has ended." << endl;
				// HARD CODED
				// Save player information if players leaving game causes too few players
				for (shared_ptr<Player> p : gamePointer->players) {
					ofstream ofs;
					ofs.open(p->name);
					if (ofs.is_open()){
						// Print player's information into a file
						ofs << p->name << outerspace << p->won << outerspace << p->lost << outerspace << p->numChips;//ADAM
					}
					ofs.close();
				}
				gamePointer->players.erase(gamePointer->players.begin(), gamePointer->players.end());
			}
			else{
				start_game(gametype);
			}
		}
		else if (startnewgame == noResponse) {
			shared_ptr<Game> temp;
			gamePointer = temp;
		}
	}
}

// Add a new player to the game
void Game::add_player(const string & plName) {
	for (shared_ptr<Player> sp : players) {
		if (sp->name == plName) {
			throw(err_playeralreadyplaying);
		}
	}
	Player pl = Player(plName);
	shared_ptr<Player> spp = make_shared<Player>(pl);
	players.push_back(spp);
}

shared_ptr<Player> Game::find_player(const string & plName) {
	for (shared_ptr<Player> sp : players) {
		string na = sp->name;
		if (na == plName) {
			return sp;
		}
	}

	shared_ptr<Player> spp;
	return spp;
}

Game::~Game() {
}

int Game::playerCount(){
	return players.size();
}



void Game::collectAntes() {
	for (shared_ptr<Player> sp : players) { 
		sp->numChips -= 1;
		++pot;
	}
}


/*
Finds the value bet needed to reach to remain in the round
*/
int Game::maxBet(vector<int> vi) {
	int max = 0;
	for (int c : vi) {
		if (c > max) {
			max = c;
		}
	}
	return max;
}

void Game::betting(){

	amountBetPerPlayer = {};
	//Set up amount bet vector
	for (shared_ptr<Player> player : players) {
		amountBetPerPlayer.push_back(0);
		player->noMoreBetsThisRound = true;
		player->betEnough = false;
	}
	for (int i = 0; i < playersStillInRound.size(); i++){
		playersStillInRound[i]->noMoreBetsThisRound = false;
	}


	//need to reset all member variables properly

	bool keep_betting = true;

	int amount;
	int bet_round = 1;
	int check_count = 0;

	string response;
	string raise_response;
	string bet_check;
	string fold_call_raise;

	int position = dealerPos + 1;


	while (keep_betting) {
		// Phase 1
		//if the position is greater or equal to the amount of players, reset it to 0
		if (position >= players.size()){
			position = 0;
		}
		cout << players[position]->name << ", you have " << players[position]->numChips <<
			" chips." << endl;
		//if the players need to continue betting
		if (!(players[position]->noMoreBetsThisRound)){
			if (bet_round == 1) {
				// Prompt the player for betting input
				cout << players[position]->name << howryabettinFirst << endl;
				get_input(response);
				stringstream ss(response);
				ss >> bet_check;

				if (bet_check != betResponse && bet_check != checkResponse) {
					bet_check = checkResponse;
				}

				// Begin bet loop
				if (bet_check == betResponse) {
					cout << howmuchbetbro << endl;
					get_input(raise_response);

					//Bet one or two chips
					if (raise_response == "1" || raise_response == "2") {
						stringstream ss(raise_response);
						ss >> amount;
					}
					//Bad input
					else {
						amount = 1;
					}

					if (players[position]->numChips >= amount) {
						// Check if player has sufficient number of chips
						cout << players[position]->name << " chose to bet " << amount << " chips. " << endl; // Put into enum later
						players[position]->numChips -= amount;
						amountBetPerPlayer[position] += amount;
					}
					else {
						amountBetPerPlayer[position] += players[position]->numChips;
						players[position]->numChips = 0;
					}
					players[position]->betEnough = true;
					bet_round = 2;
				}
				// End bet loop

				else if (bet_check == checkResponse) {
					//Skips this player
					cout << players[position]->name << " chose to check. " << endl; // Put into enum later
					check_count++;
					if (check_count == playersStillInRound.size()) {
						//Everybody has checked
						keep_betting = false;
					}
				}
				// End check loop
			} // End Round 1 loop
			else{
				if (players[position]->numChips > maxBet(amountBetPerPlayer) - amountBetPerPlayer[position]) {
					cout << players[position]->name << howryabettinSecond << endl;
				}
				else {
					cout << players[position]->name << howryabettincheapscate << endl;
				}

				get_input(response);
				stringstream ss(response);
				//Default response to callResponse
				ss >> fold_call_raise;
				if (fold_call_raise != foldResponse && fold_call_raise != callResponse && fold_call_raise != raiseResponse){
					fold_call_raise = callResponse;
				}

				if (fold_call_raise == foldResponse) {
					players[position]->noMoreBetsThisRound = true;
					players[position]->foldOrAllIn = true;

					cout << players[position]->name << " chose to fold. " << endl;
					for (int j = playersStillInRound.size() - 1; j >= 0; j--){
						if (playersStillInRound[j]->name == players[position]->name){
							cout << playersStillInRound[j]->name << "out of round" << endl;
							playersStillInRound.erase(playersStillInRound.begin() + j);
						}
					}
					if (playersStillInRound.size() == 1){
						//the remaining player in _players is the winner
						keep_betting = false;
					}
				}
				else if (fold_call_raise == callResponse) {
					cout << players[position]->name << " chose to call. " << endl; 
					int maxBetted = maxBet(amountBetPerPlayer);
					int amountToCall = maxBetted - amountBetPerPlayer[position];
					if (amountToCall >= players[position]->numChips){
						amountBetPerPlayer[position] += players[position]->numChips;
						players[position]->numChips = 0; // all in - they should not bet more
					}
					else{
						players[position]->numChips -= amountToCall;
						amountBetPerPlayer[position] += amountToCall;
					}
					players[position]->betEnough = true;
				}
				else if (fold_call_raise == raiseResponse) {
					cout << players[position]->name << " chose to raise. " << endl;
					int maxBetted = maxBet(amountBetPerPlayer);
					int amountToCall = maxBetted - amountBetPerPlayer[position];
					if (amountToCall >= players[position]->numChips) {
						//the player did not have enough chips to raise, so they are calling (and going all in)
						cout << "You do not have enough chips to raise, so you are calling (and going all in). 	" << endl;
						amountBetPerPlayer[position] += players[position]->numChips;
						players[position]->numChips = 0;
						players[position]->noMoreBetsThisRound = true;
						players[position]->betEnough = true;
					}
					else {
						//player still has extra chips and is able to raise
						for (shared_ptr<Player> player : players) {
							player->betEnough = false;
						}
						players[position]->betEnough = true;
						players[position]->numChips -= amountToCall;
						amountBetPerPlayer[position] += amountToCall;
						cout << howmuchraisebro << endl;
						get_input(response);
						stringstream ss(response);
						int numRaised;
						ss >> numRaised;
						if (numRaised != 2 && numRaised != 1){
							numRaised = 1;
						}
						if (numRaised >= players[position]->numChips){
							amountBetPerPlayer[position] += players[position]->numChips;
							players[position]->numChips = 0;
							players[position]->noMoreBetsThisRound = true;
						}
						else{
							amountBetPerPlayer[position] += numRaised;
							players[position]->numChips -= numRaised;
						}

					}
				}
			}//end else loop - round 2

		} //end if statement
		// Determine if players need to keep betting
		cout << players[position]->name << ", you now have " << players[position]->numChips <<
			" chips." << endl << endl;
		if (players[position]->numChips == 0){
			players[position]->foldOrAllIn = true;
		}
		if (keep_betting){
			keep_betting = false;
			for (shared_ptr<Player> player : players){
				if (!player->foldOrAllIn){
					if (!player->betEnough){
						keep_betting = true;
					}
				}
			}
		}
		position++;
	}
	// End of round - sum up the chips into the pot
	for (int chips : amountBetPerPlayer){
		pot += chips;
	}
	for (int i = 0; i < playersStillInRound.size(); i++){
		cout << playersStillInRound[i]->name << " is still in round" << endl;
	}
	cout << "The pot is " << pot << endl;

}

void Game::checkForNoChips(){
	string response;
	vector<shared_ptr<Player>> _players = players;
	for (int i = _players.size() - 1; i >= 0; i--){
		if (_players[i]->numChips == 0){
			cout << _players[i]->name << ", you do not have enough chips to continue. Since you have not requested to leave, you will recieve 20 chips to continue." << endl;
			players[i]->numChips = 20;
		}
	}
}
