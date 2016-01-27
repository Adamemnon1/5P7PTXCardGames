#ifndef __MAINH__
#define __MAINH__
#include <string>

using namespace std;

enum argvIndex {
    programName = 0,
    gameName = 1,
    minNumOfArguments = 4,
    firstPlayerIndex = 2,
};
enum roundInfo {
    firstRound = 0,
    minPlayers = 2,
};

string err_unknowngamemsg = "Unknown game";

#endif
