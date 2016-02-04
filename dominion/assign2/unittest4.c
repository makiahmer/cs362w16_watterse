/*********************************************************************
** Filename		:	unittest4.c
** File Location:	dominion/assign2/
** Author		:	Makiah Merritt
** Created		:	01/29/2016
** Formatting	:	Consolas 10pt with tabs sized at 4 spaces
** Description	:	A unit test for the buyCard function implemented
**				:	in dominion.c
** Input		:	N/A
** Output		:	N/A
*********************************************************************/
/*/------------------------------------------------------------------
// ORIGINAL FUNCTION
//-------------------------------------------------------------------
int buyCard(int supplyPos, struct gameState *state) {
	int who;
	if (DEBUG) {
		printf("Entering buyCard...\n");
	}

	// I don't know what to do about the phase thing.

	who = state->whoseTurn;

	if (state->numBuys < 1) {
		if (DEBUG)
			printf("You do not have any buys left\n");
		return -1;
	}
	else if (supplyCount(supplyPos, state) < 1) {
		if (DEBUG)
			printf("There are not any of that type of card left\n");
		return -1;
	}
	else if (state->coins < getCost(supplyPos)) {
		if (DEBUG)
			printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
		return -1;
	}
	else {
		state->phase = 1;
		//state->supplyCount[supplyPos]--;
		gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)

		state->coins = (state->coins) - (getCost(supplyPos));
		state->numBuys--;
		if (DEBUG)
			printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
	}

	//state->discard[who][state->discardCount[who]] = supplyPos;
	//state->discardCount[who]++;

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
int testBuyCard(struct gameState *game, int player) {
	// DECLARATIONS & INITALIZATIONS
	int i, j;
	int /*, success = 1*/allPass = 1, testCard = 0;
	int oriPlayer = 0, oriNumBuys = 0, prevValue = 0, prevValue2 = 0, prevValue3 = 0;

	// Store original values
	oriPlayer = game->whoseTurn;
	oriNumBuys = game->numBuys;

	// PROCESS
	game->whoseTurn = player;
	game->numBuys = 26;											// We're testing 26 cards

	for (i = 0; i < 27; i++) {
		testCard = i;
		
		// Manipulate numBuys
		prevValue = game->numBuys;
		for (j = -5; j < 1; j++) {
			game->numBuys = j;
			//assert(buyCard(testCard, game) == -1);
			printf("Part 1...");
			if (allPass) {
				allPass = f_Assert((buyCard(testCard, game) == -1), "");
			}
			else {
				f_Assert((buyCard(testCard, game) == -1), "");
			}
		}
		game->numBuys = prevValue;


		// Manipulate supplyCount
		prevValue = game->supplyCount[testCard];
			for (j = -5; j < 1; j++) {
				game->supplyCount[testCard] = j;
				//assert(buyCard(testCard, game) == -1);
				printf("Part 2...");
				if (allPass) {
					allPass = f_Assert((buyCard(testCard, game) == -1), "");
				}
				else {
					f_Assert((buyCard(testCard, game) == -1), "");
				}
			}
		game->supplyCount[testCard] = prevValue;


		// Manipulate player purse
		prevValue = game->coins;
			for (j = -5; j < getCost(testCard); j++) {
				game->coins = j;
				//assert(buyCard(testCard, game) == -1);
				printf("Part 3...");
				if (allPass) {
					allPass = f_Assert((buyCard(testCard, game) == -1), "");
				}
				else {
					f_Assert((buyCard(testCard, game) == -1), "");
				}
			}
		game->coins = prevValue;

		
		// Test a successful purchase
		if ((game->coins >= getCost(testCard)) && (supplyCount(testCard, game) > 1)) {		// Player can buy the test card
			prevValue = fullDeckCount(player, testCard, game);
			prevValue2 = game->coins;
			prevValue3 = game->numBuys;
			//assert(buyCard(testCard, game) == 0);								// A successful purchase returns 0
			printf("Part 4...");
			if (allPass) {
				allPass = f_Assert((buyCard(testCard, game) == 0), "");
			}
			else {
				f_Assert((buyCard(testCard, game) == 0), "");
			}
			//assert(game->phase == 1);											// Make sure players phase is now 1
			printf("Part 5...");
			if (allPass) {
				allPass = f_Assert((game->phase == 1), "");
			}
			else {
				f_Assert((game->phase == 1), "");
			}
			//assert(fullDeckCount(player, testCard, game) == (prevValue + 1));	// Make sure player gained the card
			printf("Part 6...");
			if (allPass) {
				allPass = f_Assert((fullDeckCount(player, testCard, game) == (prevValue + 1)), "");
			}
			else {
				f_Assert((fullDeckCount(player, testCard, game) == (prevValue + 1)), "");
			}
			//assert(game->coins == (prevValue2 - getCost(testCard)));			// Make sure player paid for the card
			printf("Part 7...");
			if (allPass) {
				allPass = f_Assert((game->coins == (prevValue2 - getCost(testCard))), "");
			}
			else {
				f_Assert((game->coins == (prevValue2 - getCost(testCard))), "");
			}
			//assert(game->numBuys == (prevValue3 - 1));						// Make sure players numBuys gets decremented
			printf("Part 8...");
			if (allPass) {
				allPass = f_Assert((game->numBuys == (prevValue3 - 1)), "");
			}
			else {
				f_Assert((game->numBuys == (prevValue3 - 1)), "");
			}
		}
	}

	// If all tests passed success == 1
	if (allPass) { printf("Unit test was successfully completed.\n"); }

	// Restore original values
	game->whoseTurn = oriPlayer;
	game->numBuys = oriNumBuys;

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
	for (i = 0; i < testCount; i++) {											// Run desired number of tests
		printf("---- STARTING UNIT TEST 4 [%d of %d] ---- \n", i + 1, testCount);
		initializeGame(playerCount, kingdomCards, randSeed, &game);				// Initialize a new game
		testSuccess = testBuyCard(&game, player);
		printf("---- //END// UNIT TEST 4 [%d of %d] ---- \n\n\n", i + 1, testCount);
	}

	// CLEAN-UP AND EXIT
	return 0;
}