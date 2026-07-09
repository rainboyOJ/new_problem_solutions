{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-09 21:58
 update_at: 2026-07-09 21:58
-}
main = do 
    str <- getLine
    let [r1,s] = map read . words $ str :: [Int]
    print (2*s - r1)
