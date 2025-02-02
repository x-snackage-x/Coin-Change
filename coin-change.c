#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

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

int changeRecursive(int amount, int* coins, int coinsSize) {
    // base case
    if ((amount == *coins && amount == *(coins + coinsSize - 1)) || amount == 0) {
        return 1;
    } else if (amount < 0 || coinsSize < 1) {
        return 0;
    }

    // include Branch
    int returnIncludeBranch = changeRecursive(amount - *(coins + coinsSize - 1), coins, coinsSize);    
    // exclude Branch
    int returnExcludeBranch = changeRecursive(amount, coins, coinsSize - 1);

    return returnExcludeBranch + returnIncludeBranch;                               
}

int change(int amount, int* coins, int coinsSize) {
    uint64_t cols = amount + 1;
    uint64_t rows = coinsSize + 1;
    uint64_t** tabuArray = (uint64_t**)calloc(rows, sizeof(uint64_t*));
    for (uint64_t i = 0; i < rows; i++) {
        tabuArray[i] = (uint64_t*)calloc(cols, sizeof(uint64_t));
    }

    for (uint64_t i = 0; i <= amount; ++i) {
        for (uint64_t j = 0; j <= coinsSize; ++j) {
            if (i == 0) {
                *(*(tabuArray + j) + i) = 1;
                continue;
            }
            if (j == 0) {
                continue;
            }

            uint64_t currDenom = *(coins + j - 1);
            int64_t denomDif = i - currDenom;

            *(*(tabuArray + j) + i) = *(*(tabuArray + j - 1) + i);

            if (denomDif >= 0) {
                *(*(tabuArray + j) + i) += *(*(tabuArray + j) + denomDif);
            }
        }
    }

    return *(*(tabuArray + coinsSize) + amount);
}

coinChange fillCombArrays(int numberCombinations, int* coins, int coinsSize) {

}

int main() {
    int amount = 5;
    int coins_ex1[] = {1,2,5};
    int coinsSize = 3;
    int expected = 4; 
    int answer = 0;
    printf("Test 1: amount = %d, coins = ", amount);
    printarr(coins_ex1, coinsSize);
    printf("Expected: %d\n", expected);

    answer = change(amount, coins_ex1, coinsSize);
    printf("Answer:   %d\n\n", answer);

    amount = 3;
    int coins_ex2[] = {2};
    coinsSize = 1;
    expected = 0; 
    printf("Test 2: amount = %d, coins = ", amount);
    printarr(coins_ex2, coinsSize);
    printf("Expected: %d\n", expected);

    answer = change(amount, coins_ex2, coinsSize);
    printf("Answer:   %d\n\n", answer);

    amount = 10;
    int coins_ex3[] = {10};
    coinsSize = 1;
    expected = 1; 
    printf("Test 3: amount = %d, coins = ", amount);
    printarr(coins_ex3, coinsSize);
    printf("Expected: %d\n", expected);

    
    answer = change(amount, coins_ex3, coinsSize);
    printf("Answer:   %d\n\n", answer);

    amount = 500;
    int coins_ex4[] = {3,5,7,8,9,10,11};
    coinsSize = 7;
    expected = 35502874; 
    printf("Test 5: amount = %d, coins = ", amount);
    printarr(coins_ex4, coinsSize);
    printf("Expected: %d\n", expected);

    answer = change(amount, coins_ex4, coinsSize);
    printf("Answer:   %d\n\n", answer);

    amount = 4681;
    int coins_ex5[] = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,
                       36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,
                       68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,
                       100,102,104,106,108,110,112,114,116,118,120,122,
                       124,126,128,130,132,134,136,138,140,142,144,146,
                       148,150,152,154,156,158,160,162,164,166,168,170,
                       172,174,176,178,180,182,184,186,188,190,192,194,
                       196,198,200,202,204,206,208,210,212,214,216,218,
                       220,222,224,226,228,230,232,234,236,238,240,242,
                       244,246,248,250,252,254,256,258,260,262,264,266,
                       268,270,272,274,276,278,280,282,284,286,288,290,
                       292,294,296,298,300,302,304,306,308,310,312,314,
                       316,318,320,322,324,326,328,330,332,334,336,338,
                       340,342,344,346,348,350,352,354,356,358,360,362,
                       364,366,368,370,372,374,376,378,380,382,384,386,
                       388,390,392,394,396,398,400,402,404,406,408,410,
                       412,414,416,418,420,422,424,426,428,430,432,434,
                       436,438,440,442,444,446,448,450,452,454,456,458,
                       460,462,464,466,468,470,472,474,476,478,480,482,
                       484,486,488,490,492,494,496,498,500,502,504,506,
                       508,510,512,514,516,518,520,522,524,526,528,530,
                       532,534,536,538,540,542,544,546,548,550,552,554,
                       556,558,560,562,564,566,568,570,572,574,576,578,
                       580,582,584,586,588,780,936,1170,1560,2340,4680};
    coinsSize = 300;
    expected = 0;
    printf("Test 6: amount = %d, coins = ", amount);
    printarr(coins_ex5, coinsSize);
    printf("Expected: %d\n", expected);

    answer = change(amount, coins_ex5, coinsSize);
    printf("Answer:   %d\n", answer);    

}

