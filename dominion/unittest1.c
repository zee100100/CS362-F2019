#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"

int baronEffect(struct gameState *state, int choiceDiscardCard);

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
    int choice1;

    // card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G, G2;

    printf("\nBegin Testing baronEffect():\n\n");
    initializeGame(2, k, seed, &G);
    G.whoseTurn = 0;

    printf("Test 1\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    G2.hand[p][0] = baron;
    choice1 = 0;    // choose to gain an estate card
    baronEffect(&G2, choice1);
    assertEqual(G2.numBuys, G.numBuys + 1, "Number of buys not increased by 1");
    assert(containsCard(G2.discard[p], G2.discardCount[p], estate), "Estate card not gained");
    assert(containsCard(G2.playedCards, G2.playedCardCount, baron), "Baron card not discarded");

    printf("Test 2\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    G2.hand[p][0] = baron;
    G2.hand[p][1] = estate;
    choice1 = 1;    // choose to discard an estate card
    baronEffect(&G2, choice1);
    assertEqual(G2.numBuys, G.numBuys + 1, "Number of buys not increased by 1");
    assertEqual(G2.coins, G.coins + 4, "Coins not increased by 4");
    assertEqual(cardCount(G2.hand[p], G2.handCount[p], estate),
        cardCount(G.hand[p], G.handCount[p], estate) - 1, "Estate card not discarded");
    assertEqual(cardCount(G2.hand[p], G2.handCount[p], baron),
        cardCount(G.hand[p], G.handCount[p], baron) - 1, "Baron card not discarded");

    printf("Test 3\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    G2.hand[p][0] = estate;
    G2.hand[p][1] = baron;
    G2.hand[p][2] = copper;
    G2.hand[p][3] = copper;
    G2.hand[p][4] = copper;
    choice1 = 1;    // choose to discard an estate card
    baronEffect(&G2, choice1);
    assertEqual(G2.numBuys, G.numBuys + 1, "Number of buys not increased by 1");
    assertEqual(G2.coins, G.coins + 4, "Coins not increased by 4");
    assertEqual(cardCount(G2.hand[p], G2.handCount[p], estate),
        cardCount(G.hand[p], G.handCount[p], estate) - 1, "Estate card not discarded");
    assertEqual(cardCount(G2.hand[p], G2.handCount[p], baron),
        cardCount(G.hand[p], G.handCount[p], baron) - 1, "Baron card not discarded");

    printf("End of baronEffect() Tests\n\n");
    return 0;
}
