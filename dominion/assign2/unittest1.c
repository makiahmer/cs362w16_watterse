/*********************************************************************
** Filename		:	unittest1.c
** File Location:	dominion/assign2/
** Author		:	Makiah Merritt
** Created		:	01/29/2016
** Formatting	:	Consolas 10pt with tabs sized at 4 spaces
** Description	:	A unit test for the playCard function implemented
**				:	in dominion.c
** Input		:	N/A
** Output		:	N/A
*********************************************************************/
/*/------------------------------------------------------------------
// ORIGINAL FUNCTION
//-------------------------------------------------------------------
int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
{
	int card;
	int coin_bonus = 0; 		//tracks coins gain from actions

	//check if it is the right phase
	if (state->phase != 0)
	{
		return -1;
	}

	//check if player has enough actions
	if (state->numActions < 1)
	{
		return -1;
	}

	//get card played
	card = handCard(handPos, state);

	//check if selected card is an action
	if (card < adventurer || card > treasure_map)
	{
		return -1;
	}

	//play card
	if (cardEffect(card, choice1, choice2, choice3, state, handPos, &coin_bonus) < 0)
	{
		return -1;
	}

	//reduce number of actions
	state->numActions--;

	//update coins (Treasure cards may be added with card draws)
	updateCoins(state->whoseTurn, state, coin_bonus);

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
int testPlayCard(struct gameState *game, int player) {
	int handPos, i;												// Loop counters
	int prevValue = 0, prevValue2 = 0, success = 1, allPass = 1;


	for (handPos = 0; handPos < game->handCount[player]; handPos++) {
		// Game State Phase Tests, only valid phase should be 0
		// Test invalid phases
		prevValue = game->phase;
		for (i = -5; i < 5; i++) {
			if (i == 0) { i++; }
			game->phase = i;
			success = playCard(handPos, -1, -1, -1, game);
			//assert(success == -1);
			printf("Part 1...");
			if (allPass) {
				allPass = f_Assert((success == -1), "");
			}
			else {
				f_Assert((success == -1), "");
			}
		}
		game->phase = prevValue;								// Restore prevValue to continue


		// Test player actions, player must have 1 or more actions available
		// Test invalid counts
		prevValue = game->numActions;
		game->numActions = 0;
		success = playCard(handPos, -1, -1, -1, game);
		//assert(success == -1);
		printf("Part 2...");
		if (allPass) {
			allPass = f_Assert((success == -1), "");
		}
		else {
			f_Assert((success == -1), "");
		}
		game->numActions = prevValue;							// Restore prevValue to continue



		// Test card action block
		// Note: adventurer == 7 and treasure_map == 26
		prevValue = game->hand[player][handPos];
		game->hand[player][handPos] = gold;						// Test gold < adventurer
		success = playCard(handPos, -1, -1, -1, game);
		//assert(success == -1);
		printf("Part 3...");
		if (allPass) {
			allPass = f_Assert((success == -1), "");
		}
		else {
			f_Assert((success == -1), "");
		}

		game->hand[player][handPos] = 27;						// Test 27 > treasure_map
		success = playCard(handPos, -1, -1, -1, game);
		//assert(success == -1);
		printf("Part 4...");
		if (allPass) {
			allPass = f_Assert((success == -1), "");
		}
		else {
			f_Assert((success == -1), "");
		}
		game->hand[player][handPos] = prevValue;				// Restore prevValue to continue


		// Test card effect

		// Check player action count to be decremented
		prevValue = game->numActions;
		prevValue2 = game->hand[player][handPos];
			game->hand[player][handPos] = gardens;				// Test gardens, because it has no cardEffect
			success = playCard(handPos, -1, -1, -1, game);
			if (prevValue > 0) {
				//assert(game->numActions == (prevValue - 1));
				printf("Part 5...");
				if (allPass) {
					allPass = f_Assert((game->numActions == (prevValue - 1)), "");
				}
				else {
					f_Assert((game->numActions == (prevValue - 1)), "");
				}
			}
		game->hand[player][handPos] = prevValue2;				// Restore prevValue to continue


		// Test player coins

	}
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
		printf("---- STARTING UNIT TEST 1 [%d of %d] ---- \n", i + 1, testCount);
		initializeGame(playerCount, kingdomCards, randSeed, &game);		// Initialize a new game
		testSuccess = testPlayCard(&game, player);
		printf("---- //END// UNIT TEST 1 [%d of %d] ---- \n\n\n", i + 1, testCount);
	}



	// CLEAN-UP AND EXIT
	return 0;
}