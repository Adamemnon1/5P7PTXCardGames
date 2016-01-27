/*
Authors: Carlie Abraham, Brian Lam, Adam Sandor
Date: 4/18/15
Lab: Lab 4.
Purpose: This is the FiveCardDraw file. It takes care of
the actions that occur in the poker game and how the game resolves.

*/

#include "stdafx.h"
#include "FiveCardDraw.h"

/*
Constructor that sets the deck to a standard of 52 cards
*/
FiveCardDraw::FiveCardDraw() {
	dealerPos = index::zero;
	discardDeck = {};
	for (int cardSuits = suit::club; cardSuits <= suit::spade; ++cardSuits) {
		for (int cardRanks = value::two; cardRanks <= value::ace; ++cardRanks) {
			value cv = static_cast<value>(cardRanks);
			suit cs = static_cast<suit>(cardSuits);
			Card tempCard;
			tempCard.s = cs;
			tempCard.v = cv;
			deck.add_card(tempCard);
		}
	}
}

/*
Asks the player which cards they would like to discard
*/
int FiveCardDraw::before_turn(Player & pl) {


	vector<int> cardsToBeDiscarded = {};
	bool loopy = true;
	bool error = false;
	cout << endl;
	cout << playerlabel << pl.name << endl;
	cout << handlabel << pl.hand << endl;
	while (loopy) {
		cardsToBeDiscarded = {};
		string cards;
		//asks for player to discard cards
		cout << whichcards << pl.name << liketodiscard << endl;
		get_input(cards);
		bool confirm = false;
		//asks if the player really wants to discard nothing
		while (cards.size() == index::zero && confirm == false) {
			string option;
			cout << usurebro << endl;
			get_input(option);
			if (option == yesResponse) {
				confirm = true;
			}
			if (option == noResponse) {
				cout << whichcards << pl.name << liketodiscard << endl;
				//cout << inputlabel;
				get_input(cards);
			}
		}
		stringstream ss(cards);
		int index;
		loopy = false;
		//checks input for valid indicies
		while (ss >> index && loopy == false){
			if (index < index::zero || index >= pl.hand.size()){
				cout << validindices << to_string(pl.hand.size()) << endl;
				loopy = true;
			}
			if (loopy == false){
				for (unsigned int i = index::zero; i < cardsToBeDiscarded.size(); i++){
					if (index == cardsToBeDiscarded[i]){
						loopy = true;
						cout << repeatedindex << endl;
					}
				}
			}
			if (loopy == false){
				cardsToBeDiscarded.push_back(index);
			}
		}
	}

	//discard cards
	sort(cardsToBeDiscarded.begin(), cardsToBeDiscarded.end()); //orders indexes from lowest to highest
	if (cardsToBeDiscarded.size() > handCodes::emptyHand){ //if no indicies entered, no deletion necesary
		for (int i = cardsToBeDiscarded.size() - index::one; i >= index::zero; i--){
			Card c = pl.hand[cardsToBeDiscarded[i]];
			discardDeck.add_card(c);
			pl.hand.remove_card(cardsToBeDiscarded[i]);
		}
	}
	return errorMsg::success;
}

/*
Adds stuff to the hands if they discard stuff
*/
int FiveCardDraw::turn(Player & pl) {
	while (pl.hand.size() < gameOfPoker::sizeOfHand5){
		if (deck.size() <= index::zero){
			if (discardDeck.size() <= index::zero){
				return errorMsg::notEnoughCards;
			}
			else{
				pl.hand << discardDeck;
			}
		}
		else{
			pl.hand << deck;
			if (deck.size() == index::zero){
				discardDeck.shuffle();
			}
		}
	}
	return errorMsg::success;
}

/*
Prints the player name and hand after the turn
*/
int FiveCardDraw::after_turn(Player & pl){

	cout << playerlabel << pl.name << endl;
	cout << handlabel << pl.hand << endl;
	return errorMsg::success;
}


/*
Deals out cards to each person, then calls before_turn method
*/
int FiveCardDraw::before_round(){
	pot = 0;

	checkForNoChips();

	collectAntes();
	for (shared_ptr<Player> player : players){
		player->foldOrAllIn = false;

	}

	playersStillInRound = {};
	for (int i = 0; i < players.size(); i++){
		playersStillInRound.push_back(players[i]);
	}
	betting();

	if (playersStillInRound.size()>1){
		deck.shuffle();
		unsigned int numPlayers = players.size();
		int cardsToBeDealed = numPlayers * gameOfPoker::sizeOfHand5;
		unsigned int position = dealerPos + index::one;
		for (int i = index::zero; i < cardsToBeDealed; i++){

			if (position >= numPlayers){
				position = index::zero;
			}

			//Adds a card to the player's hand from the deck
			if (deck.size() > index::zero) {
				players[position]->hand << deck;
			}
			else {
				throw errorMsg::noCardsLeft;
			}
			position++;

		}
		cout << "in before round method" << endl;

		//calls before_turn method for each player
		for (unsigned int i = index::zero; i < playersStillInRound.size(); i++){
			cout << "calling before turn on " << playersStillInRound[i]->name << endl;
			before_turn(*playersStillInRound[i]);
		}

		for (int i = 0; i < playersStillInRound.size(); i++){
			cout << "still in round: " << playersStillInRound[i]->name << endl;
		}
	}
	return errorMsg::success;
}



