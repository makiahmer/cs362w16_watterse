#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//////////////////////////////////////////
// This program tests the card Council Room.
// 
// The physical card stipulates:
//	When played:
//	+4 card draw
//	+1 card buy	
//	+1 card draw for each other player
//

int main(){
	
	struct gameState G;
	int k[10] = {council_room, smithy, great_hall, gardens, embargo, minion, mine, cutpurse, sea_hag, tribute};
	initializeGame(2, k, 1, &G);
	int player = G.whoseTurn;
	int player2;
	
	if(player == 0)
		player2 = 1;
	else
		player2 = 0;
	
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
	
	printf("######################################################c4\n");
	
	printf("Testing Smithy card functionality.\n");
	printf("Before tests:\n");
	printf("   Player hand count: %d\n", G.handCount[player]);
	printf("   Second player hand Count: %d\n", G.handCount[player2]);
	printf("   Player buy count: %d\n", G.numBuys);
	printf("   Player deck Count: %d\n", G.deckCount[player]);
	printf("   player discard Count: %d\n", G.discardCount[player]);
	
	cardEffect(council_room, 1, 1, 1, &G, 0, 0);
	
	printf("After test 1: cards in hand and cards in deck\n");
	printf("   Player hand count: %d\n", G.handCount[player]);
	printf("   Second player hand Count: %d\n", G.handCount[player2]);
	printf("   Player buy count: %d\n", G.numBuys);
	printf("   Player deck Count: %d\n", G.deckCount[player]);
	printf("   player discard Count: %d\n", G.discardCount[player]);
	
	//deck initialization might be bugged. G.deckCount[player] was returning a number while in
	//a for loop then a different number while outside of the for loop. My speculation is that
	//there is an issue with draw card that some times keeps the deck count the same.
	while(0 != G.deckCount[player] && 0 != G.deckCount[player2]){
			drawCard(G.whoseTurn, &G);
			drawCard(player2, &G);
	}
	G.handCount[player] = 1;
	G.handCount[player2] = -1; //Odd... Won't initialize at 0
	cardEffect(council_room, -1, -1, -1, &G, 0, 0);
	
	printf("After test 2: no cards in hand and no cards in deck\n");
	printf("   Player hand count: %d\n", G.handCount[player]);
	printf("   Second player hand Count: %d\n", G.handCount[player2]);
	printf("   Player Buy count: %d\n", G.numBuys);
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
	printf("   Number of Actions: %d\n", G.numActions); 
	printf("   Number of cards played: %d\n", G.playedCardCount);
	printf("\n");
	printf("----------------------------------------------------------------\n");
	printf("\n");
	return 0;
}
