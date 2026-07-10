{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 14:18
 update_at: 2026-07-10 14:18
-}
digitSum 0 = 0
digitSum n = n `mod` 10 + digitSum (n `div` 10 )

main = do
    [n,a,b] <- map read . words <$> getContents :: IO [Int]
    let l = [ x | x <- [1..n], let t = digitSum x , t >= a , t <=b ]
    print $ sum l
