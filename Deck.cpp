//
//  Deck.cpp
//  Lab2
//
//  Created by Carlie Abraham on 2/28/15.
//  Copyright (c) 2015 Carlie Abraham. All rights reserved.
//
#include "stdafx.h"
#include "Deck.h"

//constructor that takes in a file name and loads the codes into the deck as cards
Deck::Deck(string fileName){
    int returnValue = load(fileName);
    if (returnValue != deckErrMsg::deckSuccess){
        throw(returnValue);
    }
}

int Deck::load(string fileName){
    Card tempCard;
    bool flag;
    bool emptyfile = true;
    bool blankLine = true;
    ifstream ifs;
    string c;
    string nextLine;
    string subString;
    //open file and check to make sure it opened sucessfully
    ifs.open(fileName);
    if (ifs.is_open()){
        //this while loop continues as long as there are lines to parse
        while (getline(ifs, nextLine)){
            emptyfile = false; //if there was a line to parse, the file was not empty
            vector<Card> tempDeck;
            size_t found = nextLine.find("//"); //finds the index where '//' is located
            subString = nextLine.substr(index::zero, found); //creats a substring of nextLine that contains everything up until the //
            istringstream iss(subString);
            blankLine = true; //boolean flag that tells us if the line was blank
            //this while loop will continue as long as there are words to parse in the line
            while (iss >> c){
                blankLine = false; //if this line of code is executed, it is not a blank line
                flag = true; //flag tells us if the card definition string is valid
                //checks to make sure each code is 2 or three letters long
                if (c.length() == 2 || c.length() == 3){  //ks01
                    //if-else block determines value of code
                    if (c[index::zero] == '2'){
                        tempCard.v = value::two;
                    }
                    else if (c[index::zero] == '3'){
                        tempCard.v = value::three;
                    }
                    else if (c[index::zero] == '4'){
                        tempCard.v = value::four;
                    }
                    else if (c[index::zero] == '5'){
                        tempCard.v = value::five;
                    }
                    else if (c[index::zero] == '6'){
                        tempCard.v = value::six;
                    }
                    else if (c[index::zero] == '7'){
                        tempCard.v = value::seven;
                    }
                    else if (c[index::zero] == '8'){
                        tempCard.v = value::eight;
                    }
                    else if (c[index::zero] == '9'){
                        tempCard.v = value::nine;
                    }
                    else if (c[index::zero] == '1'){
                        tempCard.v = value::ten;
                    }
                    else if (c[index::zero] == 'j' || c[index::zero] == 'J'){  //ks01
                        tempCard.v = value::jack;
                    }
                    else if (c[index::zero] == 'q' || c[index::zero] == 'Q'){
                        tempCard.v = value::queen;
                    }
                    else if (c[index::zero] == 'k' || c[index::zero] == 'K'){
                        tempCard.v = value::king;
                    }
                    else if (c[index::zero] == 'a' || c[index::zero] == 'A'){
                        tempCard.v = value::ace;
                    }
                    else{
                        //flag will turn false if the code does not match up with a card
                        flag = false;
                        cout << "Text file entered contains an invalid code. There is no such code as " << c << "." << endl;
                    }
                    
                    int index;
                    //checks to see if the value is 10, and if it is, sets index to 2 (which is
                    //the index that will contain the code corresponding to the suit)
                    if (c[index::one] == '0'){
                        index = index::twoo;
                        if (c[index::zero] == '1'){
                            index = index::twoo;
                        }
                        else{
                            //if c[1] was 0, but c[0] was not one, then the code was inaccurate
                            flag = false;
                            cout << "Text file entered contains an invalid code. There is no such code as " << c << "." << endl;
                        }
                    }
                    else{
                        index = index::one;
                    }
                    //if-else block to determine suit
                    if (flag){
                        if (c[index] == 'h' || c[index] == 'H'){
                            tempCard.s = suit::heart;
                        }
                        else if (c[index] == 's' || c[index] == 'S'){
                            tempCard.s = suit::spade;
                        }
                        else if (c[index] == 'd' || c[index] == 'D'){
                            tempCard.s = suit::diamond;
                        }
                        else if (c[index] == 'c' || c[index] == 'C'){
                            tempCard.s = suit::club;
                        }
                        else{
                            //if the code does not correspond to one of the codes above, it is invalid
                            flag = false;
                            cout << "Text file entered contains an invalid code. There is no such code as " << c << "." << endl;
                        }
                    }
                    //checks to see that there are no more letters after the one that
                    //corrrespondes to the suit so that we determine if the code is invalid
                    if (c.length() != (++index)){
                        flag = false;
                        cout << "Text file entered contains an invalid code. There is no such code as " << c << "." << endl;
                    }
                    //if the code was valid (flag has not been set to false) and the card is added to the deck
                    if (flag){
                        tempDeck.push_back(tempCard);
                    }
                }
                else{
                    cout << "Text file entered contains an invalid code. There is no such code as " << c << "." << endl;
                }
            }
            //if the line is not blank, check to see if there was the correct number of card
            //definition strings, and if so, copy all the cards into the master deck
            //if not, print out a warning to the user with the line of codes that was incorrect, and why it was incorrect
            if (!blankLine){
                for (unsigned int i = 0; i < tempDeck.size(); i++){
                    deck.push_back(tempDeck[i]);
                }
            }
        }
        //checks to see if the file was empty
        if (emptyfile){
            return deckErrMsg::deckEmptyFile;
        }
        //closes the file, and returns the success code (0)
        ifs.close();
        return deckErrMsg::deckSuccess;
    }
    //alerts user that the file could not be opened, and returns an error code
    else{
        return deckErrMsg::deckFileDidNotOpen;
    }
}

//shuffles method that shuffles the cards
void Deck::shuffle(){
    random_device rd;
    mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

//returns the size of the deck
int Deck::size() const{
    return deck.size();
}

//insertion operator that pritns out card definition strings in a deck to the output stream
ostream & operator<<(ostream & out, const Deck & d) {
    for (unsigned int i = 0; i < d.deck.size(); ++i){
        Card card = d.deck[i];
        string suit;
        string value;
        switch (card.s){
            case suit::club: suit = "C"; break;
            case suit::diamond: suit = "D"; break;
            case suit::heart: suit = "H"; break;
            case suit::spade: suit = "S"; break;
        }
        switch (card.v){
            case value::ace: value = "A"; break;
            case value::two: value = "2"; break;
            case value::three: value = "3"; break;
            case value::four: value = "4"; break;
            case value::five: value = "5"; break;
            case value::six: value = "6"; break;
            case value::seven: value = "7"; break;
            case value::eight: value = "8"; break;
            case value::nine: value = "9"; break;
            case value::ten: value = "10"; break;
            case value::jack: value = "J"; break;
            case value::queen: value = "Q"; break;
            case value::king: value = "K"; break;
        }
        out << value << suit << endl;
    }
    return out;
}

//adds a card to the deck
void Deck::add_card(Card c) {
    deck.push_back(c);
}

//default constructor that initializes the deck to be empty
Deck::Deck() {
    deck = {};
}