/*
Iterates through each player and calls their
turn and after_turn methods
*/
int FiveCardDraw::round(){
	if (playersStillInRound.size()>1){
		int position = dealerPos + index::one;
		int numPlayers = playersStillInRound.size();
		for (unsigned int i = index::zero; i < playersStillInRound.size(); i++){
			if (position >= numPlayers){
				position = index::zero;
			}
			try {
				cout << playersStillInRound[position]->name << " is taking a turn" << endl;
				int num = turn(*playersStillInRound[position]);
				if (num == index::zero){
					after_turn(*playersStillInRound[position]);
				}
				else{
					return num;
				}
				position++;
			}
			catch (errorMsg err) {
				throw err;
			}
		}
		betting();
	}
	return errorMsg::success;
}

/*
Prints out everybody's info and gives the opportunity for
players to enter and leave the game
*/
int FiveCardDraw::after_round(){
	vector<shared_ptr<Player>> tempVP = vector<shared_ptr<Player>>(playersStillInRound);
	sort(tempVP.begin(), tempVP.end(), poker_rankTemp);

	unsigned int lastPlIndex = tempVP.size() - index::one;

	tempVP[index::zero]->won += winLoss::increment;
	cout << tempVP[index::zero]->name << winround << endl << endl;

	tempVP[index::zero]->numChips += pot;

	cout << tempVP[index::zero]->name << winpot << pot << "!" << endl;
	pot = 0;


	for (int i = 0; i < players.size(); i++){
		if (players[i]->name != tempVP[0]->name){
			players[i]->lost += winLoss::increment;
		}
	}


	for (shared_ptr<Player> p : players) {
		//check the folded flag here. If yes, do not print out hand, rather only that they folded.
		cout << playerlabel << p->name << endl;
		cout << winlabel << p->won << endl;
		cout << losslabel << p->lost << endl;
		cout << chipslabel << p->numChips << endl;
		cout << handlabel << p->hand << endl;
	}
	string response;

	do{
		cout << leavegamebro << endl;
		get_input(response);
		bool playerExists = true;
		if (response == yesResponse){
			cout << whosleaving << endl;
			string name;
			cin.clear();
			cout << ">> ";
			getline(cin, name);
			cin.clear();
			shared_ptr<Player> tempPlayer = find_player(name);
			if (tempPlayer == nullptr){
				cout << whoutalkingbout << name << period << endl;
				playerExists = false;
			}
			if (playerExists){
				ofstream ofs;
				ofs.open(tempPlayer->name);
				if (ofs.is_open()){
					ofs << tempPlayer->name << outerspace << tempPlayer->won << outerspace << tempPlayer->lost << outerspace << tempPlayer->numChips;
				}
				ofs.close();
				int index = index::negativeOne;
				for (unsigned int i = index::zero; i < players.size(); i++){
					if (tempPlayer->name == players[i]->name){
						index = i;
					}
				}
				players.erase(players.begin() + index);
				cout << name << " has left the game." << endl;
			}
		}
	} while (response != noResponse);

	do{
		// Add a new player into the game
		cout << whoscoming << endl;
		cout << inputlabel;
		cin.clear();
		getline(cin, response);
		cin.clear();
		if (response == yesResponse){
			cout << whatshisnamebro << endl;
			string playerName;
			cin.clear();
			cout << ">> ";
			getline(cin, playerName);
			cin.clear();
			try{
				add_player(playerName);
				cout << playerName << " has been added." << endl;
			}
			catch (char const* message) {
				cout << message << endl;
			}
			catch (...){
				continue;
			}

		}
	} while (response != noResponse);

	checkForNoChips();

	dealerPos++;
	if (dealerPos >= players.size()){
		dealerPos = index::zero;
	}

	for (unsigned int i = index::zero; i < players.size(); i++){
		(*players[i]).hand = {};
	}
	discardDeck = {};
	deck = {};
	// Create a standard deck of 52 cards
	for (int cardSuits = suit::club; cardSuits <= suit::spade; ++cardSuits) {
		for (int cardRanks = value::two; cardRanks <= value::ace; ++cardRanks) {
			value cv = static_cast<value>(cardRanks);
			suit cs = static_cast<suit>(cardSuits);
			Card tempCard;
			tempCard.s = cs;
			tempCard.v = cv;
			deck.add_card(tempCard);
		}
	}

	return errorMsg::success;
}




