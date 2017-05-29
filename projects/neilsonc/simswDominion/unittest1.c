/* unittest1.c - Testing isGameOver function */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
	
	int seed = 1000, numPlayers = 2, result, failures = 0, numSupply, count, index, i, h, j, k;
	struct gameState G, test;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	
	printf("############### Testing Function: isGameOver ###############\n");
	
	//initialize game state and copy to test case
	initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&test, &G, sizeof(struct gameState));
	
	//test initial case
	result = isGameOver(&test);
	if(result == 0)
		printf("PASSED initial case\n");
	else
		printf("FAILED initial case\n");
	
	
	//test case when province supplyCount equals 0
	test.supplyCount[province] = 0;
	result = isGameOver(&test);
	if(result == 1)
		printf("PASSED province supplyCount equals 0\n");
	else
		printf("FAILED province supplyCount equals 0\n");
	
	
	//test cases when province supplyCount > 0
	for(i = 1; i < 9; i++){
		test.supplyCount[province] = i;
		result = isGameOver(&test);
		if(result == 1){
			failures++;
			index = i;
		}
	}	
	if(failures == 0)
		printf("PASSED province supplyCount > 0\n");
	else
		printf("FAILED province supplyCount > 0 when supply is %d\n", numSupply);
	
	
	//test when any other supply piles equals 0
	failures = 0;
	for(h = 0; h < 25; h++){
		memcpy(&test, &G, sizeof(struct gameState));
		test.supplyCount[province] = 1;
		if(test.supplyCount[h] != 1){
			test.supplyCount[h] = 0;
			result = isGameOver(&test);
			if(result == 1){
				failures++;
			}
		}
	}
	if(failures == 0)
		printf("PASSED other supply piles equal 0\n");
	else
		printf("FAILED other supply piles equal 0\n");
	
	
	
	//test when 3 supply piles equal 0
	memcpy(&test, &G, sizeof(struct gameState));
	test.supplyCount[province] = 1;
	count = 0;
	for(j = 0; j < 25; j++){
		if(test.supplyCount[j] != 1){
			test.supplyCount[j] = 0;
			count++;
			if(count > 2){
				break;
			}
		}
	}
	result = isGameOver(&test);
	if(result == 1)
		printf("PASSED three supply piles equal 0\n");
	else
		printf("FAILED three supply piles equal 0\n");
	
	
	//test when 2 supply piles equal 0
	memcpy(&test, &G, sizeof(struct gameState));
	test.supplyCount[province] = 1;
	count = 0;
	for(k = 0; k < 25; k++){
		if(test.supplyCount[j] != 1){
			test.supplyCount[k] = 0;
			count++;
			if(count > 1){
				break;
			}
		}
	}
	result = isGameOver(&test);
	if(result == 0)
		printf("PASSED two supply piles equal 0\n");
	else
		printf("FAILED two supply piles equal 0\n");
	
		
	
	printf("\n***isGameOver testing finished***\n");
	
	return 0;
}