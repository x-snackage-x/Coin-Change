# Coin Change Problem - Make Change Variant

Trying to learn Dynamic Programming and practicing C pointers and memory handling.

## CLI

A simple CLI-tool was implemented to run the solver with user input.  
The tool first asks for the amount to be "changed" and then the denominations, which are inputted in ascending order in brackets. 

Example:
```
wd$ ./coin-change-cli.e
Input amount: 31
Input ordered coins as [c-1,c-2,...]: [2,3,4]
```

Output:

```
Answer: 24

Combinations:
[4, 4, 4, 4, 4, 4, 4, 3] = 31
[4, 4, 4, 4, 4, 4, 3, 2, 2] = 31
[4, 4, 4, 4, 4, 3, 2, 2, 2, 2] = 31
[4, 4, 4, 4, 4, 3, 3, 3, 2] = 31
[4, 4, 4, 4, 3, 2, 2, 2, 2, 2, 2] = 31
[4, 4, 4, 4, 3, 3, 3, 3, 3] = 31
[4, 4, 4, 4, 3, 3, 3, 2, 2, 2] = 31
[4, 4, 4, 3, 2, 2, 2, 2, 2, 2, 2, 2] = 31
[4, 4, 4, 3, 3, 3, 3, 3, 2, 2] = 31
[4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2] = 31
[4, 4, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] = 31
[4, 4, 3, 3, 3, 3, 3, 3, 3, 2] = 31
[4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2] = 31
[4, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2] = 31
[4, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] = 31
[4, 3, 3, 3, 3, 3, 3, 3, 3, 3] = 31
[4, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2] = 31
[4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2] = 31
[4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2] = 31
[3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2] = 31
[3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2] = 31
[3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2] = 31
[3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] = 31
[3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] = 31
```

If the number of combinations is over 30 only they will not be printed.

```
wd$ ./coin-change-cli.e
Input amount: 1024
Input ordered coins as [c-1,c-2,...]: [1,2,5,10,20,50,100,200,500,1000]

Answer: 378383337
```

## Test File
A static test file was implemented for the solver.

Expected output:
```
wd$ ./coin-change-c.e
Test 1: amount = 5, coins = [1, 2, 5]
Expected: 4
Answer: 4

Test 2: amount = 3, coins = [2]
Expected: 0
Answer: 0

Test 3: amount = 10, coins = [10]
Expected: 1
Answer: 1

Test 4: amount = 25, coins = [2, 5, 10]
Expected: 6
Answer: 6

Test 5: amount = 7, coins = [1, 2, 5, 10]
Expected: 6
Answer: 6

Test 6: amount = 500, coins = [3, 5, 7, 8, 9, 10, 11]
Expected: 35502874
Answer: 35502874

Test 7: amount = 10000, coins = [1, 2, 5, 10, 20, 50, 100, 500, 1000]
Expected: 924906775148246
Answer: 924906775148246
``` 