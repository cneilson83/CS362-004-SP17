/* cardtest2.c - Testing Adventurer */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
	
	int newCards = 0, discardedCard = 0, treasure = 0, nonTreasure = 0, thisPlayer = 0, otherPlayer, result, failures, changes = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, numPlayers = 2, seed = 1000;
	struct gameState G, test;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	
	printf("############### Testing Card: Adventurer ###############\n");

	//initialize game state and copy to test case
	initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&test, &G, sizeof(struct gameState));
	
	//call cardEffect with Adventurer and verify the return value
	result = cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, &bonus);
	if(result == 0)
		printf("PASSED cardEffect return val\n");
	else
		printf("FAILED cardEffect return val\n");
	newCards = 2;
	discardedCard = 1;
	
	
	//test if two cards were added to the players hand
	if(test.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discardedCard)
		printf("PASSED test for hand count\n");
	else
		printf("FAILED hand count\n");
	
	
	//test that the added cards came from the players deck
	if(test.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards)
		printf("PASSED test for deck count\n");
	else
		printf("FAILED deck count\n");
	
	
	
	//test that discarded cards were not treasure cards
	int k;
	failures = 0;
	if(test.discardCount[thisPlayer] == 0){
		failures++;
	}
	for(k = 0; k < test.discardCount[thisPlayer]; k++){
		if(test.discard[thisPlayer][k] == copper || test.discard[thisPlayer][k] == silver || 
		  test.discard[thisPlayer][k] == gold){
			failures++;
		}
	}
	if(failures == 0)
		printf("PASSED test for no discarded treasure\n");
	else
		printf("FAILED no discarded treasure\n");
	
	
	
	
	//test that no other state changes were made to the player
	if(test.coins == G.coins &&	test.numActions == G.numActions && test.numBuys == G.numBuys)
		printf("PASSED test for current player state changes\n");
	else
		printf("FAILED current player state changes\n");
	
	
	//test that no state changes occurred for other players
	for(otherPlayer = 1; otherPlayer < numPlayers; otherPlayer++){
		if(test.deckCount[otherPlayer] == G.deckCount[otherPlayer] &&
		   test.handCount[otherPlayer] == G.handCount[otherPlayer])
			printf("PASSED test for player %d state changes\n", otherPlayer + 1);
		else
			printf("FAILED player %d state changes\n", otherPlayer + 1);
	}
	
	
	//test that no state changes occurred to the victory card piles
	if(test.supplyCount[estate] == G.supplyCount[estate] && 
	   test.supplyCount[duchy] == G.supplyCount[duchy] && 
	   test.supplyCount[province] == G.supplyCount[province])
		printf("PASSED test for no victory card changes\n");
	else
		printf("FAILED victory card changes\n");
	
	
	//test that no state changes were made to the kingdom card piles
	int i, j;
	for(i = adventurer; i <= treasure_map; i++){
		for(j = 0; j < 10; j++){
			if(kingdomCards[j] == i){
				if(test.supplyCount[i] != G.supplyCount[i])
					changes++;
			}
		}
	}
	if(changes == 0)
		printf("PASSED test for no kingdom card changes\n");
	else
		printf("FAILED kingdom card changes\n");
	

	printf("\n***Adventurer testing finished***\n");
	
	return 0;
}