/*********************************************************************
** Filename		:	cardtest3.c
** File Location:	dominion/assign2/
** Author		:	Makiah Merritt
** Created		:	01/29/2016
** Formatting	:	Consolas 10pt with tabs sized at 4 spaces
** Description	:	A unit test for the great hall card effect implemented
**				:	in dominion.c
** Input		:	N/A
** Output		:	N/A
*********************************************************************/
/*/------------------------------------------------------------------
// ORIGINAL FUNCTION
//-------------------------------------------------------------------
Great Hall (via Wiki) - This is both an Action card and a Victory card. 
When you play it, you draw a card and may play another Action.

case great_hall:
	//+1 Card
	drawCard(currentPlayer, state);

	//+1 Actions
	state->numActions++;

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);
	return 0;
*/
//-------------------------------------------------------------------
//INCLUDES & NAMESPACE(S)
//-------------------------------------------------------------------
#include <stdio.h>						//C standard i/o library
#include <string.h>
#include <assert.h>
#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"
#define VERBOSE 0

int f_Assert(int test, char* message) {
	if (!test) {
		printf("FAILED \n");
		if (VERBOSE) printf("\n %s", message);
		return 0;
	}
	printf("SUCESS \n");
	return 1;
}


//-------------------------------------------------------------------
//TEST
//-------------------------------------------------------------------
int testCardEffect_GreatHall(int player, int testCard, int testCardPos, struct gameState *game) {
	int testChoice1 = -1, testChoice2 = -1, testChoice3 = -1, testBonus = 0; // Vars passed to cardEffect
	int prevValue = 0, prevValue2 = 0/*, success = 1*/, allPass = 1;
	int oriPlayer = 0;

	// Store Original Values
	oriPlayer = game->whoseTurn;

	/* After playing smithy player should have 3 new cards and smithy should be in their played cards pile */
	prevValue = game->handCount[player];
	prevValue2 = game->numActions;
	cardEffect(testCard, testChoice1, testChoice2, testChoice3, game, testCardPos, &testBonus);
	//assert(game->handCount[player] == (prevValue));				// 1 new cards - 1 great hall card = 0 card difference
	printf("Part 1...");
	if (allPass) {
		allPass = f_Assert((game->handCount[player] == (prevValue)), "");
	}
	else {
		f_Assert((game->handCount[player] == (prevValue)), "");
	}

	//assert(game->numActions == (prevValue2 + 1));				// 1 new action
	printf("Part 2...");
	if (allPass) {
		allPass = f_Assert((game->numActions == (prevValue2 + 1)), "");
	}
	else {
		f_Assert((game->numActions == (prevValue2 + 1)), "");
	}

	//assert(game->playedCards[game->playedCardCount - 1] == testCard);	// Smithy was the last card discarded
	printf("Part 3...");
	if (allPass) {
		allPass = f_Assert((game->playedCards[game->playedCardCount - 1] == testCard), "");
	}
	else {
		f_Assert((game->playedCards[game->playedCardCount - 1] == testCard), "");
	}

	// Restore original values
	game->whoseTurn = oriPlayer;

	// If all tests passed success = 1
	if (allPass) { printf("Unit test was successfully completed.\n"); }

	return allPass;
}

//-------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------
int main() {
	// DECLARATIONS & INITIALIZATIONS
	/* Loop Counters */
	int i = 0;
	int testCount = 10, testSuccess = 0, testCard = 0, testCardPos = 0;

	/* Game Variables */
	int player = 0, playerCount = 2;
	int kingdomCards[10] = { adventurer, council_room, feast,
		gardens, mine, remodel, smithy, village, baron,
		great_hall };
	struct gameState game;

	/* Setup random seeds */
	int randSeed = 71;
	SelectStream(2);
	PutSeed(3);


	// PROCESS
	player = 0;
	testCard = great_hall;
	testCardPos = 0;
	for (i = 0; i < testCount; i++) {							// Run desired number of tests
		printf("---- STARTING CARD TEST 3 [%d of %d] ---- \n", i + 1, testCount);
		initializeGame(playerCount, kingdomCards, randSeed, &game);		// Initialize a new game
		game.hand[player][0] = testCard;
		testSuccess = testCardEffect_GreatHall(player, testCard, testCardPos, &game);
		printf("---- //END// CARD TEST 3 [%d of %d] ---- \n\n\n", i + 1, testCount);
	}


	// CLEAN-UP AND EXIT
	return 0;
}