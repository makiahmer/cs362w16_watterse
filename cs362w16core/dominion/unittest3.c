#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//////////////////////////////////////////
// This program tests the function whoseTurn.
// This function takes in a game state returns 
// the who the current player is.
// 
// Outline of test: 
//	Initialize game state
//	check which players turn it is.
//	end turn
//	check which players turn it is.
//

int main(){
	
	struct gameState G;
	int k[10] = {great_hall, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(2, k, 1, &G);

	printf("######################################################f3\n");	
	
	printf("Testing whoseTurn() functionality.\n");
	printf("Before test:\n");
	printf("   whoseTurn function call: %d\n", whoseTurn(&G));
	printf("   Direct variable from gamestate: %d\n", G.whoseTurn);
	endTurn(&G);
	
	printf("After test 1: Ended the turn\n");
	printf("   whoseTurn function call: %d\n", whoseTurn(&G));
	printf("   Direct variable from gamestate: %d\n", G.whoseTurn);
	printf("\n");
	printf("----------------------------------------------------------------\n");
	printf("\n");

	return 0;
}