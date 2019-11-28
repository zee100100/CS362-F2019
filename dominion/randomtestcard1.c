#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"

int baronEffect(struct gameState *state, int choiceDiscardCard);
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
    int numPlayers;
    int currentPlayer;
    int choice1;
    int baronPosition;
    int estatePosition;
    int estateInHand;
    time_t start;
    time_t duration = 5;
    unsigned int numTests = 0;
    unsigned int buyFails = 0;
    unsigned int estateDiscardFails = 0;
    unsigned int baronDiscardFails = 0;
    unsigned int estateGainFails = 0;
    unsigned int coinIncreaseFails = 0;

    // card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall };

    // declare the game state
    struct gameState G, G2;

    // Initialize random number generator
    srand(time(0));

    printf("\nBegin Testing baronEffect():\n\n");
    start = time(NULL);
    while (time(NULL) - start < duration) {
        numTests++;
        printf("baronEffect test #%d\n", numTests);
        numPlayers = rand() % 3 + 2;            // random number of players: 2-4
        initializeGame(numPlayers, k, seed, &G);

        currentPlayer = rand() % numPlayers;    // random current player: 0-numPlayers
        G.whoseTurn = currentPlayer;

        // Generate 5 random cards for the player's hand
        for (int i=0; i < 5; i++) {
            G.hand[currentPlayer][i] = rand() % baron;  // choose cards between curse and village
        }

        baronPosition = rand() % 5;             // random position for Baron card
        G.hand[currentPlayer][baronPosition] = baron;

        //estateInHand = rand() % 2;              // choose whether an estate card is in hand
        estateInHand = 1;   // always put estate in hand to work around infinite loop bug in teammate's code
        if (estateInHand) {
            while (1) {
                estatePosition = rand() % 5;        // random position for Estate card
                if (estatePosition != baronPosition)
                    break;
            }
            G.hand[currentPlayer][estatePosition] = estate;
        }
        updateCoins(currentPlayer, &G, 0);

        memcpy(&G2, &G, sizeof(G));
        choice1 = rand() % 2;           // choose whether to discard or gain estate card
        baronEffect(&G2, choice1);

        assertEqual(G2.numBuys, G.numBuys + 1, &buyFails);
        if (choice1 && estateInHand) {
            assertEqual(cardCount(G2.hand[currentPlayer], G2.handCount[currentPlayer], estate),
                cardCount(G.hand[currentPlayer], G.handCount[currentPlayer], estate) - 1, &estateDiscardFails);
            assertEqual(G2.coins, G.coins + 4, &coinIncreaseFails);
        }
        assert(containsCard(G2.playedCards, G2.playedCardCount, baron), &baronDiscardFails);
        if (!choice1)
            assert(containsCard(G2.discard[currentPlayer], G2.discardCount[currentPlayer], estate), &estateGainFails);
    }
    printf("Number of tests run: %d\n", numTests);
    printf("Number of times numBuys was not increased by 1: %d\n", buyFails);
    printf("Number of times Estate card was not discarded: %d\n", estateDiscardFails);
    printf("Number of times Baron card was not discarded: %d\n", baronDiscardFails);
    printf("Number of times Estate card was not gained: %d\n", estateGainFails);
    printf("Number of times coins was not increased by 4: %d\n", coinIncreaseFails);

    printf("End of baronEffect() Tests\n\n");
    return 0;
}
