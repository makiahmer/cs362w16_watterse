/***************************************************************************
** Filename		:	testdominion.c
** File Location:	dominion/assign4/
** Author		:	Makiah Merritt
** Created		:	02/24/2016
** Formatting	:	Consolas 10pt with tabs sized at 4 spaces
** Description	:	A random test for the entire dominion card game.
** Input		:	N/A
** Output		:	N/A
***************************************************************************/
/*--------------------------------------------------------------------------
// TASKS & NOTES
//--------------------------------------------------------------------------
---- TASKS ----
1) Plays complete games of dominion
	- random number of players (2 - 4)
	- random set of kingdom cards
2) Prints *key (gameState) information to gameResults.out
	*key - player choices, cards played, start and end stats for a player
	NOTE: Instead of doing this programatically, I will have my makefile
	redirect the output to a file.

---- NOTES ----
There are three instances of infinite loops I have come across. I don't know
the cause of any, but I do know they occur during the action phase.
Feast card will usually create one and Tribute will cause one occasionally.
	- To assist with this I end the players action phase if they decide
	not to play a card.
	- Feast will cause an infinite loop when it continually tries to 
	buy a card that is to expensive for the player. The card it tries
	to buy cannot be changed because it is passed in as choice1.

There are also cases in which the cards played array will be printed with
null values. If whoever debugs this for their project notices why it would
be much appreciated.

My card buying's do/while process also posses an issue for infinite loops however
the conditions in place shouldn't necessarily prevent progression unless a player
is both poor and only expensive cards remain.
*/


//--------------------------------------------------------------------------
// INCLUDES, NAMESPACE(S), AND DEFINES
//--------------------------------------------------------------------------
#include "../dominion_helpers.h"
#include "../dominion.h"
#include "../rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>			// Used for srand()
#include <sys/resource.h>	// Used for setrlimit, doesn't work in VS

#define TEST_COUNT 2
#define TURN_TIMEOUT 300	// Number of turns after which to timeout the test, prevent endless games
#define VERBOSE 1			// 0 - no debugging printouts,
							// 1 - basic debugging print statements,
							// +2 - everythings printed (i.e. array contents)

struct linkedList {
	int value;				// Action card in a players hand
	int handPos;			// Position of card in hand
	struct linkedList* next;
};

struct linkedList* f_LinkedListNewList();
int f_LinkedListAppend(int value, int pos, struct linkedList *list);
int f_LinkedListClear(struct linkedList *list);
int f_LinkedListFree(struct linkedList *list);
int f_LinkedListLength(struct linkedList *list);
int f_LinkedListValueAt(int pos, struct linkedList *list);
int f_LinkedListPositionOf(int value, struct linkedList *list);
int f_LinkedListPrint(struct linkedList *list);

const char* CARD_NAMES[] = { "Curse", "Estate", "Duchy", 
"Province", "Copper", "Silver", "Gold", "Adventurer", 
"Council Room", "Feast", "Gardens", "Mine", "Remodel", "Smithy", 
"Village", "Baron", "Great Hall", "Minion", "Steward", 
"Tribute", "Ambassador", "Cutpurse", "Embargo", "Outpost", 
"Salvager", "Sea Hag", "Treasure Map" };

//--------------------------------------------------------------------------
// PROTOTYPE DECLARATIONS
//--------------------------------------------------------------------------
int f_Assert(int test, int* testSuccess, char* message);
int f_PrintStats(int currentPlayer, struct gameState *game);
int f_PrintCardsPlayed(int player, struct gameState *game);
int f_PrintEmbargoTokens(int player, struct gameState *game);
void f_SetChoices(int *choice1, int *choice2, int *choice3, int handPos, int card, struct gameState *game);


