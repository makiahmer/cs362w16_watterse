#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// int smithyfunc(struct gameState* state, int handPos){
	
	// printf("inside smithyfunc\n\n\n\n\n");
	// int i = 0;
	// int currentPlayer = whoseTurn(state);
	 // +3 Cards
      // for (i = 0; i < 5; i++)
	// {
	  // drawCard(currentPlayer, state);
	// }
			
      //discard card from hand
      // discardCard(handPos, currentPlayer, state, 0);
      // return 0;
// }

int main(){
	struct gameState g;
	int i, ret;
	
	  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

	printf ("Starting game.\n");
	
	initializeGame(2, k, 5, &g);
		   
	g.hand[0][0] = smithy;
	
	assert(g.handCount[0] == 5);
	smithyfunc(&g, 0);

	assert(g.handCount[0] == 9);
	printf ("smithyfunc works \n");
	return 0;
}