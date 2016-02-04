/*********************************************************************
** Filename		:	cardtest1.c
** File Location:	dominion/assign2/
** Author		:	Makiah Merritt
** Created		:	02/03/2016
** Formatting	:	Consolas 10pt with tabs sized at 4 spaces
** Description	:	A unit test for the steward card effect implemented
**				:	in dominion.c
** Input		:	N/A
** Output		:	N/A
*********************************************************************/
/*/------------------------------------------------------------------
// ORIGINAL FUNCTION
//-------------------------------------------------------------------
Steward – Choose one: 
+2 Cards; 
or +2 Coins; 
or trash 2 cards from your hand.

case steward:
	if (choice1 == 1)
	{
		//+2 cards
		drawCard(currentPlayer, state);
		drawCard(currentPlayer, state);
	}
	else if (choice1 == 2)
	{
		//+2 coins
		state->coins = state->coins + 2;
	}
	else
	{
		//trash 2 cards in hand
		discardCard(choice2, currentPlayer, state, 1);
		discardCard(choice3, currentPlayer, state, 1);
	}

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
#define SILENT -1
#define QUIET 0
#define VERBOSE 1

int f_Assert(int test, char* message, int noisy) {
	if (!test) {
		if (!(noisy == SILENT)) printf("FAILED \n");
		if (noisy == VERBOSE) printf("\n %s", message);
		return 0;
	}
	if (!(noisy == SILENT)) printf("SUCESS \n");
	return 1;
}


//-------------------------------------------------------------------
//TEST
//-------------------------------------------------------------------
void copyHand(int* copyHand, int* playerHand, int handCount) {
	int i = 0;

	for (i = 0; i < handCount; i++) {
		copyHand[i] = playerHand[i];
	}

	return;
}

int testCardEffect_Steward(int player, int testCard, int testCardPos, struct gameState *game) {
// Steward – Choose one: 
// +2 Cards; 
// or +2 Coins; 
// or trash 2 cards from your hand.
// Wrapup designates that the current steward card is also in the discard pile

	/* DECLARATIONS & INITIALIZATIONS*/
	int testChoice1 = -1, testChoice2 = -1, testChoice3 = -1, testBonus = 0; // Vars passed to cardEffect
	int oriHand[MAX_HAND], oriHandCount = 0, prevValue = 0, allPass = 1;
	int oriPlayer = 0;

	// Store Original Values
	oriPlayer = game->whoseTurn;
	oriHandCount = game->handCount[player];
	copyHand(&oriHand, game->hand[player], game->handCount[player]);
	
	/* PROCESS */
	// Test choice 0: invalid choice
	// Test all fail, shouldn't really fail because option 3 is an else statement, which I
	// believe should be a bug because we want to guarantee success or notify of invalid input
	//printf("Part 1...");

	// Test choice 1: draw two cards
	testChoice1 = 1;
	prevValue = game->handCount[player];
	cardEffect(testCard, testChoice1, testChoice2, testChoice3, game, testCardPos, &testBonus);
	printf("Part 1...");
	if (allPass) {
		allPass = f_Assert((game->handCount[player] == prevValue + 1), "", QUIET);						// Draw 2 discard 1 = 1 new card
		allPass = f_Assert((game->playedCards[game->playedCardCount - 1] == testCard), "", SILENT);		// Smithy was the last card discarded
	}
	else {
		f_Assert((game->handCount[player] == prevValue + 1), "", QUIET);								// Draw 2 discard 1 = 1 new card
		f_Assert((game->playedCards[game->playedCardCount - 1] == testCard), "", SILENT);				// Smithy was the last card discarded
	}
	copyHand(game->hand[player], &oriHand, game->handCount[player]);
	game->handCount[player] = oriHandCount;						// WARNING! This is unsafe to do because there is no update handCount function, handCount is managed by the game state!

	
	// Test choice 2: gain two coins
	testChoice1 = 2;
	prevValue = game->coins;
	cardEffect(testCard, testChoice1, testChoice2, testChoice3, game, testCardPos, &testBonus);
	printf("Part 2...");
	if (allPass) {
		allPass = f_Assert((game->coins == (prevValue + 2)), "", QUIET);								// Player gained two coins
		allPass = f_Assert((game->playedCards[game->playedCardCount - 1] == testCard), "", SILENT);		// Smithy was the last card discarded
	}
	else {
		f_Assert((game->coins == (prevValue + 2)), "", QUIET);											// Player gained two coins
		f_Assert((game->playedCards[game->playedCardCount - 1] == testCard), "", SILENT);				// Smithy was the last card discarded
	}
	copyHand(game->hand[player], &oriHand, game->handCount[player]);
	game->handCount[player] = oriHandCount;						// WARNING! This is unsafe to do because there is no update handCount function, handCount is managed by the game state!
	game->coins -= 2;											// Remove the two test coins
	

	// Test choice 3: trash two cards
	testChoice1 = 3;
	prevValue = game->handCount[player];
	cardEffect(testCard, testChoice1, testChoice2, testChoice3, game, testCardPos, &testBonus);
	printf("Part 3...");
	if (allPass) {
		allPass = f_Assert((game->handCount[player] == prevValue - 3), "", QUIET);						// Discard 3 cards
		allPass = f_Assert((game->playedCards[game->playedCardCount - 1] == testCard), "", SILENT);		// Smithy was the last card discarded
	}
	else {
		f_Assert((game->handCount[player] == prevValue - 3), "", QUIET);								// Discard 3 cards
		f_Assert((game->playedCards[game->playedCardCount - 1] == testCard), "", SILENT);				// Smithy was the last card discarded
	}
	copyHand(game->hand[player], &oriHand, game->handCount[player]);
	game->handCount[player] = oriHandCount;						// WARNING! This is unsafe to do because there is no update handCount function, handCount is managed by the game state!


	/* CLEAN-UP & RETURN */
	// Restore original values
	game->whoseTurn = oriPlayer;

	// If all tests passed success = 1
	if (allPass) { printf("Unit test was successfully completed.\n"); }
	else { printf("At least one subtask failed during this unit test."); }
	return allPass;
}

//-------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------
int main() {
	// DECLARATIONS & INITIALIZATIONS
	/* Loop Counters */
	int i = 0, j = 0;
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
	testCard = steward;
	testCardPos = 0;
	for (i = 0; i < testCount; i++) {											// Run desired number of tests
		printf("---- STARTING CARD TEST 1 [%d of %d] ---- \n", i + 1, testCount);
		initializeGame(playerCount, kingdomCards, randSeed, &game);				// Initialize a new game
		game.hand[player][0] = testCard;										// Set test card
		for (j = 0; j < i; j++) {
			drawCard(player, &game);											// Draw some more cards to make the test more interesting
		}
		testSuccess = testCardEffect_Steward(player, testCard, testCardPos, &game);
		printf("---- //END// CARD TEST 1 [%d of %d] ---- \n\n\n", i + 1, testCount);
	}


	// CLEAN-UP AND EXIT
	return 0;
}