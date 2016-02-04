/*********************************************************************
** Filename		:	unittest3.c
** File Location:	dominion/assign2/
** Author		:	Makiah Merritt
** Created		:	01/29/2016
** Formatting	:	Consolas 10pt with tabs sized at 4 spaces
** Description	:	A unit test for the fullDeckCount function implemented
**				:	in dominion.c
** Input		:	N/A
** Output		:	N/A
*********************************************************************/
/*/------------------------------------------------------------------
// ORIGINAL FUNCTION
//-------------------------------------------------------------------
int fullDeckCount(int player, int card, struct gameState *state) {
	int i;
	int count = 0;

	for (i = 0; i < state->deckCount[player]; i++)
	{
		if (state->deck[player][i] == card) count++;
	}

	for (i = 0; i < state->handCount[player]; i++)
	{
		if (state->hand[player][i] == card) count++;
	}

	for (i = 0; i < state->discardCount[player]; i++)
	{
		if (state->discard[player][i] == card) count++;
	}

	return count;
}

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
int testFullDeckCount(struct gameState *game, int player) {
	// DECLARATIONS & INITALIZATIONS
	int i, j;													// Loop counters
	int testCard;
	int /*, success = 1*/allPass = 1, expectedResult = 0, functionResult = 0;	// Result handlers
	int oriDeck[MAX_DECK], oriHand[MAX_HAND], oriDiscard[MAX_DECK];				// Value recovery

	// Store Original Values
	for (i = 0; i < game->deckCount[player]; i++) { 
		oriDeck[i] = game->deck[player][i];
	}
	for (i = 0; i < game->handCount[player]; i++) { 
		oriHand[i] = game->hand[player][i];
	}
	for (i = 0; i < game->discardCount[player]; i++) {
		oriDiscard[i] = game->discard[player][i];
	}

	// PROCESS
	/* Test 1 - Invalid Cards */
	testCard = -1;
	expectedResult = 0;
	functionResult = fullDeckCount(player, testCard, game);
	//assert(expectedResult == functionResult);
	printf("Part 1...");
	if (allPass) {
		allPass = f_Assert((expectedResult == functionResult), "");
	}
	else {
		f_Assert((expectedResult == functionResult), "");
	}

	testCard = 27;
	expectedResult = 0;
	functionResult = fullDeckCount(player, testCard, game);
	//assert(expectedResult == functionResult);
	printf("Part 2...");
	if (allPass) {
		allPass = f_Assert((expectedResult == functionResult), "");
	}
	else {
		f_Assert((expectedResult == functionResult), "");
	}

	/* Test 2 - Expected results for given cards*/
	for (i = 0; i < 27; i++) {									// Cards range from 0-curse to 26-treasure_map
		// Resets
		testCard = expectedResult = 0;
																
		// Modify player deck
		for (j = 0; j < game->deckCount[player]; j++) { game->deck[player][j] = i; expectedResult++; }

		// Modify player hand
		for (j = 0; j < game->handCount[player]; j++) { game->hand[player][j] = i; expectedResult++; }

		// Modify player discard
		for (j = 0; j < game->discardCount[player]; j++) { game->discard[player][j] = i; expectedResult++; }
		if ((game->discard[player][0] > 26) || (game->discard[player][0] < 0)) {
			game->discard[player][0] = 0;
			if (i == 0) { expectedResult++; }
		}
		if (game->discardCount[player] < MAX_DECK) {			// Handle anticipated circumstance where discard is already full (FOR SOME ODD REASON!)
			game->discard[player][game->discardCount[player] + 1] = i;
			game->discard[player][game->discardCount[player] + 2] = i - 1;
			game->discardCount[player] += 3;
		}
		else {
			game->discard[player][game->discardCount[player] - 2] = i;
			game->discard[player][game->discardCount[player] - 3] = i - 1;
		}
		expectedResult++;

		// Test against current card
		testCard = i;
		functionResult = fullDeckCount(player, testCard, game);
		//assert(expectedResult == functionResult);
		printf("Part 3...");
		if (allPass) {
			allPass = f_Assert((expectedResult == functionResult), "");
		}
		else {
			f_Assert((expectedResult == functionResult), "");
		}

		// Test against a different card
		testCard = i - 1;
		expectedResult = 1;										// Should be 1 because of a card in discard
		functionResult = fullDeckCount(player, testCard, game);
		//assert(expectedResult == functionResult);
		printf("Part 4...");
		if (allPass) {
			allPass = f_Assert((expectedResult == functionResult), "");
		}
		else {
			f_Assert((expectedResult == functionResult), "");
		}
	}

	// Restore original values
	for (i = 0; i < game->deckCount[player]; i++) { game->deck[player][i] = oriDeck[i]; }
	for (i = 0; i < game->handCount[player]; i++) { game->hand[player][i] = oriHand[i]; }
	for (i = 0; i < game->discardCount[player]; i++) { game->discard[player][i] = oriDiscard[i]; }

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
	int testCount = 10, testSuccess = 0;

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
	for (i = 0; i < testCount; i++) {							// Run desired number of tests
		printf("---- STARTING UNIT TEST 3 [%d of %d] ---- \n", i + 1, testCount);
		initializeGame(playerCount, kingdomCards, randSeed, &game);		// Initialize a new game
		testSuccess = testFullDeckCount(&game, player);
		printf("---- //END// CARD TEST 3 [%d of %d] ---- \n\n\n", i + 1, testCount);
	}

	// CLEAN-UP AND EXIT
	return 0;
}