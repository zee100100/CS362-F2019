#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"

int tributeEffect(struct gameState *state, int handPos);

void assert(int a, char *s) {
    if (!a) {
        printf("Assert failed: %s\n", s);
    }
}

void assertEqual(int a, int b, char *s) {
    if (a != b) {
        printf("Assert failed: %s\n", s);
    }
}

int containsCard(int *container, int size, int card) {
    for (int i=0; i < size; i++) {
        if (container[i] == card) {
            return 1;
        }
    }
    return 0;
}

int cardCount(int *container, int size, int card) {
    int count = 0;

    for (int i=0; i < size; i++) {
        if (container[i] == card) {
            count++;
        }
    }
    return count;
}

int main() {
    int seed = 47;
    int p;
    int p2;
    //int tributeRevealedCards[2];
    int result;

    // card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, tribute, great_hall };

    // declare the game state
    struct gameState G, G2;

    printf("\nBegin Testing tributeEffect():\n\n");
    initializeGame(2, k, seed, &G);
    G.whoseTurn = 1;

    // Debug test
    memcpy(&G2, &G, sizeof(G));
    p = 1;
    p2 = 0;
    G2.hand[p][0] = tribute;
    G2.deck[p2][G2.deckCount[p2]-2] = smithy;
    G2.deck[p2][G2.deckCount[p2]-1] = estate;
    tributeEffect(&G2, 0);
    result = containsCard(G2.playedCards, G2.playedCardCount, tribute);
    assert(result, "Tribute card not discarded");
    if (result)
        assertEqual(G2.handCount[p], G.handCount[p]+1, "Didn't draw 2 cards");
    else
        assertEqual(G2.handCount[p], G.handCount[p]+2, "Didn't draw 2 cards");
    assertEqual(G2.numActions, G.numActions+2, "Actions didn't increase by 2");

/*
    printf("Test 1\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    p2 = 1;
    G2.hand[p][0] = tribute;
    G2.deckCount[p2] = 0;
    G2.discardCount[p2] = 2;
    G2.discard[p2][G2.discardCount[p2]-2] = copper;
    G2.discard[p2][G2.discardCount[p2]-1] = estate;
    tributeEffect(&G2, 0);
    result = containsCard(G2.playedCards, G2.playedCardCount, tribute);
    assert(result, "Tribute card not discarded");
    if (result)
        assertEqual(G2.handCount[p], G.handCount[p]+1, "Didn't draw 2 cards");
    else
        assertEqual(G2.handCount[p], G.handCount[p]+2, "Didn't draw 2 cards");
    assertEqual(G2.coins, G.coins+2, "Coins didn't increase by 2");

    printf("Test 2\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    p2 = 1;
    G2.hand[p][0] = tribute;
    G2.deck[p2][G2.deckCount[p2]-2] = smithy;
    G2.deck[p2][G2.deckCount[p2]-1] = estate;
    tributeEffect(&G2, 0);
    result = containsCard(G2.playedCards, G2.playedCardCount, tribute);
    assert(result, "Tribute card not discarded");
    if (result)
        assertEqual(G2.handCount[p], G.handCount[p]+1, "Didn't draw 2 cards");
    else
        assertEqual(G2.handCount[p], G.handCount[p]+2, "Didn't draw 2 cards");
    assertEqual(G2.numActions, G.numActions+2, "Actions didn't increase by 2");

    printf("Test 3\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    p2 = 1;
    G2.hand[p][0] = tribute;
    G2.deckCount[p2] = 0;
    G2.discardCount[p2] = 1;
    G2.discard[p2][0] = estate;
    tributeEffect(&G2, 0);
    result = containsCard(G2.playedCards, G2.playedCardCount, tribute);
    assert(result, "Tribute card not discarded");
    if (result)
        assertEqual(G2.handCount[p], G.handCount[p]+1, "Didn't draw 2 cards");
    else
        assertEqual(G2.handCount[p], G.handCount[p]+2, "Didn't draw 2 cards");
*/

    printf("End of tributeEffect() Tests\n\n");
    return 0;
}
