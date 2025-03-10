#include <stdio.h>
#include <stdlib.h>

#include "coin-change.h"

void printarr(int* arr, int size) {
    if(size == 0) {
        printf("[]\n");
    }

    for(int i = 0; i < size; i++) {
        if(size == 1) {
            printf("[%i]\n", arr[i]);
        } else if(i == 0) {
            printf("[%i, ", arr[i]);
        } else if(i == size - 1) {
            printf("%i]\n", arr[i]);
        } else {
            printf("%i, ", arr[i]);
        }
    }
}

void printOneComb(int* arr, int size) {
    if(size == 0) {
        printf("[]\n");
        return;
    }

    for(int i = 0; i <= size; i++) {
        if(size == 1) {
            printf("[%i] = %i\n", arr[i], arr[i]);
        } else if(i == 0) {
            printf("[%i", arr[i]);
        } else if(i == size || arr[i] == 0) {
            printf("] = ");
            int sum = 0;
            for(int j = 0; j < i; j++) {
                sum += arr[j];
            }
            printf("%i\n", sum);
            return;
        } else {
            printf(", %i", arr[i]);
        }
    }
}

int sumArray(int* array, int size) {
    int sum = 0;
    for(int i = 0; i < size && array[i] != 0; ++i) {
        sum += *(array + i);
    }
    return sum;
}

void allocateTabuArray(int rows, int cols) {
    tabuArray = (uint64_t**)calloc(rows, sizeof(uint64_t*));
    for(uint64_t i = 0; i < rows; i++) {
        tabuArray[i] = (uint64_t*)calloc(cols, sizeof(uint64_t));
    }
}

void free2DArray(uint64_t** tabuArray, int rows) {
    for(int i = 0; i < rows; ++i) {
        free(*(tabuArray + i));
    }
    free(tabuArray);
}

uint64_t changeRecursive(int amount, int* coins, int coinsSize) {
    // base case
    if((amount == *coins && amount == *(coins + coinsSize - 1)) ||
       amount == 0) {
        return 1;
    } else if(amount < 0 || coinsSize < 1) {
        return 0;
    }

    // include Branch
    uint64_t returnIncludeBranch =
        changeRecursive(amount - *(coins + coinsSize - 1), coins, coinsSize);
    // exclude Branch
    uint64_t returnExcludeBranch =
        changeRecursive(amount, coins, coinsSize - 1);

    return returnExcludeBranch + returnIncludeBranch;
}

uint64_t change(int amount, int* coins, int coinsSize) {
    const uint64_t cols = amount + 1;
    const uint64_t rows = coinsSize + 1;
    allocateTabuArray(rows, cols);

    for(uint64_t i = 0; i <= amount; ++i) {
        for(uint64_t j = 0; j <= coinsSize; ++j) {
            if(i == 0) {
                *(*(tabuArray + j) + i) = 1;
                continue;
            }
            if(j == 0) {
                continue;
            }

            uint64_t currDenom = *(coins + j - 1);
            int64_t denomDif = i - currDenom;

            *(*(tabuArray + j) + i) = *(*(tabuArray + j - 1) + i);

            if(denomDif >= 0) {
                *(*(tabuArray + j) + i) += *(*(tabuArray + j) + denomDif);
            }
        }
    }

    uint64_t sum = *(*(tabuArray + coinsSize) + amount);

    return sum;
}

coinChange* fillCombArrays(int numberCombinations,
                           int amount,
                           int* coins,
                           int coinsSize) {
    int sumOfCoins = 0;

    int rows = numberCombinations;
    int cols = amount;
    int** combArray = (int**)calloc(rows, sizeof(int*));
    for(int i = 0; i < rows; i++) {
        combArray[i] = (int*)calloc(cols, sizeof(int));
    }

    int remainingCombinations = numberCombinations;
    const uint64_t amountColumn = amount;
    int changeGroupPos = 0;
    int changeGroup = 0;

    int i_ChangeGroup = 0;
    uint64_t i_row = coinsSize;
    while(*(coins + i_row - 1) > amount) {
        --i_row;
    }

    while(i_ChangeGroup < remainingCombinations) {
        uint64_t currentChangeGroupCount =
            *(*(tabuArray + i_row) + amountColumn);
        uint64_t belowChangeGroupCount =
            i_row - 1 > 0 ? *(*(tabuArray + i_row - 1) + amountColumn) : 0;
        uint64_t numberGroupWithCurrentDenomMax =
            currentChangeGroupCount - belowChangeGroupCount;

        for(int i = 0; i < numberGroupWithCurrentDenomMax; ++i) {
            *(*(combArray + changeGroup + i) + changeGroupPos) =
                *(coins + i_row - 1);
        }

        int* doneIndexes =
            (int*)calloc(numberGroupWithCurrentDenomMax, sizeof(int));
        int doneGroupsCount = 0;
        int denomListIdx = 1;
        while(doneGroupsCount < numberGroupWithCurrentDenomMax) {
            uint64_t denomIdxBase = 0;
            for(int i = 0; i < numberGroupWithCurrentDenomMax;) {
                if(*(doneIndexes + i) == 1) {
                    ++i;
                    continue;
                }
                int sumCurArray =
                    sumArray(*(combArray + changeGroup + i), amount);
                if(sumCurArray == amount) {
                    *(doneIndexes + i) = 1;
                    ++doneGroupsCount;
                    ++i;
                    continue;
                }

                uint64_t amountIdx = amountColumn - sumCurArray;
                for(int k = coinsSize - 1; denomIdxBase == 0; --k) {
                    denomIdxBase = *(coins + k) > amountIdx ? 0 : k + 1;
                }

                uint64_t denomIdx = denomIdxBase;
                int lastDenomPutInGroup = *(*(combArray + changeGroup + i) +
                                            changeGroupPos + denomListIdx - 1);
                while(*(coins + denomIdx - 1) > lastDenomPutInGroup) {
                    --denomIdxBase;
                    denomIdx = denomIdxBase;
                }

                uint64_t currentChangeGroupCount_j =
                    *(*(tabuArray + denomIdx) + amountIdx);
                uint64_t belowChangeGroupCount_j =
                    *(*(tabuArray + denomIdx - 1) + amountIdx);
                uint64_t numberGroupWithCurrentDenomMax_j =
                    currentChangeGroupCount_j - belowChangeGroupCount_j;

                for(int j = 0; j < numberGroupWithCurrentDenomMax_j; ++j) {
                    int coinDenom = *(coins + denomIdx - 1);
                    *(*(combArray + changeGroup + j + i) + changeGroupPos +
                      denomListIdx) = coinDenom;
                }

                i += numberGroupWithCurrentDenomMax_j;
                --denomIdxBase;
            }

            ++denomListIdx;
        }
        free(doneIndexes);
        i_ChangeGroup += numberGroupWithCurrentDenomMax;
        changeGroup += numberGroupWithCurrentDenomMax;
        --i_row;
    }

    coinChange* answerStruct = malloc(sizeof(coinChange));
    answerStruct->numberCombinations = numberCombinations;
    answerStruct->combinations = combArray;

    return answerStruct;
}

void printAllComb(int amount) {
    if(answerStruct->numberCombinations == 0) {
        printf("[]\n\n\n");
        return;
    }

    for(int i = 0; i < answerStruct->numberCombinations; ++i) {
        printOneComb(*(answerStruct->combinations + i), amount);
    }
    printf("\n\n");
}
