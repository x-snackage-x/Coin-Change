#include <stdio.h>
#include <stdlib.h>

void printarr(int *arr, int size) {
    if (size == 0) {
        printf("[]\n");
    }

    for (int i = 0; i < size; i++) {
        if (size == 1) {
            printf("[%i]\n", arr[i]);
        } else if (i == 0) {
            printf("[%i, ", arr[i]);
        } else if (i == size - 1) {
            printf("%i]\n", arr[i]);
        } else {
            printf("%i, ", arr[i]);
        }
    }
}

typedef struct {
    int numberCombinations;
    int** combinations;
} coinChange;

int change(int amount, int* coins, int coinsSize) {
    // base case
    if ((amount == *coins && amount == *(coins + coinsSize - 1)) || amount == 0) {
        return 1;
    } else if (amount < 0 || coinsSize < 1) {
        return 0;
    }

    // include Branch
    int returnIncludeBranch = change(amount - coins[coinsSize - 1], coins, coinsSize);
    
    // exclude Branch
    int returnExcludeBranch = change(amount, coins, coinsSize - 1);

    return returnExcludeBranch + returnIncludeBranch;                               
}

coinChange fillCombArrays(int numberCombinations, int* coins, int coinsSize) {

}

int main() {
    int amount = 5;
    int coins_ex1[] = {1,2,5};
    int coinsSize = 3;
    int expected = 4; 
    printf("Test 1: amount = %d, coins = ", amount);
    printarr(coins_ex1, coinsSize);
    printf("Expected: %d\n", expected);

    int answerEx1 = change(amount, coins_ex1, coinsSize);
    printf("Answer: %d\n\n", answerEx1);

    amount = 3;
    int coins_ex2[] = {2};
    coinsSize = 1;
    expected = 0; 
    printf("Test 2: amount = %d, coins = ", amount);
    printarr(coins_ex2, coinsSize);
    printf("Expected: %d\n", expected);

    int answerEx2 = change(amount, coins_ex2, coinsSize);
    printf("Answer: %d\n\n", answerEx2);

    amount = 10;
    int coins_ex3[] = {10};
    coinsSize = 1;
    expected = 1; 
    printf("Test 3: amount = %d, coins = ", amount);
    printarr(coins_ex3, coinsSize);
    printf("Expected: %d\n", expected);

    
    int answerEx3 = change(amount, coins_ex3, coinsSize);
    printf("Answer: %d\n\n", answerEx3);

    amount = 500;
    int coins_ex4[] = {3,5,7,8,9,10,11};
    coinsSize = 7;
    expected = 35502874; 
    printf("Test 5: amount = %d, coins = ", amount);
    printarr(coins_ex4, coinsSize);
    printf("Expected: %d\n", expected);

    
    int answerEx4 = change(amount, coins_ex4, coinsSize);
    printf("Answer: %d\n", answerEx4);
}

