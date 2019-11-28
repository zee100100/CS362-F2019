#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"

int minionEffect(struct gameState *state, int choiceGainCoins, int choiceDiscard, int handPos);
int updateCoins(int player, struct gameState *state, int bonus);

void assert(int a, unsigned int* counter) {
    if (!a) {
        (*counter)++;
    }
}

void assertEqual(int a, int b, unsigned int* counter) {
    if (a != b) {
        (*counter)++;
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
    int numPlayers;
    int currentPlayer;
    int choice1;
    int choice2;
    int minionPosition;
    time_t start;
    time_t duration = 5;
    unsigned int numTests = 0;
    unsigned int actionFails = 0;
    unsigned int minionDiscardFails = 0;
    unsigned int curPlayerDiscardFails = 0;
    unsigned int shouldDiscardFails = 0;
    unsigned int shouldNotDiscardFails = 0;
    unsigned int coinIncreaseFails = 0;

    // card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, minion, great_hall };

    // declare the game state
    struct gameState G, G2;

    // Initialize random number generator
    srand(time(0));

    printf("\nBegin Testing minionEffect():\n\n");
    start = time(NULL);
    while (time(NULL) - start < duration) {
        numTests++;
        numPlayers = rand() % 3 + 2;            // random number of players: 2-4
        initializeGame(numPlayers, k, seed, &G);

        currentPlayer = rand() % numPlayers;    // random current player: 0-numPlayers
        G.whoseTurn = currentPlayer;

        // Generate 5 random cards for the player's hand
        for (int i=0; i < 5; i++) {
            G.hand[currentPlayer][i] = rand() % baron;  // choose cards between curse and village
        }

        minionPosition = rand() % 5;             // random position for Minion card
        G.hand[currentPlayer][minionPosition] = minion;
        updateCoins(currentPlayer, &G, 0);

        if (rand() % 2 == 1) {
            choice1 = 1;
            choice2 = 0;
        }
        else {
            choice1 = 0;
            choice2 = 1;
            for (int i=0; i < numPlayers; i++) {
                if (i != currentPlayer) {
                    G.handCount[i] = rand() % 4 + 3;
                }
            }
        }

        memcpy(&G2, &G, sizeof(G));
        minionEffect(&G2, choice1, choice2, minionPosition);
        assertEqual(G2.numActions, G.numActions + 1, &actionFails);
        assert(containsCard(G2.playedCards, G2.playedCardCount, minion), &minionDiscardFails);
        if (choice1) {
            assertEqual(G2.coins, G.coins + 2, &coinIncreaseFails);
        }
        else {
            assertEqual(G2.handCount[currentPlayer], 4, &curPlayerDiscardFails);
            for (int i=0; i < numPlayers; i++) {
                if (i != currentPlayer) {
                    if (G.handCount[i] > 4)
                        assertEqual(G2.handCount[i], 4, &shouldDiscardFails);
                    else
                        assertEqual(G2.handCount[i], G.handCount[i], &shouldNotDiscardFails);
                }
            }
        }
    }
    printf("Number of tests run: %d\n", numTests);
    printf("Number of times numActions was not increased by 1: %d\n", actionFails);
    printf("Number of times Minion card was not discarded: %d\n", minionDiscardFails);
    printf("Number of times current player didn't discard hand correctly: %d\n", curPlayerDiscardFails);
    printf("Number of times a player with 5 or more cards didn't discard: %d\n", shouldDiscardFails);
    printf("Number of times a player with less than 5 cards did discard: %d\n", shouldNotDiscardFails);
    printf("Number of times coins was not increased by 2: %d\n", coinIncreaseFails);

    printf("End of minionEffect() Tests\n\n");
    return 0;
}
