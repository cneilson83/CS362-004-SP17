/* unittest3.c - Testing supplyCount function */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
	
	int seed = 1000, numPlayers = 2, failures, i;
	struct gameState G, test;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	printf("############### Testing Function: supplyCount ###############\n");
	
	//initialize game state and copy to test case
	initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&test, &G, sizeof(struct gameState));
	
	//test that supply updates properly
	test.supplyCount[smithy]--;
	if(supplyCount(smithy, &test) == supplyCount(smithy, &G) - 1)
		printf("PASSED supply update\n");
	else
		printf("FAILED supply update\n");
	
	
	//test that no other cards supply is altered
	test.supplyCount[smithy] = 1;
	for(i = 0; i < 25; i++){
		if(supplyCount(i, &test) != 1){
			if(supplyCount(i, &test) != supplyCount(i, &G)){
				failures++;
			}
		}
	}
	if(failures == 0)
		printf("PASSED other supply not altered\n");
	else
		printf("FAILED other supply not altered\n");
	
	
	printf("\n***supplyCount testing finished***\n");
	
	return 0;
}