#include <stdio.h>
#include <stdlib.h>

# include "coin-change.h"
# define max_input_length 10000
# define printLimit 30

coinChange* answerStruct = NULL;
uint64_t** tabuArray = NULL;

typedef struct {
    int inputOK;
    int coinsSize;
    int* coins;
} parseCoinsStruct;

int integerPower(int base, int exponant) {
    int r = 1;
    while (exponant != 0) {
        r *= base;
        --exponant;
    }
    return r;
}

parseCoinsStruct* parseCoinsInput(char* coinInput) {
    parseCoinsStruct* parseReturn = malloc(sizeof(parseCoinsStruct));

    // count coins && varify input
    int lastPosition = 0;
    parseReturn->inputOK = 1;
    parseReturn->coinsSize = 0;
    if(*coinInput != '[') {
        parseReturn->inputOK = 0;
        printf("Missing [\n");
    }
    
    for(int i = 1; i < max_input_length && parseReturn->inputOK == 1; ++i) {
        char curChar = *(coinInput + i);
        char prevChar = *(coinInput + i - 1);
        if(curChar == ',' && prevChar >= '0' && prevChar <= '9') {
            ++(parseReturn->coinsSize);
        } else if(curChar == ']' && prevChar >= '0' && prevChar <= '9') {
            ++(parseReturn->coinsSize);
            lastPosition = i;
            break;
        }
        
        if(curChar == 0) {
            parseReturn->inputOK = -3;
            printf("Missing ]\n");
            break;           
        }

        if(!(curChar == ']' || curChar == ',' 
            || (curChar >= '0' && curChar <= '9'))) {
            parseReturn->inputOK = -1;
            printf("Illegal Character: %c\n", curChar);
            break;
        }

        if(prevChar == ',' && (curChar == ',' || curChar == ']')) {
            parseReturn->inputOK = -2;
            printf("Missing Number\n");
            break;           
        }
    }

    if (parseReturn->inputOK != 1) {
        return parseReturn;
    }
    
    // fill parse input
    parseReturn->coins = malloc(parseReturn->coinsSize * sizeof(int));
    int numberLength = 0;
    int coinIndex = 0;
    for(int i = 1; i <= lastPosition; ++i) {
        char curChar = *(coinInput + i);
        if(curChar == ',' || curChar == ']'){
            int currentCoin = 0;
            for(int j = 1; j <= numberLength; ++j) {
                int currentDigit = *(coinInput + i - j) - '0';
                currentCoin += currentDigit * integerPower(10, j - 1);
            }
            numberLength = 0;
            *(parseReturn->coins + coinIndex++) = currentCoin; 
        } else {
            ++numberLength;
        }  
    }

    return parseReturn;
}

int main() {
    uint64_t combinationsCount = 0;

    int amount = 0;
    char coinInput[max_input_length];
    int* coins;
    int coinsSize;

    printf("Input amount: ");
    fflush(stdout);
    scanf("%d", &amount);

    printf("Input ordered coins as [c-1,c-2,...]: ");
    fflush(stdout);
    scanf("%9999s", coinInput);

    parseCoinsStruct* parseReturn = parseCoinsInput(coinInput);
    if(parseReturn->inputOK != 1) {
        return 0;
    }
    coinsSize = parseReturn->coinsSize;
    coins = parseReturn->coins;
    free(parseReturn);
    printf("\n");

    combinationsCount = change(amount, coins, coinsSize);    
    printf("Answer: %" PRIu64 "\n\n", combinationsCount);
    
    if(combinationsCount <= printLimit) {
        answerStruct = 
            fillCombArrays(combinationsCount, amount, coins, coinsSize);
        printf("Combinations:\n");
        printAllComb(amount);
        
        free2DArray((uint64_t**)answerStruct->combinations, combinationsCount);
        free(answerStruct);
    }

    free2DArray(tabuArray, coinsSize + 1);
}