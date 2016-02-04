/*********************************************************************
** Filename		:	unittest2.c
** File Location:	dominion/assign2/
** Author		:	Makiah Merritt
** Created		:	01/29/2016
** Formatting	:	Consolas 10pt with tabs sized at 4 spaces
** Description	:	A unit test for the updateCoins function implemented
**				:	in dominion.c
** Input		:	N/A
** Output		:	N/A
*********************************************************************/
/*/------------------------------------------------------------------
// ORIGINAL FUNCTION
//-------------------------------------------------------------------
int updateCoins(int player, struct gameState *state, int bonus)
{
	int i;

	//reset coin count
	state->coins = 0;

	//add coins for each Treasure card in player's hand
	for (i = 0; i < state->handCount[player]; i++)
	{
		if (state->hand[player][i] == copper)
		{
			state->coins += 1;
		}
		else if (state->hand[player][i] == silver)
		{
			state->coins += 2;
		}
		else if (state->hand[player][i] == gold)
		{
			state->coins += 3;
		}
	}

	//add bonus
	state->coins += bonus;

	return 0;
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
int testUpdateCoins(struct gameState *game, int player) {
	int coinBonus = 0, expectedTotal = 0, i, j;							// Loop counters
	int /*, success = 1*/allPass = 1;

	/* Store Original Values */
	int prevValue = game->coins;
	int* oriHand = game->hand[player];
	int* testHand = game->hand[player];

	/* Run Test */
	for (i = 4; i < 7; i++) {									// pass treasure cards to update coins
		expectedTotal = coinBonus;								// Reset total
		
		for (j = 0; j < game->handCount[player]; j++) {
			testHand[j] = i;
			expectedTotal += (i - 3);
		}
		
		updateCoins(player, game, coinBonus);
		//assert(game->coins == expectedTotal);
		printf("Part 1...");
		if (allPass) {
			allPass = f_Assert((game->coins == expectedTotal), "");
		}
		else {
			f_Assert((game->coins == expectedTotal), "");
		}
		coinBonus++;
	}

	/* Restore Original Values */
	for (j = 0; j < game->handCount[player]; j++) {
		game->hand[player][j] = oriHand[j];
	}
	game->coins = prevValue;

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
		printf("---- STARTING UNIT TEST 2 [%d of %d] ---- \n", i + 1, testCount);
		initializeGame(playerCount, kingdomCards, randSeed, &game);		// Initialize a new game
		testSuccess = testUpdateCoins(&game, player);
		printf("---- //END// UNIT TEST 2 [%d of %d] ---- \n\n\n", i + 1, testCount);
	}

	// CLEAN-UP AND EXIT
	return 0;
}