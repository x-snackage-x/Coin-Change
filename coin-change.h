#include <inttypes.h>

typedef struct {
    int numberCombinations;
    int** combinations;
} coinChange;

extern coinChange* answerStruct;
extern uint64_t** tabuArray;

int changeRecursive(int amount, int* coins, int coinsSize);
int change(int amount, int* coins, int coinsSize);
coinChange* fillCombArrays(int numberCombinations, int amount, int* coins, int coinsSize);

void free2DArray(uint64_t** tabuArray, int rows);
void printarr(int* arr, int size);
void printAllComb(int amount);