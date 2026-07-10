{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 10:24
 update_at: 2026-07-10 10:24
-}

-- 二进制末尾0的数量 : lowbit
--

-- 递归函数

calc2 n = if even n then 1 + calc2 (n `div` 2) else 0

main = do
    n <- getLine
    str <- getLine
    let x = map read . words $ str :: [Int]
    print $ minimum $ map calc2 x
