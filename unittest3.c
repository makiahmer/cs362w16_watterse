#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


int main(){
	
	struct gameState g;

	g.hand[0][0] = copper;
	g.hand[0][1] = silver;
	g.hand[0][2] = gold;
	
	int total; 
	int i;
	int money = 0;
	int r;
	for (i = 0; i < 3; i ++){
		printf("what is in hand : %d \n", g.hand[0][i]);
		
		//increment handCount when there is a valid card in hand
		if (g.hand[0][i] >= 0 && g.hand[0][i] <= 26){
			g.handCount[0]++;
		}
	}
	
	
	printf ("I have %d in hand \n",g.handCount[0]);
	
	while(i<numHandCards(&g)){
	  if (handCard(i, &g) == copper){
	    r = playCard(i, -1, -1, -1, &g);
	    money++;
	  }
	  else if (handCard(i, &g) == silver){
	    r = playCard(i, -1, -1, -1, &g);
	    money += 2;
	  }
	  else if (handCard(i, &g) == gold){
	    r = playCard(i, -1, -1, -1, &g);
	    money += 3;
	  }
	  i++;
	}
	
	assert(r == -1 || r == 0);
	printf("playCard Works ! \n");
	
	//updateCoins(0,&g,5);
	
	//total = g.coins;
    //printf("total coin is : %d \n", total);
	
	//assert (total == 11);
	
	return 0;
}