{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 11:20
 update_at: 2026-07-10 11:20
-}
main :: IO ()
main = do
    input <- getContents
    let [a, b, c, target] = map read (words input) :: [Int]
    let ans =
            length
                [ ()
                | x <- [0..a]
                , y <- [0..b]
                , z <- [0..c]
                , x * 500 + y * 100 + z * 50 == target
                ]
    print ans
