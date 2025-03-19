#include <stdio.h>
#include <stdlib.h>

#include "coin-change.h"

coinChange* answerStruct = NULL;
uint64_t** tabuArray = NULL;

int main() {
    int amount = 5;
    int coins_ex1[] = {1, 2, 5};
    int coinsSize = 3;
    uint64_t expected = 4;
    uint64_t answer = 0;
    printf("Test 1: amount = %d, coins = ", amount);
    printarr(coins_ex1, coinsSize);
    printf("Expected: %" PRIu64 "\n", expected);

    answer = change(amount, coins_ex1, coinsSize);
    answerStruct = fillCombArrays(answer, amount, coins_ex1, coinsSize);
    printf("Answer: %" PRIu64 "\n", answer);
    printf("Combinations:\n");
    printAllComb(amount);

    free2DArray(tabuArray, coinsSize + 1);
    free2DArray((uint64_t**)answerStruct->combinations, answer);
    free(answerStruct);

    amount = 3;
    int coins_ex2[] = {2};
    coinsSize = 1;
    expected = 0;
    printf("Test 2: amount = %d, coins = ", amount);
    printarr(coins_ex2, coinsSize);
    printf("Expected: %" PRIu64 "\n", expected);

    answer = change(amount, coins_ex2, coinsSize);
    answerStruct = fillCombArrays(answer, amount, coins_ex2, coinsSize);
    printf("Answer: %" PRIu64 "\n", answer);
    printf("Combinations:\n");
    printAllComb(amount);

    free2DArray(tabuArray, coinsSize + 1);
    free2DArray((uint64_t**)answerStruct->combinations, answer);
    free(answerStruct);

    amount = 10;
    int coins_ex3[] = {10};
    coinsSize = 1;
    expected = 1;
    printf("Test 3: amount = %d, coins = ", amount);
    printarr(coins_ex3, coinsSize);
    printf("Expected: %" PRIu64 "\n", expected);

    answer = change(amount, coins_ex3, coinsSize);
    answerStruct = fillCombArrays(answer, amount, coins_ex3, coinsSize);
    printf("Answer: %" PRIu64 "\n", answer);
    printf("Combinations:\n");
    printAllComb(amount);

    free2DArray(tabuArray, coinsSize + 1);
    free2DArray((uint64_t**)answerStruct->combinations, answer);
    free(answerStruct);

    amount = 500;
    int coins_ex4[] = {3, 5, 7, 8, 9, 10, 11};
    coinsSize = 7;
    expected = 35502874;
    printf("Test 4: amount = %d, coins = ", amount);
    printarr(coins_ex4, coinsSize);
    printf("Expected: %" PRIu64 "\n", expected);

    answer = change(amount, coins_ex4, coinsSize);
    printf("Answer: %" PRIu64 "\n\n", answer);

    free(tabuArray);

    amount = 10000;
    int coins_ex5[] = {1, 2, 5, 10, 20, 50, 100, 500, 1000};
    coinsSize = 9;
    expected = 924906775148246;
    printf("Test 5: amount = %d, coins = ", amount);
    printarr(coins_ex5, coinsSize);
    printf("Expected: %" PRIu64 "\n", expected);

    answer = change(amount, coins_ex5, coinsSize);
    printf("Answer: %" PRIu64 "\n\n", answer);

    free(tabuArray);

    amount = 25;
    int coins_ex6[] = {2, 5, 10};
    coinsSize = 3;
    expected = 6;
    printf("Test 6: amount = %d, coins = ", amount);
    printarr(coins_ex6, coinsSize);
    printf("Expected: %" PRIu64 "\n", expected);

    answer = change(amount, coins_ex6, coinsSize);
    answerStruct = fillCombArrays(answer, amount, coins_ex6, coinsSize);
    printf("Answer: %" PRIu64 "\n\n", answer);
    printf("Combinations:\n");
    printAllComb(amount);

    free2DArray(tabuArray, coinsSize + 1);
    free2DArray((uint64_t**)answerStruct->combinations, answer);
    free(answerStruct);

    amount = 7;
    int coins_ex7[] = {1, 2, 5, 10};
    coinsSize = 4;
    expected = 6;
    printf("Test 7: amount = %d, coins = ", amount);
    printarr(coins_ex7, coinsSize);
    printf("Expected: %" PRIu64 "\n", expected);

    answer = change(amount, coins_ex7, coinsSize);
    answerStruct = fillCombArrays(answer, amount, coins_ex7, coinsSize);
    printf("Answer: %" PRIu64 "\n", answer);
    printf("Combinations:\n");
    printAllComb(amount);

    getchar();
    fflush(stdin);
    printf("Press any key to continue");
    getchar();

    free2DArray(tabuArray, coinsSize + 1);
    free2DArray((uint64_t**)answerStruct->combinations, answer);
    free(answerStruct);
}