//--------------------------------------------------------------------------
// MAIN
//--------------------------------------------------------------------------
int main() {
	/*==== DECLARATIONS ====*/
	// General variables
	int i = 0, j = 0, k = 0, temp = 0;

	// Testing Variables
	int testSuccess = 0, suiteSuccess = 0, failedSuites = 0,
		turnCount = 0, timeoutTriggered = 0;
	float randSeed = 0.0;
	struct rlimit defaultTimeLimit;
	struct rlimit myTimeLimit;
	myTimeLimit.rlim_cur = 10;
	myTimeLimit.rlim_max = 30;
	// getrlimit(RLIMIT_CPU, &defaultTimeLimit);
	// printf("\n Default value now is : %lld\n", (long long int)defaultTimeLimit.rlim_cur);
	// setrlimit(RLIMIT_CPU, &myTimeLimit);
	// printf("\n New value is : %lld\n", (long long int)myTimeLimit.rlim_cur);
	// getrlimit(RLIMIT_CPU, &defaultTimeLimit);
	// printf("\n Default value now is : %lld\n", (long long int)defaultTimeLimit.rlim_cur);
	// return 0;
 
	// Random seeds
	randSeed = time(NULL) - getpid();
	srand(randSeed);											// http://stackoverflow.com/a/34720789/5443200
	SelectStream(2);
	PutSeed(3);

	// Game variables
	struct linkedList *actionCards = f_LinkedListNewList();		// A linked list to hold any action cards in the players hand for the action phase
	int kingdomCards[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int playerCount = 2, currentPlayer = 0, cardPlayed = -1, cardDrawn = -1,
		choice1 = 1, choice2 = 1, choice3 = 1, handPos = 0, supplyPos = 0;
	struct gameState *game = NULL, *testGame = NULL;


	/*==== PROCESS ====*/
	printf("==== Running Random Dominion Test ====\n");
	for (i = 0; i < TEST_COUNT; i++) {
		/*---- RESETS ----*/
		testSuccess = suiteSuccess = turnCount = timeoutTriggered = 0;

		/*---- Setup Game State ----*/
		// Randomize player count
		do {
			playerCount = rand() % 4; 
		} while (playerCount < 2);
		
		// Randomize kingdom cards
		for (j = 0; j < 10; j++) {
			do {
				temp = 1;
				cardDrawn = (rand() % 19) + 7;					// Random card excluding the first 7

				// Make sure this card isn't already in the kingdom card set
				for (k = 0; k < j; k++) {
					if (kingdomCards[k] == cardDrawn) { temp = 0; }
				}
				if (temp) { kingdomCards[j] = cardDrawn; }		// Card isn't already in kingdom cards

			} while (!temp);
		}
		
		// Initialize game state
		if (game != NULL) { free(game); } 
			game = newGame();
		if (testGame != NULL) { free(testGame); } 
			testGame = newGame();
		initializeGame(playerCount, kingdomCards, randSeed, game);
		memcpy(testGame, game, sizeof(struct gameState));

		/*---- Start Test ----*/
		while (!isGameOver(game)) {
			turnCount++;
			testSuccess = 1;
			cardDrawn = cardPlayed = -42;
			currentPlayer = whoseTurn(game);

			/* Print player stats */
			printf("---- Turn %d Start: Player %d ----\n", turnCount, (currentPlayer + 1));
			f_PrintStats(currentPlayer, game);

			/* Action phase */
			while (game->numActions > 0) {
				f_LinkedListClear(actionCards);
				actionCards = f_LinkedListNewList();
				for (j = 0; j < game->handCount[currentPlayer]; j++) {
					temp = game->hand[currentPlayer][j];
					if (temp >= adventurer) {
						f_LinkedListAppend(temp, j, actionCards);
					}
				}
				temp = (rand() % (f_LinkedListLength(actionCards) + 1) - 1);	// actionCards can be empty thus !#div/0 err
				cardPlayed = f_LinkedListValueAt(temp, actionCards);			// Pick a random action card to play
				handPos = f_LinkedListPositionOf(cardPlayed, actionCards);		// Get the hand position


				if (cardPlayed != -42 && cardPlayed != -1) {						// An action card wasn't found.
					temp = rand() % 10;
					if (temp > 2) {								// Determine whether or not the player will play the chosen card
						printf("Player %d will play CARD[%d]: '%s'.\n",
							(currentPlayer + 1), cardPlayed,
							CARD_NAMES[cardPlayed]);
						if (cardPlayed == feast) {
							printf("\tWarning playing feast will probably be an infinite loop.\n");
						}

						// Randomize player choices
						f_SetChoices(&choice1, &choice2, &choice3, handPos, cardPlayed, game); 
						printf("\tCard position:   %d\n", handPos);
						printf("\tPlayers choices: [%d, %d, %d]\n", choice1, choice2, choice3);

						setrlimit(RLIMIT_CPU, &myTimeLimit);			// Set CPU time limit to 10 secs soft, 30 secs hard
						temp = playCard(handPos, choice1, choice2, choice3, game);
						setrlimit(RLIMIT_CPU, &defaultTimeLimit);		// Restore original CPU time limit
						if (temp == -1) {
							printf("Player %d was unable to play CARD[%d]: '%s'.\n",
								(currentPlayer + 1), cardPlayed,
								CARD_NAMES[cardPlayed]);
							break;
						}
					}
					else {
						printf("Player %d will not play CARD[%d]: '%s'.\n",
							(currentPlayer + 1), cardPlayed,
							CARD_NAMES[cardPlayed]);
						printf("Ending players action phase.\n");
						break;
					}
				}
				else {
					if (game->playedCardCount == 0) {
						printf("Player %d has no action cards. \n",
							(currentPlayer + 1));
					}
					else {
						printf("Player %d has no more action cards. \n",
							(currentPlayer + 1));
					}
					break;	// Break out of the while (game->numActions > 0) loop
				}
			}/*--//END//-- while(game->numActions > 0)*/
			printf("-- Post Action Phase --\n");
			f_PrintStats(currentPlayer, game);


			/* Buy phase */
			while (game->numBuys > 0) {
				temp = rand() % 10;
				if (temp > 2) {
					do {
						supplyPos = (rand() % 25) + 1;				// Choose a random card to buy, no one would by curse.
						temp = getCost(supplyPos);					// that has a supply and which the player can afford.
					} while ((temp == -1)
						|| (temp > game->coins)
						|| (game->supplyCount[supplyPos] < 1));
					printf("Player %d will buy CARD[%d]: '%s'.\n",
						(currentPlayer + 1), supplyPos,
						CARD_NAMES[supplyPos]);

					// Attempt to buy the chosen card.
					setrlimit(RLIMIT_CPU, &myTimeLimit);			// Set CPU time limit to 10 secs soft, 30 secs hard
					temp = buyCard(supplyPos, game);
					setrlimit(RLIMIT_CPU, &defaultTimeLimit);		// Restore original CPU time limit


					if (temp == -1) {
						printf("Player %d was unable to buy CARD[%d]: '%s'.\n",
							(currentPlayer + 1), supplyPos,
							CARD_NAMES[supplyPos]);
					}
				}
				else {
					printf("Player %d will not buy anything.\n", (currentPlayer + 1));
					break;
				}
			} /*--//END//-- while (game->numBuys > 0)*/
			printf("-- Post Buy Phase --\n");
			f_PrintStats(currentPlayer, game);

			/* Clean-up phase */
			endTurn(game);
			printf("-- Post Clean-up Phase ----\n");
			f_PrintStats(currentPlayer, game);
			printf("---- Turn %d End: Player %d --\n\n\n", turnCount, (currentPlayer + 1));

			if (turnCount == TURN_TIMEOUT) {
				printf("Suite terminated at turn count = %d.\n", turnCount);
				testSuccess = 0;
				break;						// End game if there is no winner after X turns
			}
		}/*--//END//-- while (!isGameOver(game))*/

		/*---- Test complete ----*/
		if(VERBOSE) {
			printf("Suite %d of %d complete: ", i + 1, TEST_COUNT);
			if (testSuccess) { printf("SUCCESS. \n"); }
			else { printf("FAILED. \n"); }
			if ((VERBOSE > 1) && (i < TEST_COUNT - 1)) printf("\n");
			if (!testSuccess) suiteSuccess = 0;
		}/*-- //END// FOR j loop --*/
	}/*-- //END// FOR i to TEST_COUNT loop --*/


	printf("==== //END// Tests Complete: %d / %d Successful ====\n",
		(TEST_COUNT - failedSuites), TEST_COUNT);

	/*==== CLEANUP AND EXIT ====*/
	f_LinkedListFree(actionCards);
	return 0;
}

//--------------------------------------------------------------------------
// PROTOTYPE DEFINITIONS
//--------------------------------------------------------------------------
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

int f_PrintStats(int player, struct gameState *game) {
	printf("Score:     \t%d\n"
		"Purse:        \t%d\n"
		"Action Count: \t%d\n"
		"Buy Count:    \t%d\n"
		"Hand Count:   \t%d\n"
		"Deck Count:   \t%d\n"
		"Discard Count:\t%d\n",
		scoreFor(player, game), 
		game->coins,
		game->numActions, game->numBuys,
		game->handCount[player],
		game->deckCount[player],
		game->discardCount[player]);
	f_PrintEmbargoTokens(player, game);
	f_PrintCardsPlayed(player, game);
	printf("\n");
	return 0;
};

int f_PrintEmbargoTokens(int player, struct gameState *game) {
	int i = 0, tokenCount = 0;

	printf("Embargo Tokens: ");
	if(VERBOSE > 1) printf("\n\t\t");
	for (i = 0; i < 26; i++) {
		tokenCount += game->embargoTokens[i];
		if (VERBOSE > 1) {
			printf("[%d]: '%s' = %d tokens\t", i,
				CARD_NAMES[i], game->embargoTokens[i]);
			if (i % 2 == 1) printf("\n\t\t");
		}
	}
	printf("%d total tokens. \n", tokenCount);
	return 0;
}

int f_PrintCardsPlayed(int player, struct gameState *game) {
	int i = 0, card = 0;

	printf("Cards Played: \t%d\n", game->playedCardCount);
	for (i = 0; i < game->playedCardCount; i++) {
		card = game->playedCards[i];
		printf("\t\t%d) CARD[%d]: '%s'\n", (i + 1), card, CARD_NAMES[card]);
	}
	return 0;
}

void f_SetChoices(int *choice1, int *choice2, int *choice3, 
	int handPos, int card, struct gameState *game) {
	*choice1 = *choice2 = *choice3 = 0;
	switch (card) {
	case feast:		/* choice1 is supply # of card gained) */
		*choice1 = rand() % 26;
		break;

	case mine:		/* choice1 is hand# of money to trash, choice2 is supply# of money to put in hand */
		*choice1 = rand() % game->handCount[game->whoseTurn];
		*choice2 = (rand() % 6) + 1;							// 0 = curse, 7 = adventurer
		break;

	case remodel:	/* choice1 is hand# of card to remodel, choice2 is supply# */
		*choice1 = rand() % game->handCount[game->whoseTurn];
		*choice2 = rand() % 26;
		break;

	case baron:		/* choice1: boolean for discard of estate */
					/* Discard is always of first (lowest index) estate */
		*choice1 = rand() % 2;
		break;

	case minion:	/* choice1:  1 = +2 coin, 2 = redraw */
		*choice1 = rand() % 2;
		*choice2 = rand() % 2;
		break;

	case steward:	/* choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) */
		*choice1 = rand() % 2;
		*choice2 = rand() % 2;
		*choice3 = rand() % 2;
		break;

	case ambassador:/* choice1 = hand#, choice2 = number to return to supply */
		*choice1 = rand() % game->handCount[game->whoseTurn];
		*choice2 = rand() % 3;	//http://dominioncg.wikia.com/wiki/Ambassador Effect	Reveal a card from your hand. Return up to 2 copies of it from your hand to the Supply. Then each other player gains a copy of it.
		break;

	case embargo:	/* choice1 = supply# */
		*choice1 = rand() % 26;
		break;

	case salvager:	/* choice1 = hand# to trash */
		*choice1 = rand() % game->handCount[game->whoseTurn];
		break;

	default:		/* random choices */
		*choice1 = rand() % 2;
		*choice2 = rand() % 2;
		*choice3 = rand() % 2;
	};

	return;
}

struct linkedList* f_LinkedListNewList() {
	struct linkedList *list = malloc(sizeof(struct linkedList));
	list->value = -42;
	list->handPos = -42;
	list->next = NULL;

	return list;
};

int f_LinkedListAppend(int value, int pos, struct linkedList *list) {
	struct linkedList *itr = list;
	struct linkedList *newNode = malloc(sizeof(struct linkedList));
	newNode->value = value;
	newNode->handPos = pos;
	newNode->next = NULL;

	if ((list->value == -42) && (list->next == NULL)) {
		list->value = value;
		list->handPos = pos;
		return 0;
	}

	while (itr->next != NULL) {
		itr = itr->next;
	}

	itr->next = newNode;
	return 0;
}

int f_LinkedListClear(struct linkedList *list) {
	struct linkedList *itr = list;
	while (itr != NULL) {
		itr = list->next;
		free(list);
		list = itr;
	}

	//struct linkedList *itr = list, *nextItr = list->next;
	//while (itr->next != NULL) {
	//	itr = nextItr;
	//	nextItr = nextItr->next;
	//	itr->value = -42;
	//	itr->handPos = -42;
	//	itr->next = NULL;
	//	free(list);
	//	list = itr;
	//}
	//itr->value = -42;
	//itr->handPos = -42;
	//itr->next = NULL;
	return 0;
}

int f_LinkedListFree(struct linkedList *list) {
	f_LinkedListClear(list);
	//free(list);
	return 0;
}

int f_LinkedListLength(struct linkedList *list) {
	struct linkedList *itr = list;
	int length = 0;

	if ((list->value == -42) && (list->next == NULL)) {
		if (DEBUG) printf("List has no elements.\n");
		return 0;
	}

	while (itr != NULL) {
		length++;
		itr = itr->next;
	}
	return length;
}

int f_LinkedListValueAt(int pos, struct linkedList *list) {
	int i = 0;
	struct linkedList *itr = list;
	if (f_LinkedListLength(list) == 0) {
		if (DEBUG) printf("List has no elements.\n");
		return -1;
	}
	else if (pos > f_LinkedListLength(list)) {
		if (DEBUG) printf("Position is outside list bounds.\n");
		return -1;
	}
	for (i = 0; i < (pos - 1); i++) {
		itr = itr->next;
	}
	return itr->value;
}

int f_LinkedListPositionOf(int value, struct linkedList *list) {
	int i = 0;
	struct linkedList *itr = list;
	if (f_LinkedListLength(list) == 0) {
		if (DEBUG) printf("List has no elements.\n");
		return -1;
	}
	for (i = 0; i < f_LinkedListLength(list); i++) {
		if (itr->value == value) {
			return itr->handPos;
		}
		itr = itr->next;
	}

	if (DEBUG) printf("Value position not found.\n");
	return -1;
}

int f_LinkedListPrint(struct linkedList *list) {
	int i = 0;
	struct linkedList *itr = list;
	if (f_LinkedListLength(list) == 0) {
		if (DEBUG) printf("List has no elements.\n");
		return -1;
	}

	printf("List Contents: \n");
	for (i = 0; i < f_LinkedListLength(list); i++) {
		printf("\t[%d] = %d\n", i + 1, itr->value);
		itr = itr->next;
	}
	return 0;
}
