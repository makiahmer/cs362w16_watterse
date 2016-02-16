/*********************************************************************
** Filename		:	randomtest_remodel.c
** File Location:	dominion/assign3/
** Author		:	Makiah Merritt
** Created		:	02/09/2016
** Formatting	:	Consolas 10pt with tabs sized at 4 spaces
** Description	:	A random test for the remodel card effect
**				:	implemented in dominion.c
** Input		:	N/A
** Output		:	N/A
*********************************************************************/
//-------------------------------------------------------------------
// ORIGINAL FUNCTION
//-------------------------------------------------------------------
/* Effect:
	Trash a card from your hand. Gain a card costing up to 2 
	Coins more than the trashed card.

case remodel:
	j = state->hand[currentPlayer][choice1]; //store card we will trash

	if ((getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2))
	{
		return -1;
	}

	gainCard(choice2, state, 0, currentPlayer);

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

	//discard trashed card
	for (i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (state->hand[currentPlayer][i] == j)
		{
			discardCard(i, currentPlayer, state, 0);
			break;
		}
	}

	return 0;
*/


//-------------------------------------------------------------------
// INCLUDES, NAMESPACE(S), AND DEFINES
//-------------------------------------------------------------------
#include "../dominion.h"
#include "../rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>			// Used for srand()

#define RUN_COUNT 5
#define MAX_TESTS 20
#define VERBOSE 1


//-------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------
int f_Assert(int test, int* testSuccess, char* message) {
	if (!test) {
		if (VERBOSE == 2) printf("FAILED \n");
		if (VERBOSE == 3) printf("\n %s", message);
		*testSuccess = 0;
		return 0;
	}
	if (VERBOSE == 2) printf("SUCESS \n");
	return 1;
}


//-------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------
int main() {
	/*==== DECLARATIONS ====*/
	// General variables
	int i, j, testSuccess, suiteSuccess, failedSuites = 0;

	// Random seeds
	int randSeed = time(NULL);
	SelectStream(2);
	PutSeed(3);

	// Game variables
	int kingdomCards[10] = { adventurer, gardens, embargo, 
		village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int playerCount = 2, player = 0, choice1 = 1, choice2 = 1, 
		choice3 = 1, handPos = 0;
	struct gameState game, testGame;


	/*==== PROCESS ====*/
	printf("==== Running Random Remodel Test ====\n");
	for (i = 0; i < RUN_COUNT; i++) {
		suiteSuccess = 1;

		for (j = 0; j < MAX_TESTS; j++) {
			testSuccess = 1;

			/*---- Setup Game State ----*/
			do {
				srand(time(NULL));
				playerCount = rand() % 4; 
			} while (playerCount < 2);							// Generate a random number of players 2-4
			initializeGame(playerCount, kingdomCards, randSeed, &game);			// Initialize a new game

			srand(time(NULL));
			game.whoseTurn = player = rand() % playerCount;		// Pick a random player out of the players set.

			srand(time(NULL));
			game.deckCount[player] = rand() % MAX_DECK;			// Pick random deck size out of MAX DECK size (copied from randomtestadventurer.c)

			srand(time(NULL));
			game.discardCount[player] = rand() % MAX_DECK;		// Pick random discard size out of MAX DECK size (copied from randomtestadventurer.c)

			srand(time(NULL));
			game.handCount[player] = rand() % MAX_HAND;			// Pick random hand size out of MAX HAND size (copied from randomtestadventurer.c)

			srand(time(NULL));
			choice1 = rand() % game.handCount[player] - 1;		// Randomize choice1 to be some card in the players hand

			srand(time(NULL));
			choice2 = rand() % 26;								// Randomize choice2 to be any card

			srand(time(NULL));
			handPos = rand() % game.handCount[player];			// Determine a random hand position to place the card
			game.hand[player][handPos] = remodel;				// Add remodel to players hand

			/*---- Start actual test ----*/
			memcpy(&testGame, &game, sizeof(struct gameState));	// Copy game state
			playCard(handPos, choice1, choice2, choice3, &game);// Run effect

			/* If values were modifiable check the results against expected values */
			if ((getCost(testGame.hand[player][choice1]) + 2) <= getCost(choice2))
			{
				/* One call to play card reduces num actions by 1 */
				if (VERBOSE == 2) printf("Player action count is decremented 1: ");
				f_Assert((game.numActions == (testGame.numActions - 1)), &testSuccess, "");
				
				/* Gain card decrements supply count of choice2 && discard[count-3] should be choice2 */
				if (supplyCount(choice2, &game) >= 1) {
					if (VERBOSE == 2) printf("Supply count of choice2 is decremented: ");
					f_Assert((game.supplyCount[choice2] == (testGame.supplyCount[choice2] - 1)), &testSuccess, "");

					if (VERBOSE == 2) printf("Card of choice2 is 'gained' (placed in discard): ");
					f_Assert(((game.discard[player][game.discardCount[player] - 1]) == choice2), &testSuccess, "");
				}

				/* Two calls to discardCard should yield +2 cards to playedCardCount and -2 cards from handCount*/
				if (VERBOSE == 2) printf("Two cards are added to played card count: ");
				f_Assert((game.playedCardCount == (testGame.playedCardCount + 2)), &testSuccess, "");

				if (VERBOSE == 2) printf("Two cards are decremented from hand count: ");
				f_Assert((game.handCount[player] == (testGame.handCount[player] - 2)), &testSuccess, "");
			}

			/*---- Test complete ----*/
			if(VERBOSE) printf("Suite %d of %d test %d of %d complete: ", i + 1, RUN_COUNT, j + 1, MAX_TESTS);
			if (VERBOSE && testSuccess) { printf("SUCCESS. \n"); }
			else if(VERBOSE) { printf("FAILED. \n"); }
			if ((VERBOSE > 1) && (j < MAX_TESTS - 1)) printf("\n");
			if (!testSuccess) suiteSuccess = 0;
		}/*-- //END// FOR j loop --*/


		if (VERBOSE) {
			printf("---- Suite test complete: ");
			if (suiteSuccess) { printf(" SUCCESS ----\n\n"); }
			else { failedSuites++; printf(" FAILURE ----\n\n"); }
		}


	}/*-- //END// FOR i loop --*/


	printf("==== //END// Tests Complete: %d / %d Successful ====\n", 
		((MAX_TESTS * RUN_COUNT) - failedSuites), (MAX_TESTS * RUN_COUNT));


	/*==== CLEANUP AND EXIT ====*/
	return 0;
}