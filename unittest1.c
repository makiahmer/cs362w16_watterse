#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


// test to ensure isGameOver works

int main (int argc, char** argv) {
  struct gameState G;
  struct gameState *p = &G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

  printf ("Starting game.\n");
  
  
  // set up game
  initializeGame(2, k, 5, p);
  
  int money = 0;
  int i=0;
  int check = 0;


do{
    money = 0;
	
    for (i = 0; i < numHandCards(p); i++) {
      if (handCard(i, p) == copper)
    money++;
      else if (handCard(i, p) == silver)
    money += 2;
      else if (handCard(i, p) == gold)
    money += 3;

    }
	// player 0 buys card 
    if (whoseTurn(p) == 0) {
		
      if (money >= 8) {
        printf("0: bought province\n"); 
        buyCard(province, p);
      }
      else if (money >= 6) {
        printf("0: bought gold\n"); 
        buyCard(gold, p);
      }
	  
	  else if (money >= 5) {
        printf("0: bought duchy\n"); 
        buyCard(duchy, p);
      }
      else if (money >= 3) {
        printf("0: bought silver\n"); 
        buyCard(silver, p);
      }

      printf("0: end turn\n");
      endTurn(p);
    }
	// player 1 buys card 
    else {

      if (money >= 8) {
        printf("0: bought province\n"); 
        buyCard(province, p);
      }
      else if (money >= 6) {
        printf("0: bought gold\n"); 
        buyCard(gold, p);
      }
	  
	  else if (money >= 5) {
        printf("0: bought duchy\n"); 
        buyCard(duchy, p);
      }
      else if (money >= 3) {
        printf("0: bought silver\n"); 
        buyCard(silver, p);
      }

      printf("0: end turn\n");
      endTurn(p);
      
      endTurn(p);      
    }

      printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, p), scoreFor(1, p));
	
	check = isGameOver(p);
	assert (check == 0 || check == 1);
  }  while (!check);

  printf ("Finished game.\n");
  printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, p), scoreFor(1, p));
  printf ("Unit test 1 for isGameOver, result check: %d\n", check);
  if (check == 1){
	  printf ("game over complete\n");
  }

  return 0;
}