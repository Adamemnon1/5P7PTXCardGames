/*
 Authors: Carlie Abraham, Brian Lam, Adam Sandor
 Date: 4/5/15
 Lab: Lab 3.
 Purpose: Starts the poker game with starting players and shows
 relevant error messages.
 
 */

#include "stdafx.h"
#include "Main.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Game.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    string errorMessage = "";
    string shuffleCode = "-shuffle";
    string gameName = "";
    bool constructDeck = false;
    shared_ptr<Game> game;
    
    // Check if there aren't enough arguments
    if (argc < argvIndex::minNumOfArguments){ //4
        errorMessage = "You have not entered in enough arguments.";
        usageMsg(argv[argvIndex::programName], errorMessage);
        return errorMsg::tooFewArguments;
    }
    
    else {
        try{
            //Start the game
			Game::start_game(argv[argvIndex::gameName]);//1

            game = Game::instance();
            
            //Add the players
            for (int i = argvIndex::firstPlayerIndex; i < argc; i++){//2
                game->add_player(argv[i]);
            }
			do{
				game = Game::instance();
				int roundcount = roundInfo::firstRound;
				while (game->playerCount() >= roundInfo::minPlayers) {
					roundcount++;
					printMessage("Before round " + to_string(roundcount));
					game->before_round();
					printMessage("Round " + to_string(roundcount));
					game->round();
					printMessage("Round " + to_string(roundcount) + " results");
					int afterRoundReturn = game->after_round();
				}
				cout << "There aren't enough players to play the game." << endl;
				game->stop_game();
			} while (game->playerCount() >= roundInfo::minPlayers);

        }
        catch (errorMsg err) {
            if (err == errorMsg::noCardsLeft) {
                errorMessage = "There were no cards left in the deck to deal to the players.";
                printError(errorMessage);
                game->stop_game();
                return errorMsg::noCardsLeft;
            }
            if (err == errorMsg::notEnoughCards) {
                errorMessage = "There are not enough cards left.";
                printError(errorMessage);
                game->stop_game();
                return errorMsg::noCardsLeft;
            }
			printError(to_string(err));
            game->stop_game();
            return (int)err;
        }
        catch (string err) {
			if (err == err_playeralreadyplaying) {
				errorMessage = "Player is already playing.";
				printError(errorMessage);
				return errorMsg::playerAlreadyPlaying;
			}
            if (err == err_unknowngamemsg) {
                printError(err);
                return errorMsg::badGameName;
            }
        }
        catch (int d) {
            string errorMessage;
            if (d == errorMsg::handsNotCorrectSize){
                errorMessage = "The hands were not the correct size. Their rank cannot be determined.";
                printError(errorMessage);
                game->stop_game();
                return errorMsg::handsNotCorrectSize;
            }

            game->stop_game();
            return d;
        }
        catch (...) {
            errorMessage = "Unexpected error";
            usageMsg(argv[argvIndex::programName], errorMessage);
            game->stop_game();
            return errorMsg::unexpectedError;
        }
    }
    return errorMsg::success;
}
