#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_TESTS 1000

//This randomly tests Adventurer

int main() {

	  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

int i, j, n, players, player, handCount, deckCount, seed, address, oldDeckcount, oldDiscardcount, oldHandcount, card, treasure, passed;
	  //struct gameState state;
	  struct gameState state;
	  struct gameState stat;
	  struct gameState sta;

	  srand(time(NULL)); //make rand function not give same result on every test.

	  printf("Running Random Adventurer Test\n");

	  /*
										--- Author's Note (Origional) ---
	  So, I had problems running out of memory when I used the same gameState variable more than 12 times, and
	  I honestly don't know why. I momentarily solved this problem by adding more for loops and creating more gamestates;
	  I was still able to get decent coverage, though not up to the amount of tests I originally had in mind.
	  */


	   for (i = 0; i < MAX_TESTS; i++) {

  		  players = rand() % MAX_PLAYERS;
		  seed = rand();		//pick random seed
		
		  initializeGame(players, k, seed, &sta);	//initialize Gamestate
          for(j = 0; j < players; j++){
		  //Initiate valid state variables
		      sta.deckCount[j] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
		      sta.discardCount[j] = rand() % MAX_DECK;
		      sta.handCount[j] = rand() % MAX_HAND;
			  oldHandcount = sta.handCount[j];
			  oldDiscardcount = sta.discardCount[j];
		      oldDeckcount = sta.deckCount[j];
		  
		  //state.hand[player][0] = adventurer; //make first care addventure
		  

		  //Copy state variables
		      handCount = sta.handCount[j];
		      deckCount = sta.deckCount[j];

		  //1 in 3 chance of making empty deck for coverage
		      // if (seed % 3 == 0) {

			// sta.deckCount[j] = 0;
		      // }
			  
			  player = j;
		  }
		  cardEffect(adventurer, 1, 1, 1, &sta, 0, 0);		//Run adventurer card
		  
			//check that discard pile and see if adventurer function is discaring cards 
				if(sta.discardCount[player] != oldDiscardcount ){
					passed++;
				}
			}	

	  printf("%d of %d of test has passed\n", passed,MAX_TESTS);
	  printf("Tests Complete\n");

	  return 0;
}

