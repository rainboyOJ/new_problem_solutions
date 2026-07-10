{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 16:16
 update_at: 2026-07-10 16:16
-}
import Data.List (sort)

main = do
    input <- getContents
    let (_:xs) = map read (words input) :: [Int]
        ys = reverse (sort xs)
        alice = sum [ y | (i,y) <- zip [0..] ys, even i ]
        bob   = sum [ y | (i,y) <- zip [0..] ys, odd  i ]
    print $ alice - bob
