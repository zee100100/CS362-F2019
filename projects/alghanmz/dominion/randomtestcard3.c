#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"

void doTribute(struct gameState *state, int currentPlayer, int nextPlayer, int tributeRevealedCards[2]);
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
    int nextPlayer;
    int tributePosition;
    int tributeRevealedCards[2];
    int numDeckCards;
    int numDiscardCards;
    int maxTributeCards;
    int numExpectedCardEffects;
    int numCardEffects;
    int result;
    time_t start;
    time_t duration = 5;
    unsigned int numTests = 0;
    unsigned int numEffectsFails = 0;
    unsigned int numActionFails = 0;
    unsigned int numTreasureFails = 0;
    unsigned int numVictoryFails = 0;
    unsigned int tributeDiscardFails = 0;

    // card array
    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, tribute, great_hall };

    // declare the game state
    struct gameState G, G2;

    // Initialize random number generator
    srand(time(0));

    printf("\nBegin Testing doTribute():\n\n");
    start = time(NULL);
    while (time(NULL) - start < duration) {
        numTests++;
        numPlayers = rand() % 3 + 2;            // random number of players: 2-4
        initializeGame(numPlayers, k, seed, &G);

        currentPlayer = rand() % numPlayers;    // random current player: 0-numPlayers
        G.whoseTurn = currentPlayer;
        nextPlayer = (currentPlayer + 1) % numPlayers;

        // Generate 5 random cards for the player's hand
        for (int i=0; i < 5; i++) {
            G.hand[currentPlayer][i] = rand() % baron;  // choose cards between curse and village
        }

        tributePosition = rand() % 5;             // random position for Tribute card
        G.hand[currentPlayer][tributePosition] = tribute;
        updateCoins(currentPlayer, &G, 0);

        numDeckCards = rand() % 6;
        numDiscardCards = rand() % 6;
        maxTributeCards = numDeckCards + numDiscardCards;
        // Generate random cards for the next player's deck
        for (int i=0; i < numDeckCards; i++) {
            G.deck[nextPlayer][i] = rand() % baron;  // choose cards between curse and village
        }
        G.deckCount[nextPlayer] = numDeckCards;
        // Generate random cards for the next player's discard
        for (int i=0; i < numDiscardCards; i++) {
            G.discard[nextPlayer][i] = rand() % baron;  // choose cards between curse and village
        }
        G.discardCount[nextPlayer] = numDiscardCards;

        memcpy(&G2, &G, sizeof(G));
        doTribute(&G2, currentPlayer, nextPlayer, tributeRevealedCards);
        // Calculate the number of expected card effects
        if (maxTributeCards < 2) {
            numExpectedCardEffects = maxTributeCards;
        }
        else if (tributeRevealedCards[0] == tributeRevealedCards[1]) {
            numExpectedCardEffects = 1;
        }
        else {
            numExpectedCardEffects = 2;
        }
        numCardEffects = 0;
        if (G2.deckCount[currentPlayer] != G.deckCount[currentPlayer])
            numCardEffects++;
        if (G2.coins != G.coins)
            numCardEffects++;
        if (G2.numActions != G.numActions)
            numCardEffects++;
        assertEqual(numCardEffects, numExpectedCardEffects, &numEffectsFails);
        for (int i=0; i < numExpectedCardEffects; i++) {
            // Check for Victory card
            if (tributeRevealedCards[i] < copper) {
                assertEqual(G2.deckCount[currentPlayer], G.deckCount[currentPlayer]-2, &numVictoryFails);
            }
            // Check for Treasure card
            else if (tributeRevealedCards[i] <= gold) {
                assertEqual(G2.coins, G.coins+2, &numTreasureFails);
            }
            // Else it must be an Action card
            else {
                assertEqual(G2.numActions, G.numActions+2, &numActionFails);
            }
        }
        result = containsCard(G2.playedCards, G2.playedCardCount, tribute);
        assert(result, &tributeDiscardFails);
    }
    printf("Number of tests run: %d\n", numTests);
    printf("Number of times the number of effects was incorrect: %d\n", numEffectsFails);
    printf("Number of times two cards weren't drawn correctly: %d\n", numVictoryFails);
    printf("Number of times coins didn't increase by 2, when it should: %d\n", numTreasureFails);
    printf("Number of times numActions didn't increase by 2, when it should: %d\n", numActionFails);
    printf("Number of times Tribute card was not discarded: %d\n", tributeDiscardFails);

    printf("End of doTribute() Tests\n\n");
    return 0;
}
