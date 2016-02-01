#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//////////////////////////////////////////
// This program tests the function handCard().
// This function takes in a game state and hand position 
// and returns the card that's in the current hand possition
// 
// Outline of test: 
//	check player 1 hand before, check player 2 hand before
//	check card in player 1 hand, check card in player 2 hand
//	player 2 draw a single card
//	check player 1 hand after, check player 2 hand after
//	check card in player 1 hand, check card in player 2 hand
//	set hands and decks to 0
//	check player 1 hand after, check player 2 hand after
//	check card in player 1 hand, check card in player 2 hand


int main(){
	
	struct gameState G;
	int k[10] = {great_hall, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(2, k, 1, &G);
	G.handCount[0] = 5;
	G.handCount[1] = 5;
	int i;
	
	printf("######################################################f2\n");	
	
	printf("Testing numHandCards() functionality.\n");
	
	printf("Before tests:\n");
	printf("   Player hand: ");
	for(i = 0; i < numHandCards(&G); i++){
		printf("%d ",G.hand[G.whoseTurn][i]);
	}
	printf("\n   Player hand location 1: %d\n", handCard(0, &G));
	G.whoseTurn = 1;
	printf("   Player2 hand: ");
	for(i = 0; i < numHandCards(&G); i++){
		printf("%d ",G.hand[G.whoseTurn][i]);
	}
	printf("\n   Player2 hand location 1: %d\n", handCard(0, &G));
	
	drawCard(G.whoseTurn, &G);
	
	G.whoseTurn = 0;
	printf("After test 1: Player 2 draws a card.\n");
	printf("   Player hand: ");
	for(i = 0; i < numHandCards(&G); i++){
		printf("%d ",G.hand[G.whoseTurn][i]);
	}
	printf("\n   Player hand location 6: %d\n", handCard(5, &G));
	G.whoseTurn = 1;
	printf("   Player2 hand: ");
	for(i = 0; i < numHandCards(&G); i++){
		printf("%d ",G.hand[G.whoseTurn][i]);
	}
	printf("\n   Player2 hand location 6: %d\n", handCard(5, &G));
	
	//deck initialization might be bugged. G.deckCount[player] was returning a number while in
	//a for loop then a different number while outside of the for loop. My speculation is that
	//there is an issue with draw card that some times keeps the deck count the same.

	for(i = 0; i < 2; i++){
		while(0 != G.deckCount[i]){
			drawCard(i, &G);
		}
		while(0 != numHandCards(&G)){
			discardCard(0, i, &G, 1);
		}
		G.whoseTurn = i;
	}
	
	printf("After test 2: bad values in hand and deck count.\n");
	G.whoseTurn = 0;
	printf("   Player hand: ");
	for(i = 0; i < numHandCards(&G); i++){
		printf("%d ",G.hand[G.whoseTurn][i]);
	}
	printf("\n   Player hand location 6: %d\n", handCard(5, &G));
	G.whoseTurn = 1;
	printf("   Player2 hand: ");
	for(i = 0; i < numHandCards(&G); i++){
		printf("%d ",G.hand[G.whoseTurn][i]);
	}
	printf("\n   Player2 hand location 6: %d\n", handCard(5, &G));
	printf("\n");
	printf("----------------------------------------------------------------\n");
	printf("\n");

	return 0;
}