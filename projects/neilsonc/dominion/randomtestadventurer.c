/* randomtestcard1.c - Testing Adventurer */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NUM_TESTS 1000


int main(){

	int i, j, numPlayers, randC, newCards = 0, discardedCard = 0, coinsBefore, coinsAfter, thisPlayer, otherPlayer, failures, changes = 0;
	int seed = 1000;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int cards[13] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room, copper, silver, gold};
	struct gameState G, test;
	
	printf("############### Random Test Card: Adventurer ###############\n");

	for(i = 0; i < NUM_TESTS; i++) {
		
		//set random number of players from 1 to 4
		numPlayers = rand() % 4 + 1;
		thisPlayer = numPlayers;
		
		//initialize the game state
		initializeGame(numPlayers, kingdomCards, seed, &G);
		G.whoseTurn = thisPlayer;
		
		//get random numbers for handCount and  deckCount
		G.handCount[thisPlayer] = rand() % MAX_HAND + 1;
		G.deckCount[thisPlayer] = rand() % MAX_DECK + 1;
		G.discardCount[thisPlayer] = 0;

		//fill player hand with random cards
		for(j = 0; j < G.handCount[thisPlayer]; j++) {
			randC = rand() % 13;
			G.hand[thisPlayer][j] = cards[randC];
		}
		coinsBefore = updateCoins(thisPlayer, &G, 0);
		
		
		//copy game state and use adventurer card
		memcpy(&test, &G, sizeof(struct gameState));
		useAdventurer(&test, thisPlayer);
		newCards = 2;
		discardedCard = 1;
		updateCoins(thisPlayer, &test, 0);

		
		printf("Test Iteration: %i\n", i + 1);
		
		//test if two cards were added to the players hand
		if(test.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discardedCard)
			printf("PASSED test for hand count\n");
		else
			printf("FAILED hand count <iteration #%i>\n", i + 1);
		
		
		//test that the added cards came from the players deck
		if(test.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards)
			printf("PASSED test for deck count\n");
		else
			printf("FAILED deck count <iteration #%i>\n", i + 1);
		
		
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
			printf("FAILED no discarded treasure <iteration #%i>\n", i + 1);
		
		
		//test that no other state changes were made to the player
		if(test.coins == G.coins &&	test.numActions == G.numActions && test.numBuys == G.numBuys)
			printf("PASSED test for current player state changes\n");
		else
			printf("FAILED current player state changes <iteration #%i>\n", i + 1);
		
		
		//test that no state changes occurred for other players
		for(otherPlayer = 0; otherPlayer < numPlayers; otherPlayer++){
			if(test.deckCount[otherPlayer] == G.deckCount[otherPlayer] &&
			   test.handCount[otherPlayer] == G.handCount[otherPlayer])
				printf("PASSED test for player %d state changes\n", otherPlayer + 1);
			else
				printf("FAILED player %d state changes <iteration #%i>\n", otherPlayer + 1, i + 1);
		}
		
		
		//test that no state changes occurred to the victory card piles
		if(test.supplyCount[estate] == G.supplyCount[estate] && 
		   test.supplyCount[duchy] == G.supplyCount[duchy] && 
		   test.supplyCount[province] == G.supplyCount[province])
			printf("PASSED test for no victory card changes\n");
		else
			printf("FAILED victory card changes <iteration #%i>\n", i + 1);
		
		
		//test that no state changes were made to the other card piles
		int i, j;
		for(i = adventurer; i <= treasure_map; i++){
			for(j = 0; j < 10; j++){
				if(cards[j] == i){
					if(test.supplyCount[i] != G.supplyCount[i])
						changes++;
				}
			}
		}
		if(changes == 0)
			printf("PASSED test for no other card changes\n");
		else
			printf("FAILED other card changes <iteration #%i>\n", i + 1);

	}
	
	printf("\n***Adventurer testing finished***\n");

	return 0;
}

