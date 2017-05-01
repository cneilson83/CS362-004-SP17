/* cardtest3.c - Testing Village */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
	
	int newCards = 0, discardedCard = 0, newActions = 0, thisPlayer = 0, otherPlayer, result, changes = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, numPlayers = 2, seed = 1000;
	struct gameState G, test;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	
	printf("############### Testing Card: Village ###############\n");

	//initialize game state and copy to test case
	initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&test, &G, sizeof(struct gameState));
	
	//call cardEffect with Village and verify the return value
	result = cardEffect(village, choice1, choice2, choice3, &test, handpos, &bonus);
	if(result == 0)
		printf("PASSED cardEffect return val\n");
	else
		printf("FAILED cardEffect return val\n");
	newCards = 1;
	discardedCard = 1;
	newActions = 2;
	
	
	//test if 1 card was added to the players hand
	printf("Discarded count: new - %s, original - %s", test.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	if(test.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discardedCard /*&&
	   test.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discardedCard*/)
		printf("PASSED test for hand count\n");
	else
		printf("FAILED hand count\n");
	
	
	//test if new card was added from the players own deck
	if(test.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards)
		printf("PASSED test for deck count\n");
	else
		printf("FAILED deck count\n");
	
	
	//test if the number of actions increased by 2
	if(test.numActions == G.numActions + newActions)
		printf("PASSED test for number of actions\n");
	else
		printf("FAILED number of actions\n");
	
		
	//test that no other state changes were made to the player
	if(test.coins == G.coins &&	test.numBuys == G.numBuys)
		printf("PASSED test for current player state changes\n");
	else
		printf("FAILED current player state changes\n");
	
	
	//test that no state changes occurred for other players
	for(otherPlayer = 1; otherPlayer < numPlayers; otherPlayer++){
		if(test.deckCount[otherPlayer] == G.deckCount[otherPlayer] &&
		   test.handCount[otherPlayer] == G.handCount[otherPlayer])
			printf("PASSED test for other player state changes\n");
		else
			printf("FAILED other player state changes\n");
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
	

	printf("\n***Village testing finished***\n");
	
	
	return 0;
}