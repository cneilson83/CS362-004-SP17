/* unittest2.c - Testing gainCard function */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
	
	int seed = 1000, numPlayers = 2, thisPlayer = 0, otherPlayer, newCards, toDeck = 1, toHand = 2, toDiscard = 0;
	int result, failures = 0, i, j, k;
	struct gameState G, test;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	
	printf("############### Testing Function: gainCard ###############\n");
	
	//initialize game state and copy to test case
	initializeGame(numPlayers, kingdomCards, seed, &G);
	memcpy(&test, &G, sizeof(struct gameState));
	newCards = 1;
	
	//test adding a current card when supply pile equals 0
	for(i = 0; i < 10; i++){
		test.supplyCount[kingdomCards[i]] = 0;
		result = gainCard(kingdomCards[i], &test, toDeck, thisPlayer);
		if(result != -1){
			failures++;
		}
	}
	if(failures == 0)
		printf("PASSED adding card with 0 supply\n");
	else
		printf("FAILED adding card with 0 supply\n");
	
	
	//test adding a card not used in current game
	memcpy(&test, &G, sizeof(struct gameState));
	result = gainCard(outpost, &test, toDeck, thisPlayer);
	if(result == -1)
		printf("PASSED adding card not used in game\n");
	else
		printf("FAILED adding card not used in game\n");
	

//TEST ADDING TO DECK	
	// test adding a current card to the deck
	memcpy(&test, &G, sizeof(struct gameState));
	result = gainCard(smithy, &test, toDeck, thisPlayer);
	if((test.deckCount[thisPlayer] == G.deckCount[thisPlayer] + newCards) && result == 0)
		printf("PASSED adding card to deck\n");
	else
		printf("FAILED adding card to deck\n");
	
	// test that nothing was added to hand or discard 
	if(test.handCount[thisPlayer] == G.handCount[thisPlayer] && 
	  test.discardCount[thisPlayer] == G.discardCount[thisPlayer])
		printf("PASSED adding deck, no other piles altered\n");
	else
		printf("FAILED adding deck, no other piles altered\n");
	
	// test that no changes were made for other players
	for(otherPlayer = 1; otherPlayer < numPlayers; otherPlayer++){
		if(test.deckCount[otherPlayer] == G.deckCount[otherPlayer] &&
		  test.handCount[otherPlayer] == G.handCount[otherPlayer] &&
		  test.discardCount[otherPlayer] == G.discardCount[otherPlayer])
			printf("PASSED test for player %d state changes\n", otherPlayer + 1);
		else
			printf("FAILED player %d state changes\n", otherPlayer + 1);
	}
	
	
//TEST ADDING TO HAND
	// test adding a current card to the hand
	memcpy(&test, &G, sizeof(struct gameState));
	result = gainCard(smithy, &test, toHand, thisPlayer);
	if((test.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards) && result == 0)
		printf("PASSED adding card to hand\n");
	else
		printf("FAILED adding card to hand\n");
	
	// test that nothing was added to deck or discard 
	if(test.deckCount[thisPlayer] == G.deckCount[thisPlayer] && 
	  test.discardCount[thisPlayer] == G.discardCount[thisPlayer])
		printf("PASSED adding hand, no other piles altered\n");
	else
		printf("FAILED adding hand, no other piles altered\n");
	
	// test that no changes were made for other players
	for(otherPlayer = 1; otherPlayer < numPlayers; otherPlayer++){
		if(test.deckCount[otherPlayer] == G.deckCount[otherPlayer] &&
		  test.handCount[otherPlayer] == G.handCount[otherPlayer] &&
		  test.discardCount[otherPlayer] == G.discardCount[otherPlayer])
			printf("PASSED test for player %d state changes\n", otherPlayer + 1);
		else
			printf("FAILED player %d state changes\n", otherPlayer + 1);
	}
	
	
//TEST ADDING TO DISCARD
	// test adding a current card to discard
	memcpy(&test, &G, sizeof(struct gameState));
	result = gainCard(smithy, &test, toDiscard, thisPlayer);
	if((test.discardCount[thisPlayer] == G.discardCount[thisPlayer] + newCards) && result == 0)
		printf("PASSED adding card to discard\n");
	else
		printf("FAILED adding card to discard\n");
	
	// test that nothing was added to deck or hand 
	if(test.deckCount[thisPlayer] == G.deckCount[thisPlayer] && 
	  test.handCount[thisPlayer] == G.handCount[thisPlayer])
		printf("PASSED adding discard, no other piles altered\n");
	else
		printf("FAILED adding discard, no other piles altered\n");
	
		
	// test that no changes were made for other players
	for(otherPlayer = 1; otherPlayer < numPlayers; otherPlayer++){
		if(test.deckCount[otherPlayer] == G.deckCount[otherPlayer] &&
		  test.handCount[otherPlayer] == G.handCount[otherPlayer] &&
		  test.discardCount[otherPlayer] == G.discardCount[otherPlayer])
			printf("PASSED test for player %d state changes\n", otherPlayer + 1);
		else
			printf("FAILED player %d state changes\n", otherPlayer + 1);
	}
	
	
	//test that appropriate supply pile was decreased
	if(test.supplyCount[smithy] == G.supplyCount[smithy] - 1)
		printf("PASSED supply updated\n");
	else
		printf("FAILED supply updated\n");
	
	
	//test that no other supply piles were altered
	failures = 0;
	test.supplyCount[smithy] = 1;
	for(j = 0; j < 25; j++){
		if(test.supplyCount[j] != 1){
			if(test.supplyCount[j] != G.supplyCount[j]){
				failures++;
			}
		}
	}
	if(failures == 0)
		printf("PASSED no other supply altered\n");
	else
		printf("FAILED no other supply altered\n");


	
	printf("\n***gainCard testing finished***\n");
	
	return 0;
}