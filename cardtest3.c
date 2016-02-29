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
	g.embargoTokens[smithy] = 0;
	g.hand[0][0] = embargo;
	
	printf("handcount is %d \n", g.handCount[0]);
	printf("coin is %d \n", g.coins);
	
	assert(g.handCount[0] == 5);
	assert(g.coins == 4);
	
	//cardEffect(card, choice1, choice2, choice3, state, handPos, &coin_bonus)
	playCard(0,smithy,-1,-1, &g);
	//cardeffect(embargo, smithy, -1, -1, &g, 0, &bonus);
	
	printf("handcount is %d \n", g.handCount[0]);
	printf("coin is %d \n", g.coins);
	
	assert( g.embargoTokens[smithy] == 1);
	printf("g.embargoTokens[smithy] is : %d \n", g.embargoTokens[smithy]);
	
	//assert(g.handCount[0] == 8);
	//assert(g.numBuys == 2);
	
	//assert(g.handCount[0] == 9);
	printf ("embargo switch statement works \n");
	return 0;
}