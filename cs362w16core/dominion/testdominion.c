//To do: 
//1) make it to allow multiple games.
//2) set the choice print statements.
//3) set the winner print statements.
//4) make things a bit more readable.
//5) set makefile rules.

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define MAX_TESTS 10

int main (int argc, char** argv) {
	
	int games = 0;
	
	srand(80);
	
	for(;games < MAX_TESTS; games++){

		struct gameState G;
		struct gameState *p = &G;
		

		
		int k[10];
		int pool = 0;
		int random_card = 0;
		int play_cards = 0;
		int i = 0;
		int j = 0;
		int check = 0;
		int we_playin = 0;
		int randPos = 0;
		int choice1 = 0;
		int choice2 = 0;
		int choice3 = 0;
		int num_turns = 0;
		int num_players = (rand() % 3) + 2;
		printf("Number of players: %d\n", num_players);
		for(i = 0; i < 10; i++){
			k[i] = -1;
		}
		
		
		
		do{
		  
			//rand to the size of all enumerated cards minus provences and coins.
			random_card = (rand() % (treasure_map - 6) + 7);
			
			//if we already have the card, don't do it!
			for(i = 0; i  < 10; i = i + 1){
				if(k[i] == random_card){
					check = 1;
				}
			}
			
			if(check == 0){
				k[j] = random_card;
				printf("randomly assigned card: %d\n", random_card);
				j = j + 1;	
				if(j > 9){
					break;
				}
			}
			else{
				check = 0;
			}
			
		}while(pool != 1);

		initializeGame(num_players, k, atoi(argv[1]), p);
		printf("Initialized game!\n");
		we_playin = 0;
		
		while(we_playin != 1){
			randPos = 0;
			if(isGameOver(p) == 1){
				printf("Game will now end after %d turns.\n", num_turns);
				break;
			}
			
			num_turns++;
			printf("Player %d's turn. Hand size:  %d\n", whoseTurn(p), p->handCount[whoseTurn(p)]);
			for(j = 0; j < p->handCount[whoseTurn(p)]; j++){
				printf("   Player %d's hand at %d:  %d\n", whoseTurn(p), j, p->hand[whoseTurn(p)][j] );
			}
			//play a number of cards from 5 to deck count
			play_cards = rand() % ((p->deckCount[whoseTurn(p)]) + 5);
			

			for(j = 0; j < play_cards; j++){
				if(p->numActions > 0){
					i = 0;
					do{		
						randPos = rand() % p->handCount[whoseTurn(p)];
						//give randPos 10 tries to find a card.
						i++;
					}while(p->hand[whoseTurn(p)][randPos] > gold && i < 10);
				
					//There is a large issue where choice1 is highly dependant on the differing array sizes
					//and each card has need for various ranges. I have 2 design choices: I can design each
					//choice selection for the smallest array to prevent the potential for a seg fault, or 
					//I can design the test to check the card value I'm looking to play and set specific 
					//logic for each instance that could happen.
					//
					//I'm going to choose to catter to smallest array so as to not drive myself nuts trying 
					//to figure out every card.
					choice1 = rand() % p->numPlayers;
					choice2 = rand() % p->numPlayers;
					choice3 = rand() % p->numPlayers;
					printf("       We playin' card %d, at hand possition %d\n", p->hand[whoseTurn(p)][randPos], randPos);
					printf("           Choice 1: %d, choice 2: %d, choice 3: %d\n", choice1, choice2, choice3);
					if(playCard(randPos, choice1, choice2, choice3, p) == -1){
						printf("           card failed\n");
					}
				
				}
			}
			
			//try to buy 30 cards

			for(j = 0; j < rand() % 30; j++){
				if(p->numBuys > 0){
					randPos = rand() % treasure_map + 1;
					if(randPos > 6){
						for(i = 0; i < 10; i++){
							if(k[i] == randPos){
								printf("   we buyin' card %d, in supply possition %d\n", k[randPos], randPos);
								if(buyCard(randPos, p) == -1){
									printf("       couldn't buy card\n");
								}
							}
						}
					}
					else{
						printf("   we buyin' card %d, in supply possition %d\n", k[randPos], randPos);
						if(buyCard(randPos, p) == -1){
							printf("       couldn't buy card\n");
						}
					}
				}
			}
			
			endTurn(p);
		}
		
		printf("Getting winners\n");
		int players[MAX_PLAYERS];
		int *p_players = players;
		getWinners(p_players, p);
		for(i = 0; i < MAX_PLAYERS; i++){
			if(i <= num_players - 1){
				printf("Player %d has score: %d\n", i, scoreFor(i, p));
			}
			if(players[i] == 1){
				printf("  player %d has won\n", i);
			}
		}
		
	}
	
	return 0;
}