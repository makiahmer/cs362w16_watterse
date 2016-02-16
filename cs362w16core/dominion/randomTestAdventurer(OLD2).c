#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TESTS 100

//This randomly tests Adventurer

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int runTest(){
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int players, handCount, deckCount, seed;
	int player = 0;
	
	printf("1, before creating struct\n");

	struct gameState g;
	struct gameState* state = &g;

	players = rand() % 4;
	
	printf("2, random\n");
	seed = rand();		//pick random seed
	
	printf("3, initialize game\n");
	initializeGame(players, k, seed, state);	//initialize Gamestate 

	//Initiate valid state variables
	printf("4, randomizing\n");
	state->deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
	state->discardCount[player] = rand() % MAX_DECK;
	state->handCount[player] = rand() % MAX_HAND;

	printf("deck count %d\n", state->deckCount[player]);
	printf("discardCount %d\n", state->discardCount[player]);
	printf("handCount %d\n", state->handCount[whoseTurn(state)]--);
	
	printf("5, creating hand and deck count\n");
	//Copy state variables
	handCount = state->handCount[player];
	deckCount = state->deckCount[whoseTurn(state)];
	
	//1 in 3 chance of making empty deck for coverage
	if(seed % 3 == 0){
		state->deckCount[player] = 0;
	}
	
	printf("6, Using cardEffect()\n");
	
	//state->whoseTurn = 0;
	cardEffect(adventurer, 1, 1, 1, state, 0, 0);		//Run adventurer card
	
	return 0;
}
	
int main(){

	printf("Running Random Adventurer Test\n");

	/*
									--- Author's Note ---
	So, I had problems running out of memory when I used the same gameState variable more than 12 times, and
	I honestly don't know why. I momentarily solved this problem by adding more for loops and creating more gamestates;
	I was still able to get decent coverage, though not up to the amount of tests I originally had in mind.
	*/

	/*  addition: 
		changed the functionality from in main to in functions. That way the scope of the memory being used
		should be removed and you won't run out. If it isn't a memory issue, then that will be varified by 
		running the function a number of times.
		
		update: 
		The memory issue is still present after refactor. Next step is using trace statements.
	*/
	int i;
	for(i = 0; i < MAX_TESTS; i++){

		runTest();
	
	}

	printf("Tests Complete\n");
	return 0;
}