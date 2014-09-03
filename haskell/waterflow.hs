import System.Random
array = [2, 5, 1, 2, 3, 4, 7, 7, 6]

colsum ::  [Int] -> Int
colsum = sum . map sendToOne
    where sendToOne x = if x >= 1
                        then 1
                        else 0

-- slow (O(n))
first ::  Int -> [Int] -> Int
first idx []        = 0
first idx (x:xs)
    | x > 0         = idx
    | otherwise     = first (idx + 1) xs

-- Calculates the volume in an array
-- assumes at least two columns
baseVolume ::  [Int] -> Int
baseVolume array =
    let left_idx = left array
        right_idx = right array
        width = right_idx - left_idx - 1
        colsBetween = colsum array - 2
    in width - colsBetween
        where left = first 0
              right a = (fromIntegral (length a)) - (first 0 . reverse $ a) - 1

-- Recursive function that measures volume then "chops off" the base by
-- decrementing the array.
line ::  Int -> [Int] -> Int
line accum array =
    if incontinent array
    then accum
    else line (accum + (baseVolume array)) $ dec array
        where
            incontinent array = (colsum array) < 2
            dec array = map (subtract 1) array

-- drag a lineup the bottom of the array and count volume at each horizontal
-- layer
waterflow ::  [Int] -> Int
waterflow array = line 0 array

-- Fast haskell implementation found online. Very elegant.
waterflow2 :: [Int] -> Int
waterflow2 h =
  sum (zipWith (-)
               (zipWith min
                        (scanl1 max h)
                        (scanr1 max h))
               h)


main :: IO ()
main = do
    let g = mkStdGen 0
        xs10000 = take 1000 $ randomRs (0, 10000) g :: [Int]
    print . show $ waterflow xs10000
    print . show $ waterflow2 xs10000
