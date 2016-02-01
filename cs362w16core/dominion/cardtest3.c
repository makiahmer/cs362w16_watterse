#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//////////////////////////////////////////
// This program tests the card Village.
// 
// The physical card stipulates:
//	When played:
//	+2 card action
//	+1 card draw
//

int main(){
	
	struct gameState G;
	int k[10] = {village, smithy, great_hall, gardens, embargo, minion, mine, cutpurse, sea_hag, tribute};
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
	
	printf("######################################################c3\n");
	
	printf("Testing Smithy card functionality.\n");
	printf("Before tests:\n");
	printf("   Player hand count: %d\n", G.handCount[player]);
	printf("   Player action count: %d\n", G.numActions);
	printf("   Player deck Count: %d\n", G.deckCount[player]);
	printf("   player discard Count: %d\n", G.discardCount[player]);
	
	cardEffect(village, 1, 1, 1, &G, 0, 0);
	
	printf("After test 1: cards in hand and cards in deck\n");
	printf("   Player hand count: %d\n", G.handCount[player]);
	printf("   Player action count: %d\n", G.numActions);
	printf("   Player deck Count: %d\n", G.deckCount[player]);
	printf("   player discard Count: %d\n", G.discardCount[player]);
	
	//deck initialization might be bugged. G.deckCount[player] was returning a number while in
	//a for loop then a different number while outside of the for loop. My speculation is that
	//there is an issue with draw card that some times keeps the deck count the same.
	while(0 != G.deckCount[player]){
			drawCard(G.whoseTurn, &G);
	}
	G.handCount[player] = 1;
	cardEffect(village, -1, -1, -1, &G, 0, 0);
	
	printf("After test 2: no cards in hand and no cards in deck\n");
	printf("   Player hand count: %d\n", G.handCount[player]);
	printf("   Player action count: %d\n", G.numActions);
	printf("   Player deck Count: %d\n", G.deckCount[player]);
	printf("   player discard Count: %d\n", G.discardCount[player]);
	printf("After tests: The rest of the game state variables\n");
	printf("   Number of players: %d\n", G.numPlayers); 
	printf("   Supply Counter: %d\n", G.supplyCount[treasure_map+1]);
	printf("   Embargo Tokens: %d\n", G.embargoTokens[treasure_map+1]);
	printf("   Outpost check: %d\n", G.outpostPlayed);
	printf("   Outpost turn: %d\n", G.outpostTurn);
	printf("   Current player: %d\n", G.whoseTurn);
	printf("   Phase check: %d\n",  G.phase);
	printf("   Number of Coins: %d\n", G.coins); 
	printf("   Number of buys: %d\n", G.numBuys); 
	printf("   Number of cards played: %d\n", G.playedCardCount);
	printf("\n");
	printf("----------------------------------------------------------------\n");
	printf("\n");
	return 0;
}
