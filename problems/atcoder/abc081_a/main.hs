{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-09 20:47
 update_at: 2026-07-09 20:47
-}
main :: IO ()
main = do
    s <- getLine
    let ones = filter (== '1') s
    let cnt = length ones
    print cnt
