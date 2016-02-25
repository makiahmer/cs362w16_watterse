#ifndef _TESTDOMINIONFUNC_H
#define _TESTDOMINIONFUNC_H

#include "dominion.h"

void cardNumToName(int card, char *name);
int randomsnum(int limit,int min);
void play(struct gameState *p,int pcard, int favCard, int *pnumcard, int who, int money);



#endif