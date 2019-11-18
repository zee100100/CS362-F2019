#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"

void doMinion(int choice1, int choice2, struct gameState *state, int handPos, int currentPlayer);

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

int main() {
    int seed = 47;
    int p;
    int p2;
    int choice1;
    int choice2;

    // card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, minion, great_hall };

    // declare the game state
    struct gameState G, G2;

    printf("\nBegin Testing doMinion():\n\n");
    initializeGame(4, k, seed, &G);     // 4 players

    printf("Test 1\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    G2.hand[p][0] = minion;
    choice1 = 1;    // choose +2 coins
    choice2 = 0;
    doMinion(choice1, choice2, &G2, 0, p);
    assertEqual(G2.numActions, G.numActions + 1, "Number of actions not increased by 1");
    assertEqual(G2.coins, G.coins + 2, "Number of coins not increased by 2");
    assert(containsCard(G2.playedCards, G2.playedCardCount, minion), "Minion card not discarded");

    printf("Test 2\n");
    memcpy(&G2, &G, sizeof(G));
    p = 0;
    p2 = 2;     // another player
    G2.hand[p][0] = minion;
    G2.handCount[p2] = 3;   // change handcount from 5 to 3
    choice1 = 0;
    choice2 = 1;    // choose to redraw hand
    doMinion(choice1, choice2, &G2, 0, p);
    assertEqual(G2.numActions, G.numActions + 1, "Number of actions not increased by 1");
    assertEqual(G2.handCount[p], 4, "Current player should have exactly 4 cards");
    assertEqual(G2.handCount[p2], 3, "A player with less than 5 cards discarded hand");
    assert(containsCard(G2.playedCards, G2.playedCardCount, minion), "Minion card not discarded");

    printf("End of doMinion() Tests\n\n");
    return 0;
}
