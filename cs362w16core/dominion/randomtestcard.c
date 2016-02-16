//##################################################
//#  This program tests the dominion card Great Hall
//#

//##	TO RUN THIS PROGRAM WITH THE CURRENT MAKEFILE:
//##	Type into the terminal: make runRandomCard

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TESTS 10000

int runActionTest(struct gameState G){
	int player = G.whoseTurn;
	
	int k[10] = {great_hall, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(2, k, 1, &G);
	
	G.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
	
	int deckZero = rand() % 10;
	if(deckZero == 0){
		G.deckCount[player] = 0;
	}
	else if(deckZero == 10){
		G.deckCount[player] = MAX_DECK;
	}
	
	//make the deck random
	int tempDeckCount = G.deckCount[player];
	int t;
	for(t = 0; t < tempDeckCount; t++){
		G.deck[player][t] = rand() % treasure_map;
	}
	
	G.handCount[player] = rand() % MAX_HAND;
	
	int tempActionCount = G.numActions;
	
	int i;
	//attempt to run the cards multiple times
	for(i = 0; i < 10; i++){
		tempActionCount++;
		int check = cardEffect(great_hall, 1, 1, 1, &G, 0, 0);
		//check if a cardEffect didn't work correctly
		if(check == -1){
			return 1;
		}
		else if(G.numActions != tempActionCount){
			return 2; // if the action count isn't equal to what it should be, report back.
		}
	}
	
	return 0;
}

int runDiscardTest(struct gameState G){
	//Initialize game state
	int player = G.whoseTurn;
	
	int k[10] = {great_hall, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(2, k, 1, &G);
	
	G.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
	
	int deckZero = rand() % 10;
	if(deckZero == 0){
		G.deckCount[player] = 0;
	}
	else if(deckZero == 10){
		G.deckCount[player] = MAX_DECK;
	}
	
	int tempDeckCount = G.deckCount[player];
	int t;
	
	//make the deck random
	for(t = 0; t < tempDeckCount; t++){
		G.deck[player][t] = rand() % treasure_map;
	}
	
	G.handCount[player] = rand() % MAX_HAND;
	
	int tempDiscard = G.discardCount[player];
	int discardedCards = 0;
	
	int check;
	int i;
	//attempt to run the cards multiple times
	for(i = 0; i < 10; i++){
		discardedCards++;
		check = cardEffect(great_hall, 1, 1, 1, &G, 0, 0);
		//check if a cardEffect didn't work correctly
		if(check == -1){
			return 1;
		}
		else if(discardedCards + tempDiscard != G.discardCount[player]){
			return 3; // if the discard pile has too many or too few report back
		}
		else if(G.deckCount[player] + discardedCards != tempDeckCount){
			return 4; // if the deck count and the discard count is off report back
		}
	}
	
	return 0;
}

int runHandTest(struct gameState G){
	int player = G.whoseTurn;
	
	int k[10] = {great_hall, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(2, k, 1, &G);
	
	G.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
	
	int deckZero = rand() % 10;
	if(deckZero == 0){
		G.deckCount[player] = 0;
	}
	else if(deckZero == 10){
		G.deckCount[player] = MAX_DECK;
	}
	
	//make the dec random
	int tempDeckCount = G.deckCount[player];
	int t;
	for(t = 0; t < tempDeckCount; t++){
		G.deck[player][t] = rand() % treasure_map;
	}
	
	G.handCount[player] = rand() % MAX_HAND;
	int tempHandCount = G.handCount[player];
	
	int check;
	int i;
	//attempt to run the cards multiple times
	for(i = 0; i < 10; i++){
		tempDeckCount--;
		check = cardEffect(great_hall, 1, 1, 1, &G, 0, 0);
		//check if a cardEffect didn't work correctly
		if(check == -1){
			return 1;
		}
		else if(tempHandCount != G.handCount[player]){ //check hand count to see if it drew properly 
			return 5; // if the hand count doesnt increment by 1 report back
		}
		else if(tempDeckCount != G.deckCount[player]){
			return 6; // if the deck doesn't decriment by 1 report back
		}
	}
	
	return 0;
}

int main(){
	srand(time(NULL));	
	int i;
	int temp = 0;
	int printFailure[7];
	
	for(i = 0; i < 7; i++){
		printFailure[i] = 0;
	}
	
	for(i = 0; i < MAX_TESTS; i++){
		struct gameState G;
		temp = runHandTest(G);
		printFailure[temp] = printFailure[temp] + 1;
		temp = runDiscardTest(G);
		printFailure[temp] = printFailure[temp] + 1;
		temp = runActionTest(G);
		printFailure[temp] = printFailure[temp] + 1;
	}
	printf("\n------------------------------------------------------\n\n");
	printf("Testing Great Hall dominion card\n");
	printf("results in number of times the problem occured: \n\n");
	
	printf("CardEffect() returned -1: %d\n", printFailure[1]);
	printf("The player doesn't contain the right number of actions: %d\n", printFailure[2]);
	printf("The discard pile doesn't have the correct number of cards in it: %d\n", printFailure[3]);
	printf("The sum between deck and discard isn't correct: %d\n", printFailure[4]);
	printf("The hand count did not increment by 1: %d\n", printFailure[5]);
	printf("The deck count did not decriment by 1: %d\n", printFailure[6]);
	printf("\n");
	return 0;
}
