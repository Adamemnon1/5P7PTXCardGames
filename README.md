# 5P7PTXCardGames
Code for 5 Card Stud, 7 Card Stud, and Texas Hold 'em poker games.

Five Card Draw and Seven Card Stud



========================================================

========================================================

Adam Sandor

Brian Lam

Carlie Abraham

========================================================

Summary

========================================================


This program extends our Game class to implement Five Card

Draw and Seven Card Stud. It also adds the ability for players

to add bets in a round, and associates a number of chips

with each player. 

========================================================

Test Cases

========================================================


$    Lab4.exe FiveCardDraw Brian Carlie



The program runs Five Card Draw with two players (Brian and Carlie). The

game stops and the error level is 0 if a player leaves and there aren't

enough players int he game.



$    Lab4.exe Goats Brian Carlie

The program throws an error "Unknown Game" and sets the error level to

68.



$   Lab4.exe SevenCardStud Adam Brian Carlie Adam

The program returns an error message because Adam is listed twice as a player. Error level is 

set to 69.



$    Lab4.exe FiveCardDraw Adam Brian Carlie David Emma Fred George Harry Ivan Jack Karly Larry

The program throws an error that there aren't enough cards left in the deck (because there are 

12 players and a standard deck cannot hold enough cards to give each of them a hand). Error level 

is set to 455.



$    Lab4.exe FiveCardDraw Obama

The program throws an error message that there weren't enough arguments passed in and 

displays the usage message. Error level is set to 1. 



$   Lab4.exe SevenCardStud Adam Brian Carlie

 The program starts a game of Seven Card Stud with Adam, Brian, and Carlie as the 

players. Error level is set to 0.
