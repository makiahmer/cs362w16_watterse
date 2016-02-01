#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//////////////////////////////////////////
// This program tests the function numHandCards.
// This function takes in a game state and returns
// the hand count of the current player.
// 
// Outline of test: 
//	check player 1 hand before, check player 2 hand before
//	player 1 draw a single card
//	check player 1 hand after, check player 2 hand after
//	set hands and decks to 0
//	check player 1 hand after, check player 2 hand after


int main(){
	
	struct gameState G;
	int k[10] = {great_hall, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(2, k, 1, &G);
	G.handCount[0] = 5;
	G.handCount[1] = 5;
	
	printf("######################################################f1\n");
	
	printf("Testing numHandCards() functionality.\n");
	printf("Before tests:\n");
	printf("   Player hand count: %d\n", numHandCards(&G));
	G.whoseTurn = 1;
	printf("   Player2 hand count: %d\n", numHandCards(&G));
	drawCard(G.whoseTurn, &G);
	G.whoseTurn = 0;
	printf("After test 1: player2 draws a card\n");
	printf("   Player hand count: %d\n", numHandCards(&G));
	G.whoseTurn = 1;
	printf("   Player2 hand count: %d\n", numHandCards(&G));
	
	//deck initialization might be bugged. G.deckCount[player] was returning a number while in
	//a for loop then a different number while outside of the for loop. My speculation is that
	//there is an issue with draw card that some times keeps the deck count the same.
	int i;
	for(i = 0; i < 2; i++){
		while(0 != G.deckCount[i]){
			drawCard(i, &G);
		}
		G.handCount[i] = 0;
	}
	G.whoseTurn = 0;
	printf("After test 2: no cards in hand and no cards in deck\n");
	printf("   Player hand count: %d\n", numHandCards(&G));
	G.whoseTurn = 1;
	printf("   Player2 hand count: %d\n", numHandCards(&G));	
	printf("\n");
	printf("----------------------------------------------------------------\n");
	printf("\n");

	return 0;
}