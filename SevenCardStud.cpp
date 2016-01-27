#include "stdafx.h"
#include "SevenCardStud.h"

/*
Constructor that sets the deck to a standard of 52 cards
*/
SevenCardStud::SevenCardStud() {
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


// ha01 -- this is the exact same method from FiveCardDraw and is never used for SevenCardDraw
int SevenCardStud::before_turn(Player & pl) {
	vector<int> cardsToBeDiscarded = {};
	bool loopy = true;
	bool error = false;
	cout << endl;
	cout << playerlabel << pl.name << endl;
	cout << handlabel << pl.hand << endl;

	printHands(pl);

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

int SevenCardStud::after_turn(Player & pl) {
	// Print out player information after turn
	cout << playerlabel << pl.name << endl;
	cout << handlabel << pl.hand << endl;
	return errorMsg::success;
}

int SevenCardStud::before_turn1(){
	cout << "Turn 1" << endl;
	int numCardsDealtPerPerson = 3;
	int position = dealerPos + 1;
	int numPlayers = playersStillInRound.size();
	for (unsigned i = index::zero; i < numCardsDealtPerPerson; i++)
	{
		for (int j = 0; j<playersStillInRound.size();j++){
			if (position >= numPlayers){
				position = index::zero;
			}

			if (deck.size() > index::zero) {
				Hand tempHand = {};
				tempHand << deck;

				Card addedCard = tempHand[0];

				if (i < 2){
					addedCard.isVisible = false;
				}
				else{
					addedCard.isVisible = true;
				}
				players[position]->hand.addCard(addedCard);
				players[position]->hand.sortHand();

			}//end deck if
			else {
				throw errorMsg::noCardsLeft;
			}
			position++;
		}

	}

	return errorMsg::success;
}
int SevenCardStud::before_turn234(){
	int numCardsDealtPerPerson = 1;
	int position = dealerPos + 1;
	int numPlayers = playersStillInRound.size();
	for (unsigned i = index::zero; i < numCardsDealtPerPerson; i++){
		for (int j = 0; j<playersStillInRound.size();j++){
			if (position >= numPlayers){
				position = index::zero;
			}

			if (deck.size() > index::zero) {
				Hand tempHand = {};
				tempHand << deck;

				Card addedCard = tempHand[0];
				addedCard.isVisible = true;

				players[position]->hand.addCard(addedCard);
				players[position]->hand.sortHand();


			}//end deck if
			else {
				throw errorMsg::noCardsLeft;
			}
			position++;
		}

	}
	return errorMsg::success;
}
int SevenCardStud::before_turn5(){
	int numCardsDealtPerPerson = 1;
	int position = dealerPos + 1;
	int numPlayers = playersStillInRound.size();
	for (unsigned i = index::zero; i < numCardsDealtPerPerson; i++)
	{
		for (int j = 0; j<playersStillInRound.size();j++){ // ha02
			if (position >= numPlayers){
				position = index::zero;
			}

			if (deck.size() > index::zero) {
				Hand tempHand = {};
				tempHand << deck;

				Card addedCard = tempHand[0];
				addedCard.isVisible = false;

				players[position]->hand.addCard(addedCard); // ha02
				players[position]->hand.sortHand();

			}//end deck if
			else {
				throw errorMsg::noCardsLeft;
			}
			position++;
		}

	}
	return errorMsg::success;
}

int SevenCardStud::turn(Player & pl){
	
	cout << endl << playerlabel << pl.name << endl;
	cout << handlabel << pl.hand;

	printHands(pl);
	cout << endl;

	return errorMsg::success;
}

int SevenCardStud::before_round() {
	pot = 0;
	checkForNoChips();
	for (int i = 0; i < players.size(); i++){
		players[i]->hand = {};
	}

	for (int i = 0; i<players.size(); i++){
		cout << players[i]->name << " has " << players[i]->numChips << " chips." << endl;
	}
	collectAntes();
	for (shared_ptr<Player> player : players){
		player->foldOrAllIn = false;
	}
	playersStillInRound = {};
	for (int i = 0; i<players.size(); i++){
		playersStillInRound.push_back(players[i]);
	}
	deck.shuffle();

	return errorMsg::success;
}

int SevenCardStud::compareHands( Hand  h1, Hand h2) { 
	vector<Card> hand1 = h1.getHandVect();
	vector<Card> hand2 = h2.getHandVect();
	 
	
	if (hand1.size() == 0 && hand2.size() == 1) {
		return 1;
	}
	
	
	for (Card c : hand1) {
		for (int c1 = 0; c1 < hand2.size(); ++c1) {
			if (c.v != hand2[c1].v || c.s != hand2[c1].s ) {
				return c1;
			}
		}
	}
	return errorMsg::success;
}

bool SevenCardStud::diffCardHere(Hand h1, Hand h2) {
	vector<Card> hand1 = h1.getHandVect();
	vector<Card> hand2 = h2.getHandVect();
	
	if (hand1.size() == 0 && hand2.size() == 1) { 
		return false;
	}


	for (Card c : hand1) {
		for (Card c1 : hand2) {
			if (c.v != c1.v || c.s != c1.s) {
				return true;;
			}
		}
	}
	return false;
}

int SevenCardStud::round() {
	// return -1;
	int position = dealerPos + index::one;
	
	//turn 1 for each player
	if (playersStillInRound.size() > 1){
		before_turn1();
		int numPlayers = playersStillInRound.size();
		for (unsigned int i = index::zero; i < numPlayers; i++){
			if (position >= numPlayers){
				position = index::zero;
			}
			try {
				turn(*playersStillInRound[position]);
				position++;
			}
			catch (errorMsg err) {
				throw err;
			}
		}
		betting();
	}

	//turn 2 3 4 for each player
	for (int i = 0; i < 3; i++){
		if (playersStillInRound.size() > 1){
			before_turn234();
			int numPlayers = playersStillInRound.size();
			for (unsigned int i = index::zero; i < numPlayers; i++){
				if (position >= numPlayers){
					position = index::zero;
				}
				try {
					turn(*playersStillInRound[position]);
					
					position++;
				}
				catch (errorMsg err) {
					throw err;
				}
			}
			betting();
		}
	}

	//turn 5 for each player
	if (playersStillInRound.size() > 1){
		before_turn5();
		int numPlayers = playersStillInRound.size();
		for (unsigned int i = index::zero; i < numPlayers; i++){
			if (position >= numPlayers){
				position = index::zero;
			}
			try {
				turn(*playersStillInRound[position]);
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
int SevenCardStud::after_round() {
	vector<shared_ptr<Player>> tempVP = vector<shared_ptr<Player>>(playersStillInRound);
	sort(tempVP.begin(), tempVP.end(), poker_rankTemp);

	unsigned int lastPlIndex = tempVP.size() - index::one;

	tempVP[index::zero]->won += winLoss::increment;
	cout << tempVP[index::zero]->name << winround << endl << endl;
	tempVP[index::zero]->numChips += pot;
	pot = 0;
	cout << tempVP[index::zero]->name << winpot << pot << endl;

	for (int i = 0; i < players.size(); i++){
		if (players[i]->name != tempVP[0]->name){
			players[i]->lost += winLoss::increment;
		}
	}


	// Print out player iformation
	for (shared_ptr<Player> p : players) {
		cout << playerlabel << p->name << endl;
		cout << winlabel << p->won << endl;
		cout << losslabel << p->lost << endl;
		cout << chipslabel << p->numChips << endl;
		cout << handlabel << p->hand << endl;
	}
	string response;
	do{
		// Player is leaving the game
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
		// Player is entering the game
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

	checkForNoChips();

	// Rotate dealer position
	dealerPos++;
	if (dealerPos >= players.size()){
		dealerPos = index::one;
	}

	//Clear hands and decks
	for (unsigned int i = index::zero; i < players.size(); i++){
		(*players[i]).hand = {};
	}
	discardDeck = {};
	deck = {};
	
	//Create standard deck of 52 cards
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


//for printing out the hands of players depending on the card's visibility.
void SevenCardStud::printHands(Player & pl) {
	for (shared_ptr<Player> p : players) {
		if (pl.name == p->name) {
		
		}
		else
		{
			string theirCards = "";
			for (int c = 0; c < p->hand.size(); ++c)
			{
				if (p->hand[c].isVisible) {
					theirCards += p->hand[c].toString() + " ";
				}

			}
			for (int c = 0; c < p->hand.size(); ++c)
			{
				if (p->hand[c].isVisible) {
					
				}
				else {
					theirCards += "*";
					theirCards += " ";
				}
			}
			cout << p->name << handis << theirCards << endl;
		}
	}

}
