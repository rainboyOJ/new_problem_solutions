{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 15:44
 update_at: 2026-07-10 15:44
-}
import Data.List (tails)

main = do
    s <- getLine
    print $ maximum $ 0 : [ length (takeWhile (`elem` "ACGT") t) | t <- tails s ]
