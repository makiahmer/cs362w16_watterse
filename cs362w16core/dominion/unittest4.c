#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//////////////////////////////////////////
// This program tests the function kingdomCards.
// This function takes in a game state returns 
// the who the current player is.
//
// Outline:
//	initialize game with kingdomCards() function.
//  print out intended list of cards
//	print out list of saved cards
//	run kingdomCards() with new set.
//	print out intended list of cards
//	print out list of saved cards.
//

int main(){
	
	struct gameState G;
	int *k  = kingdomCards(gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall);
	initializeGame(2, k, 1, &G);
	int i;
	
	int g[10] = {gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall};
	printf("######################################################f4\n");	
	
	printf("Testing kingdomCards() functionality.\n");
	printf("Before test:\n");
	printf("   Intended list of cards: %d %d %d %d %d %d %d %d %d %d\n", gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall);
	printf("   Saved list of cards:    ");
	for(i = 0; i < 10; i++){
		printf("%d ", k[i]);
	}
	for(i = 0; i < 10; i++){
		if(g[i] != k[i])
			printf("Bug!: at location %d, %d != %d", i, g[i], k[i]);
	}
	k = kingdomCards(great_hall, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy);
	int h[10] = {great_hall, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	printf("\nAfter test 1: rerun function with a new list.\n");
	printf("   Intended list of cards: %d %d %d %d %d %d %d %d %d %d\n", great_hall, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy);
	printf("   Saved list of cards:    ");
	for(i = 0; i < 10; i++){
		printf("%d ", k[i]);
	}
	for(i = 0; i < 10; i++){
		if(h[i] != k[i])
			printf("Bug!: at location %d, %d != %d", i, h[i], k[i]);
	}
	printf("\n");
	printf("----------------------------------------------------------------\n");
	printf("\n");

	return 0;
}