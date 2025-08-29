module Main
  ( main,
  )
where

{-
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
-}

change :: Integer -> [Integer] -> Integer
change amount coins
  | amount < 0 || null coins = 0
  | amount == 0 = 1
  | amount == head coins && amount == last coins = 1
  | otherwise = returnIncludeBranch + returnExcludeBranch
  where
    returnIncludeBranch = change (amount - last coins) coins
    returnExcludeBranch = change amount (init coins)

main :: IO ()
main = do
  putStrLn ("Test 1: amount = " ++ show 5 ++ ", coins = " ++ show [1, 2, 5])
  putStrLn ("Expected: " ++ show 4)
  putStrLn ("Answer: " ++ show (change 5 [1, 2, 5]) ++ "\n")

  putStrLn ("Test 2: amount = " ++ show 3 ++ ", coins = " ++ show [2])
  putStrLn ("Expected: " ++ show 0)
  putStrLn ("Answer: " ++ show (change 3 [2]) ++ "\n")

  putStrLn ("Test 3: amount = " ++ show 10 ++ ", coins = " ++ show [10])
  putStrLn ("Expected: " ++ show 1)
  putStrLn ("Answer: " ++ show (change 10 [10]) ++ "\n")

  putStrLn ("Test 4: amount = " ++ show 25 ++ ", coins = " ++ show [2, 5, 10])
  putStrLn ("Expected: " ++ show 6)
  putStrLn ("Answer: " ++ show (change 25 [2, 5, 10]) ++ "\n")

  putStrLn ("Test 5: amount = " ++ show 7 ++ ", coins = " ++ show [1, 2, 5, 10])
  putStrLn ("Expected: " ++ show 6)
  putStrLn ("Answer: " ++ show (change 7 [1, 2, 5, 10]) ++ "\n")

  putStrLn ("Test 6: amount = " ++ show 500 ++ ", coins = " ++ show [3, 5, 7, 8, 9, 10, 11])
  putStrLn ("Expected: " ++ show 35502874)
  putStrLn ("Answer: " ++ show (change 500 [3, 5, 7, 8, 9, 10, 11]) ++ "\n")

  putStrLn ("Test 7: amount = " ++ show 10000 ++ ", coins = " ++ show [1, 2, 5, 10, 20, 50, 100, 500, 1000])
  putStrLn ("Expected: " ++ show 924906775148246)
  putStrLn ("Answer: " ++ show (change 10000 [1, 2, 5, 10, 20, 50, 100, 500, 1000]))
