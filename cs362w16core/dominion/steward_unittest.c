#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//////////////////////////////////////////
// This program tests the card Steward.
// 
//


int main(){
	
	struct gameState G;
	int k[10] = {steward, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(2, k, 1, &G);
	int player = G.whoseTurn;
	G.handCount[player] = 0;
	G.hand[player][0] = k[0];
	
	int i;
	for(i = 0; i < 5; i++){
		if(i < 5)
			gainCard(1, &G, 1, player);
		
		else
			gainCard(i+1, &G, 1, G.whoseTurn);
	}
	
	drawCard(G.whoseTurn, &G);
	
	G.coins = 5;
	G.handCount[G.whoseTurn] = 6;
	int handPos = 1;
	G.hand[G.whoseTurn][handPos] = steward;
	
	//set choice1 to 2 to enact the +2 coins.
	
	printf("coint count: %d\n", G.coins);
	cardEffect(steward, 2, 1, 1, &G, 0, 0);
	
	printf("coin coint should be +2: %d\n", G.coins);
	
	return 0;
}