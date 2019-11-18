#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"

int doMine(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

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
    int handPos;
    int choice1;
    int choice2;
    int ret_val;

    // card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, ambassador, great_hall };

    // declare the game state
    struct gameState G, G2;

    printf("\nBegin Testing doMine():\n\n");
    initializeGame(2, k, seed, &G);

    printf("Test 1\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    G2.hand[p][0] = curse;
    G2.hand[p][1] = mine;
    choice1 = 0;        // choose to trash curse
    choice2 = silver;   // choose to gain a silver
    handPos = 1;        // mine
    ret_val = doMine(choice1, choice2, &G2, handPos, p);
    assertEqual(ret_val, -1, "Didn't return -1 when trying to trash a curse");

    printf("Test 2\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    G2.hand[p][0] = copper;
    G2.hand[p][1] = mine;
    G2.hand[p][2] = copper;
    G2.hand[p][3] = estate;
    G2.hand[p][4] = estate;
    choice1 = 0;        // choose to trash copper
    choice2 = silver;   // choose to gain a silver
    handPos = 1;        // mine
    ret_val = doMine(choice1, choice2, &G2, handPos, p);
    assert(containsCard(G2.playedCards, G2.playedCardCount, mine), "Mine card not discarded");
    assert(containsCard(G2.hand[p], G2.handCount[p], silver), "Silver not gained to hand");
    assert(containsCard(G2.playedCards, G2.playedCardCount, copper), "Copper card not discarded");

    printf("Test 3\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    G2.hand[p][0] = smithy;
    G2.hand[p][1] = mine;
    choice1 = 0;        // choose to trash smithy
    choice2 = silver;   // choose to gain a silver
    handPos = 1;        // mine
    ret_val = doMine(choice1, choice2, &G2, handPos, p);
    assertEqual(ret_val, -1, "Didn't return -1 when trying to trash a smithy");

    printf("End of doMine() Tests\n\n");
    return 0;
}
