/* unittest4.c - Testing numHandCards function */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main(){
	
	int seed = 1000, numPlayers = 2, thisPlayer = 0, failures, i;
	struct gameState G, test;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	printf("############### Testing Function: numHandCards ###############\n");
	
	//initialize game state and copy to test case
	initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&test, &G, sizeof(struct gameState));
	
	//test that numHandCards returns the correct number of cards
	test.handCount[thisPlayer]++;
	if(numHandCards(&test) == numHandCards(&G) + 1)
		printf("PASSED number cards in hand update\n");
	else
		printf("FAILED number cards in hand update\n");
	
	
	printf("\n***numHandCards testing finished***\n");
	
	return 0;
}