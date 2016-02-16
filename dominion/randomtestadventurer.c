#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define RUN_COUNT 1
#define MAX_TESTS 15
#define VERBOSE 1

//--------------------------------------------------------------
// PROTOTYPES
//--------------------------------------------------------------
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


int main() {

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	int i, j, n, players, player = 0, handCount, deckCount, seed, address;
	int testSuccess, temp, prevHandCount, lastCard, lastCard2;
	struct gameState state;
	// struct gameState stat;
	// struct gameState sta;

	printf("Running Random Adventurer Test\n");

	/*
	--- Author's Note ---
	So, I had problems running out of memory when I used the same gameState variable more than 12 times, and
	I honestly don't know why. I momentarily solved this problem by adding more for loops and creating more gamestates;
	I was still able to get decent coverage, though not up to the amount of tests I originally had in mind.

	*/
	for (j = 0; j < RUN_COUNT; j++) {
		for (i = 0; i < MAX_TESTS; i++) {
			testSuccess = 1;

			do {
				players = rand() % 4;
			} while (players < 2);
			state.whoseTurn = player = rand() % players;		//pick a random player out of the players set. This is SO FINIKY, I can't move this line without the program crashing!!! >:( Could it be the rand()'s seed?
			seed = rand();										//pick random seed
			initializeGame(players, k, seed, &state);			//initialize Gamestate 
			player = state.whoseTurn;

			//Initiate valid state variables
			state.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
			state.discardCount[player] = rand() % MAX_DECK;
			state.handCount[player] = rand() % MAX_HAND;

			//Copy state variables
			prevHandCount = handCount = state.handCount[player];
			deckCount = state.deckCount[player];

			//1 in 3 chance of making empty deck for coverage
			if (seed % 3 == 0) {
				state.deckCount[player] = 0;
			}
			//cardEffect(adventurer, 1, 1, 1, &state);			//Run adventurer card

			// /* ADDED - 02/15/2016 - merrittm
			// Card Effect:
			// Reveal cards from your deck until you reveal 2 Treasure cards.
			// Put those Treasure cards into your hand and discard the
			// other revealed cards.
			// */
			// This is a bad test because hands can be cycled during the cards effect
			// if (VERBOSE == 2) printf("The player has two new cards: ");
			// f_Assert((prevHandCount + 2 == state.handCount[player]), &testSuccess, "");

			 if (state.handCount[player] <= 500 && state.handCount[player] > 2) {
				 lastCard = state.hand[player][state.handCount[player] - 1];		// Get the last card in the players hand
				 lastCard2 = state.hand[player][state.handCount[player] - 2];	// Get the second to last card in the players hand

				 if (VERBOSE == 2) printf("The last two cards in the players hand are treasure cards: ");
				 f_Assert(((lastCard2 == copper || lastCard2 == silver || lastCard2 == gold)
					 && (lastCard == copper || lastCard == silver || lastCard == gold)), &testSuccess, "");
			 }

			printf("Suite %d of %d test %d of %d: ", j + 1, RUN_COUNT, i + 1, MAX_TESTS);
			if (testSuccess) printf("SUCCESS. \n");
			else printf("FAILED. \n");
		}
	}


	//for (i = 0; i < MAX_TESTS; i++) {

	//	do {
	//		players = rand() % 4;
	//	} while (players < 2);
	//	stat.whoseTurn = player = rand() % players; //pick a random player out of the players set.

	//	seed = rand();		//pick random seed
	//	initializeGame(players, k, seed, &stat);	//initialize Gamestate

	//	//Initiate valid state variables
	//	stat.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
	//	stat.discardCount[player] = rand() % MAX_DECK;
	//	stat.handCount[player] = rand() % MAX_HAND;


	//	//Copy state variables
	//	handCount = stat.handCount[player];
	//	deckCount = stat.deckCount[player];

	//	//1 in 3 chance of making empty deck for coverage
	//	if (seed % 3 == 0) {
	//		stat.deckCount[player] = 0;
	//	}

	//	cardEffect(adventurer, 1, 1, 1, &stat);		//Run adventurer card
	//	printf("Test %d of %d\n", i + 1, MAX_TESTS);
	//}

	//for (i = 0; i < MAX_TESTS; i++) {
	//	do {
	//		players = rand() % 4;
	//	} while (players < 2);
	//	sta.whoseTurn = player = rand() % players; //pick a random player out of the players set.
	//	
	//	seed = rand();		//pick random seed
	//	initializeGame(players, k, seed, &sta);	//initialize Gamestate
	//	
	//	//Initiate valid state variables
	//	sta.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
	//	sta.discardCount[player] = rand() % MAX_DECK;
	//	sta.handCount[player] = rand() % MAX_HAND;
	//	
	//	
	//	//Copy state variables
	//	handCount = sta.handCount[player];
	//	deckCount = sta.deckCount[player];
	//	
	//	//1 in 3 chance of making empty deck for coverage
	//	if (seed % 3 == 0) {
	//		
	//		sta.deckCount[player] = 0;
	//	}
	//	cardEffect(adventurer, 1, 1, 1, &sta);		//Run adventurer card
	//	printf("Part 3 test %d of %d\n", i + 1, MAX_TESTS);
	//}

	printf("Tests Complete\n");

	return 0;
}