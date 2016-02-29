#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


int main(){
	struct gameState g;
	int i, ret;
	
	  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute,council_room};

	printf ("Starting game.\n");
	
	initializeGame(2, k, 5, &g);
		   
	g.hand[0][0] = council_room;
	
	printf("handcount is %d \n", g.handCount[0]);
	printf("numBuy is %d \n", g.numBuys);
	
	assert(g.handCount[0] == 5);
	assert(g.numBuys == 1);
	
	councilfunc(&g, 0);
	
	printf("handcount is %d \n", g.handCount[0]);
	printf("numBuy is %d \n", g.numBuys);
	
	assert(g.handCount[0] == 8);
	assert(g.numBuys == 2);
	
	//assert(g.handCount[0] == 9);
	printf ("councilfunc works \n");
	return 0;
}