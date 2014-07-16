module Main where
import System.Environment


diff :: Int -> [Float] -> Float
diff n l = head l - sum (tail l)

-- what constant base (Real) c,
-- such that c^{i} = c^{i - 1} + c^{i - 2} + .. c^{i - n}
-- e.g. mconst 2 = phi
mconst :: Int -> (Float, Float)
mconst n = last $ takeWhile isPositive [(c, diff n . take (n + 1) $ [c**(-(fromIntegral i)) | i <- [1..(n + 1)]])| c <- [1,(1 + delta)..fromIntegral n]]
    where
        delta = 0.000001
        isPositive (a, b) = b < 0

main :: IO ()
main = do
    args <- getArgs
    let i = read (args !! 0) :: Int
    putStrLn . show $ mconst i
