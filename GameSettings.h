
#ifndef __GameSettings_
#define __GameSettings_
#include <string>

using namespace std;

const int ONE = 1;
const int TWO = 2;

const string game_fivecarddraw = "FiveCardDraw";
const string game_sevencardstud = "SevenCardStud";

const string err_noinstance = "Instance not available";
const string err_gamestarted = "Game already started";
const string err_unknowngame = "Unknown game";
const string err_nogameprogress = "No game in progress";
const string err_playeralreadyplaying = "Player is already playing";
const string destructor_message = "Game destructor has been called.";

const string question_startnewgame = "The game has ended. Would you like to start a new game?";
const string question_newgametype = "What's the name of the game you want to play?";

const string yesResponse = "yes";
const string noResponse = "no";
const string playerlabel = "Player: ";
const string handlabel = "Hand: ";
const string whichcards = "Which cards would player ";
const string liketodiscard = " like to discard? List the indices of the cards you would like to discard (indices start at 0).";
const string inputlabel = ">> ";
const string usurebro = "Are you sure you do not want to discard anything? Enter 'yes' or 'no' please. ";
const string validindices = "Please enter valid indices from 0 to ";
const string repeatedindex = "Repeated index";
const string waterudoing = "Please enter an integer";
const string winround = " wins this round!";
const string winlabel = "Wins: ";
const string losslabel = "Losses: ";
const string leavegamebro = "Do any players want to LEAVE the game? Enter \"yes\" or \"no\".";
const string whosleaving = "Enter the name of the player that is leaving.";
const string whoutalkingbout = "There is no player with the name ";
const string period = ".";
const string outerspace = " ";
const string whoscoming = "Do any players want to ENTER the game? Enter \"yes\" or \"no\".";
const string whatshisnamebro = "Enter the name of the player that is entering.";

const string howryabettinFirst = ", What would you like to do? Bet, or Check? Input bet or check. [Default: check]";
const string howryabettinSecond = ", What would you like to do? Fold, Call, or Raise? Input fold, call, or raise. [Default: call]";
const string howmuchbetbro = "Would you like to bet 1 or 2 chips? [Default: 1 chip]";
const string howmuchraisebro = "Would you like to raise 1 or 2 chips? [Default: 1 chip]";
const string winpot = " has won the pot of ";
const string chipslabel = "Chips: ";
const string howryabettincheapscate = " You do not have enough chips to raise. You may call or fold. Input fold or call. [Default: call].";
const string yourhandis = "Your hand is: ";
const string handis = " hand is: ";

const string betResponse = "bet";
const string callResponse = "call";
const string foldResponse = "fold";
const string raiseResponse = "raise";
const string checkResponse = "check";


#endif /* defined(__GameSettings__) */
