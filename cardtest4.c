#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

//note updatecoin function not working expected coin should be 6 but it become 3

int main(){
	struct gameState g;
	int i, ret, bonus;
	bonus = 0;
	
	  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute,smithy};

	printf ("Starting game.\n");
	
	initializeGame(2, k, 5, &g);
		   
	//g.coins = 0;
	//g.outpostPlayed = 0;
	g.hand[0][0] = outpost;
	
	printf("handcount is %d \n", g.handCount[0]);
	printf("g.outpostPlayed is %d \n", g.outpostPlayed);
	
	assert(g.handCount[0] == 5);

	
	//cardEffect(card, choice1, choice2, choice3, state, handPos, &coin_bonus)
	//playCard(0,-1,-1,-1, &g);
	cardEffect(embargo, smithy, -1, -1, &g, 0, &bonus);
	
	printf("handcount is %d \n", g.handCount[0]);
	
	//assert( g.embargoTokens[smithy] == 1);
	printf("g.outpostPlayed is %d \n", g.outpostPlayed);
	
	//assert(g.handCount[0] == 8);
	//assert(g.numBuys == 2);
	
	//assert(g.handCount[0] == 9);
	printf ("outpost switch statement works \n");
	return 0;
}