{- supportedby @tanakh -}
import Control.Applicative
main :: IO ()
main = do
    -- get a integer
    a <- readLn
    -- get two integers separated with half-width break
    [b, c] <- map read . words <$> getLine
    -- get a string
    s <- getLine
    -- output
    putStrLn $ show (a + b + c) ++ " " ++ s
