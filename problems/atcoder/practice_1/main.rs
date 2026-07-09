{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-09 19:30
 update_at: 2026-07-09 19:30
-}
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
