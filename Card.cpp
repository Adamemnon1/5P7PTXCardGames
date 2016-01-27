// Card.cpp : Defines the entry point for the console application.
//
//This program defines the functions parseCards, printDeck, and ussageMsg
// author: Charlotte Abraham carlieabraham@wustl.edu
//#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <sstream>
#include "Card.h"
using namespace std;

//Parses a .txt document, and uses the codes in the document to create cards,
//which are added to a vector of cards called deck


//operator< method that compares two cards, first with regards to value, and then suit
//if c1 has a smaller value (or smaller suit, if both values are equal), the method returns true
bool Card::operator< (const Card &c2) const{
    Card c1 = *this;
    if (c1.v < c2.v){
        return true;
    }
    else if (c1.v > c2.v){
        return false;
    }
    else{
        if (c1.s < c2.s){
            return true;
        }
        else{
            return false;
        }
    }
}

//usage message telling the user what to input into the program
void usageMsg(string programName, string error){
    cout << endl << "Invalid usage!" << endl << endl;
    cout << "Usage for " << programName << ":" << endl;
    cout << "$ " << programName << " [gamename] Player1 Player2 ... LastPlayer" << endl << endl;
    cout << "where gamename refers to the game to be played (such as \"FiveCardDraw\"),\
    followed by the name of the players in the game. There must be at least two players." << endl;
    cout << error << endl << endl;
}

void printError(string errorMessage) {
    cout << "The program encountered an error." << endl << endl;
    cout << " === Error Details ===" << endl;
    cout << errorMessage << endl;
}

//helper function to print out messages to the output stream
void printMessage(string message){
    string separatingLine = "~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << endl << separatingLine << endl << message << endl << separatingLine << endl << endl;
}

//Print out card
string Card::toString() {
    string cardString = "";
    string suit;
    string value;
    switch (this->s){
        case suit::club: suit = "C"; break;
        case suit::diamond: suit = "D"; break;
        case suit::heart: suit = "H"; break;
        case suit::spade: suit = "S"; break;
    }
    switch (this->v){
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
    cardString += value;
    cardString += suit;
    cardString += " ";
    return cardString;
}
