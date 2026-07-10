{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 10:09
 update_at: 2026-07-10 10:09
-}
calc2 0 = 0
calc2 n = if even n then 1 + calc2 (n `div` 2) else 0

main = do
    input <- getContents
    let xs = map read (words input) :: [Int]
    print $ minimum $ map calc2 (tail xs)