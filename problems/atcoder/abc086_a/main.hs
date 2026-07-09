{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-09 19:45
 update_at: 2026-07-09 19:45
-}
main :: IO ()
main = do
    [a,b] <- map read . words <$> getContents :: IO [Int]
    let c = a * b
    let res = if c `mod` 2 == 0  then "Even" else "Odd"
    putStrLn res
