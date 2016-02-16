//##################################################
//##  This program tests the dominion card Adventurer
//##

//##	TO RUN THIS PROGRAM WITH THE CURRENT MAKEFILE:
//##	Type into the terminal: make runAdventurer


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

int runDiscardTest(struct gameState G){
	
	//set game state and random variables.
	int player = G.whoseTurn;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
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
	
	int tempDiscard = G.discardCount[player];
	int discardedCards = 0;
	
	int check;
	int i;
	
	//attempt to run the cards multiple times
	for(i = 0; i < 10; i++){
		check = cardEffect(adventurer, 1, 1, 1, &G, 0, 0);
		
		//check if a cardEffect didn't work correctly
		if(check == -1){
			return 1;
		}
		int u;
		int currencyCount = 0;
		//find how many currency cards have been discarded.
		for(u = tempDiscard; u < G.discardCount[player]; u++){
			discardedCards++;
			if(G.discard[player][u] == gold || G.hand[player][u] == silver || G.hand[player][u] == copper){
				currencyCount++;
			}
		}
		if(currencyCount > 0){ //if we have any that have been discarded, a bug
			return 5;
		}
		if(2 + G.deckCount[player] + discardedCards != tempDeckCount){ // if we have an off number of cards, a bug
			return 6;
		}
	}
	
	return 0;
}

int runHandTest(struct gameState G){
	int player = G.whoseTurn;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
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
	int tempHandCount = G.handCount[player];
	
	int check;
	int i;
	//attempt to run the cards multiple times
	for(i = 0; i < 10; i++){
		check = cardEffect(adventurer, 1, 1, 1, &G, 0, 0);
		//check if a cardEffect didn't work correctly
		if(check == -1){
			return 1;
		}
		if(G.hand[player][G.handCount[player]-1] != copper && G.hand[player][G.handCount[player]-1] != silver && G.hand[player][G.handCount[player]-1] != gold){
			if(G.deckCount[player] != 0){
				return 2;
			}
		}
		int u;
		int currencyCount = 0;
		//find how many currency cards have been drawn
		for(u = tempHandCount; u < MAX_HAND; u++){
			if(G.hand[player][u] == gold || G.hand[player][u] == silver || G.hand[player][u] == copper){
				currencyCount++;
			}
		}
		if(currencyCount < 2 && G.deckCount[player] != 0){ // if there aren't enough currency cards in hand and there are cards in the deck, a bug
			return 3;
		}
		if(currencyCount > 2){ // if there are too many currency cards, a bug
			return 4;
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
	}
	printf("\n------------------------------------------------------\n\n");
	printf("Testing adventurer dominion card\n");
	printf("results in number of times the problem occured: \n\n");
	
	printf("CardEffect() returned -1: %d\n", printFailure[1]);
	printf("Last card drawn in players hand isn't a currency card and there are cards left in deck: %d\n", printFailure[2]);
	printf("There are less than two currency cards in the drawn cards and there are cards left in deck: %d\n", printFailure[3]);
	printf("There are more than 2 currency cards in the drawn cards: %d\n", printFailure[4]);
	printf("CardEffect() discarded at least 1 currency card: %d\n", printFailure[5]);
	printf("The sum of all cards interacted with do not total what was originally in the deck: %d\n\n", printFailure[6]);
	return 0;
}
