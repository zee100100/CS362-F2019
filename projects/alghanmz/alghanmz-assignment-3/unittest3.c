#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"

int doAmbassador(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

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
    int handPos;
    int choice1;
    int choice2;
    int ret_val;

    // card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, ambassador, great_hall };

    // declare the game state
    struct gameState G, G2;

    printf("\nBegin Testing doAmbassador():\n\n");
    initializeGame(2, k, seed, &G);

    printf("Test 1\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    p2 = 1;
    G2.hand[p][0] = copper;
    G2.hand[p][1] = smithy;
    G2.hand[p][2] = copper;
    G2.hand[p][3] = copper;
    G2.hand[p][4] = ambassador;
    choice1 = 0;    // choose to discard copper
    choice2 = 3;    // choose to discard 3 of them
    handPos = 4;    // ambassador
    ret_val = doAmbassador(choice1, choice2, &G2, handPos, p);
    assertEqual(ret_val, -1, "Didn't return -1 when trying to discard too many cards");
    assertEqual(cardCount(G2.hand[p], G2.handCount[p], copper),
        cardCount(G.hand[p], G.handCount[p], copper) - choice2, "Trashed the wrong number of cards");
    assert(containsCard(G2.playedCards, G2.playedCardCount, ambassador), "Ambassador card not discarded");
    assert(containsCard(G2.discard[p2], G2.discardCount[p2], copper), "Player 2 did not gain a copper");

    printf("Test 2\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    p2 = 1;
    G2.hand[p][0] = ambassador;
    G2.hand[p][1] = ambassador;
    choice1 = 0;    // choose to discard ambassador
    choice2 = 1;    // choose to discard 1 of them
    handPos = 0;    // ambassador
    ret_val = doAmbassador(choice1, choice2, &G2, handPos, p);
    assertEqual(ret_val, -1, "Didn't return -1 when trying to discard ambassador card");
    assert(containsCard(G2.playedCards, G2.playedCardCount, ambassador), "Ambassador card not discarded");
    assert(containsCard(G2.discard[p2], G2.discardCount[p2], ambassador), "Player 2 did not gain an ambassador card");

    printf("End of doAmbassador() Tests\n\n");
    return 0;
}
