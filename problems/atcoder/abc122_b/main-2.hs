{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 15:38
 update_at: 2026-07-10 15:38
-}
main = do
    s <- getLine
    print $ maximum $ scanl (\cur c -> if c `elem` "ACGT" then cur + 1 else 0) 0 s
