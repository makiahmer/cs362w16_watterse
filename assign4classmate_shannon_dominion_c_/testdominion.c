#include "dominion.h"
#include "dominion_helpers.h"
#include "testdomfunc.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>


int main(){
	
	srand(time(NULL));
	int i = 0, counter = 0, tempkc = 0, appear = 0, numplayer = 0, seed = 0, temp = -1, check = 0, money = 0;
	int p0card = -1, p1card = -1, p2card = -1, p3card = -1, tempcard0 = 0, tempcard1 = 0, tempcard2 = 0, tempcard3 = 0;
	int p0numcard = 0, p1numcard = 0, p2numcard = 0, p3numcard = 0;
	int favCards[4];
	struct gameState G;
    struct gameState *p = &G;
	char cardName[32];

	// 0 to 26 index start at enum 7 
	//create k[] of of size 10
	int k[10] = {0,0,0,0,0,0,0,0,0,0};
	
	printf("generating a random set of kindom cards\n");
	do{
	//printf("tempkc was %d\n",tempkc);
	tempkc = randomsnum(26,7);
	//printf ("%d\n", tempkc);
	for (i = 0; i < 10; i++){
		if (k[i] == tempkc){
			appear++;
		}
	}
	
	if (appear == 0){
		//printf("k[%d] : %d\n", counter, k[counter]);
		k[counter] = tempkc;
		//printf("k[%d] : %d\n", counter, k[counter]);
		counter++;
	}
	
	appear = 0;
	
	}while(counter < 10);
	

	for (i = 0; i < 10; i++){
	cardNumToName(k[i],cardName);
	printf ("k[%d] : %d , %s\n", i, k[i], cardName);
	//printf ("ktest[%d] : %d\n", i, ktest[i]);
	}
	
	//assign random number of player
	numplayer = randomsnum(4,2);
	
	printf ("number of player is %d \n", numplayer);
	
	//assign see a random number between 0 and 27

	seed = randomsnum(9,1);
	
	//random fav card for player
	for (i = 0; i < numplayer; i++){
		favCards[i] = -1;
		temp = randomsnum(9,0);
		favCards[i] = k[temp];
	}
	
	
	initializeGame(numplayer, k, seed, p);
	do{
		
	 money = 0;

	 //set position of players card	
	 p0card = -1;
	 p1card = -1;
	 p2card = -1;
	 p3card = -1;
	 
	for (i = 0; i < numHandCards(p); i++) {
      if (handCard(i, p) == copper)
    money++;
      else if (handCard(i, p) == silver)
    money += 2;
      else if (handCard(i, p) == gold)
    money += 3;
      else if (handCard(i, p) == favCards[0])
    p0card = i;
      else if (handCard(i, p) == favCards[1])
    p1card = i;
      else if (handCard(i, p) == favCards[2])
    p2card = i;
      else if (handCard(i, p) == favCards[3])
    p3card = i;
    }
	
	//void play(struct gameState *p,int pcard, int favCard, int *pnumcard, int who, int money)
	int tempfav = 0;
	int who = 0;
	if (whoseTurn(p) == 0){
		who = 0;
		//printf("who is : %d\n", who);
		tempfav = favCards[0];
		play(p,p0card, tempfav,&p0numcard, who, money);
	}
	
	else if (whoseTurn(p) == 1){
		who = 1;
		//printf("who is : %d\n", who);
		tempfav = favCards[1];
		play(p,p1card, tempfav,&p1numcard, who, money);
	}
	
	else if (whoseTurn(p) == 2){
		who = 2;
		//printf("who is : %d\n", who);
		tempfav = favCards[2];
		play(p,p2card, tempfav,&p2numcard, who, money);
	}
	
	else if (whoseTurn(p) == 3){
		who = 3;
		//printf("who is : %d\n", who);
		tempfav = favCards[3];
		play(p,p3card, tempfav,&p3numcard, who, money);
	}
	check = isGameOver(p);	
	}while (!check);
	
	printf ("Finished game.\n");
	for (i = 0; i < numplayer; i++){
		 printf ("Player %d: %d\n", i, scoreFor(i, p));
	}
	
	
	return 0;
}