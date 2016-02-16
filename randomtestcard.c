#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_TESTS 1000

//This randomly tests smithy

int main() {

	  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

	  int i, j, n, players, player, handCount, deckCount, seed, address, oldactioncount, success;
	  //struct gameState state;
	  struct gameState state;
	  
	  srand(time(NULL)); // ensure rand function to be different every run 

	  printf("Running Random Card Test for Village\n");


	  for (i = 0; i < MAX_TESTS; i++) {

		  
		 players = rand() % MAX_PLAYERS;
		 seed = rand();		//pick random seed
		
		 initializeGame(players, k, seed, &state);	//initialize Gamestate

		  //Initiate valid state variables
		  for (player = 0; player < players; player++){
		  state.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
		  state.discardCount[player] = rand() % MAX_DECK;
		  
		  //printf("discardcount is %d \n",state.discardCount[player]);
		  
		  state.handCount[player] = rand() % MAX_HAND;
		  state.hand[player][0] = village; // make sure first are is village 
		  
		  //Copy state variables
		  handCount = state.handCount[player];
		  deckCount = state.deckCount[player];
		  oldactioncount = state.numActions;
		  printf("%d\n", i);
		
		
		
			//playCard(0, -1, -1, -1, &state);
		  cardEffect(village, -1, -1, -1, &state,0,0);		//Run village card

		  printf("%dB\n", i);
		  
		  printf("number of action is %d \n", state.numActions);
		  printf("old number of action is %d \n", oldactioncount);
		  //printf ("number of card in player %d, hand %d \n", player, state.handCount[player]);
		  //printf ("number of card (temp) in player %d, hand %d \n", player, handCount);
		  //printf ("number of card discarded for player %d, hand %d \n", player, state.discardCount[player]);
		  j = player; // set current player for outside of for loop check
		  }
		  
		  // it seems that the number of cards, such as in handCount, discardCount does not change. This can indicate that there
		  // is some problem with the draw and discard function in dominion.c
		  // The action count does get change correctly, but handcount doesn't it was suppose to be increased by 1
		  if ((oldactioncount + 2  == state.numActions) && (handCount == state.handCount[j])){ 
			  printf("yay it worked \n");
			  success++;
		  }

	  }
	   printf("%d of %d of test has passed\n", success,MAX_TESTS);

	  printf("Tests Complete\n");

	  return 0;
}