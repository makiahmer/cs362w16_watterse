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
	g.deckCount[0] = 5;
	g.handCount[0] = 5;
	g.discardCount[0] = 5;
	
	int c[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};
	

	// put only smith in the deck
	for (i = 0; i < g.deckCount[0]; i++){
		g.deck[0][i] = c[9];
	}
	
	//put card in direct relation to c[] indexes
	for ( i = 0; i < g.handCount[0]; i++){
		g.hand[0][i] = c[i];
	}
	
	for ( i = 0; i < g.discardCount[0]; i++){
		g.discard[0][i] = c[i];
	}
	
	
	ret = fullDeckCount(0,smithy, &g);
	printf (" ret is %d \n",ret);
	assert(ret == 5);
	printf (" fullDeck Count works \n");
	return 0;
}