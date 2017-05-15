/* randomtestcard2.c - Testing Village */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define NUM_TESTS 100


int main(){
	
	int i, j, numPlayers, randC, handPos, newCards = 0, discardedCard = 0, newActions = 0, thisPlayer, otherPlayer, changes = 0;
	int seed = 1000;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int cards[13] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, copper, silver, gold};
	struct gameState G, test;
	
	printf("############### Random Test Card: Village ###############\n");

	for(i = 0; i < NUM_TESTS; i++){
		//set random number of players from 1 to 4
		numPlayers = rand() % 4 + 1;
		thisPlayer = numPlayers;
		
		// set random hand position from 0 to max hand
		handPos = rand() % MAX_HAND;
		
		//initialize the game state
		initializeGame(numPlayers, kingdomCards, seed, &G);
		G.whoseTurn = thisPlayer;
		
		//get random numbers for handCount and deckCount from 1 to max
		G.handCount[thisPlayer] = rand() % MAX_HAND + 1;
		G.deckCount[thisPlayer] = rand() % MAX_DECK + 1;
		G.discardCount[thisPlayer] = 0;

		//fill player hand with random cards
		for(j = 0; j < G.handCount[thisPlayer]; j++) {
			randC = rand() % 13;
			G.hand[thisPlayer][j] = cards[randC];
		}
	
		
		//copy game state and use Village card
		memcpy(&test, &G, sizeof(struct gameState));
		useVillage(&test, thisPlayer, handPos);
		newCards = 1;
		discardedCard = 1;
		newActions = 2;

		
		printf("Test Iteration: %i\n", i + 1);
		
		//test if 1 card was added to the players hand
		if(test.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discardedCard)
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
		for(otherPlayer = 0; otherPlayer < numPlayers; otherPlayer++){
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
	}	
	
	printf("\n***Village testing finished***\n");

	return 0;
}