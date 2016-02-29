#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "testdomfunc.h"


void cardNumToName(int card, char *name){
  switch(card){
  case curse: strcpy(name,"Curse");
    break;
  case estate: strcpy(name,"Estate");
    break;
  case duchy: strcpy(name,"Duchy");
    break;
  case province: strcpy(name,"Province");
    break;
  case copper: strcpy(name,"Copper");
    break;
  case silver: strcpy(name,"Silver");
    break;
  case gold: strcpy(name,"Gold");
    break;
  case adventurer: strcpy(name,"Adventurer");
    break;
  case council_room: strcpy(name,"Council Room");
    break;
  case feast: strcpy(name,"Feast");
    break;
  case gardens: strcpy(name,"Gardens");
    break;
  case mine: strcpy(name,"Mine");
    break;
  case remodel: strcpy(name,"Remodel");
    break;
  case smithy: strcpy(name,"Smithy");
    break;
  case village: strcpy(name,"Village");
    break;
  case baron: strcpy(name,"Baron");
    break;
  case great_hall: strcpy(name,"Great Hall");
    break;
  case minion: strcpy(name,"Minion");
    break;
  case steward: strcpy(name,"Steward");
    break;
  case tribute: strcpy(name,"Tribute");
    break;
  case ambassador: strcpy(name,"Ambassador");
    break;
  case cutpurse: strcpy(name,"Cutpurse");
    break;
  case embargo: strcpy(name,"Embargo");
    break;
  case outpost: strcpy(name,"Outpost");
    break;
  case salvager: strcpy(name,"Salvager");
    break;
  case sea_hag: strcpy(name,"Sea Hag");
    break;
  case treasure_map: strcpy(name,"Treasure Map");
    break;

  default: strcpy(name,"?");
  }

}
//Generate a inclusive random number between the limit and min
int randomsnum(int limit,int min){
	
    return (rand()%(limit+1-min))+min;

}

void play(struct gameState *p,int pcard, int favCard, int *pnumcard, int who, int money){
	int i = 0;
	char cardname[32];

	
	cardNumToName(favCard, cardname);
	printf("your fav card is %s\n",cardname);
    if (pcard != -1) {
	cardNumToName(favCard, cardname);
    printf("%d: %s played from position %d\n",who, cardname, pcard); 
	playCard(pcard, -1, -1, -1, p); 
	printf("%s played.\n",cardname);
	money = 0;
	i=0;
	while(i<numHandCards(p)){
	  if (handCard(i, p) == copper){
	    playCard(i, -1, -1, -1, p);
	    money++;
	  }
	  else if (handCard(i, p) == silver){
	    playCard(i, -1, -1, -1, p);
	    money += 2;
	  }
	  else if (handCard(i, p) == gold){
	    playCard(i, -1, -1, -1, p);
	    money += 3;
	  }
	  i++;
	}
      }

      if (money >= 8) {
        printf("%d: bought province\n",who); 
        buyCard(province, p);
      }
      else if (money >= 6) {
        printf("%d: bought gold\n",who); 
        buyCard(gold, p);
      }
      else if ((money >= 4) && (*pnumcard < 2)) {
        printf("%d: bought %s\n",who, cardname); 
        buyCard(favCard, p);
        *pnumcard++;
      }
      else if (money >= 3) {
        printf("%d: bought silver\n",who); 
        buyCard(silver, p);
      }

      printf("%d: end turn\n",who);
      endTurn(p);
    }

