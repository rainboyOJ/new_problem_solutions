{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 14:33
 update_at: 2026-07-10 14:33
-}
solve r e c
    | e - c > r  = "advertise"
    | e - c < r  = "do not advertise"
    | otherwise  = "does not matter"
main = do
    (_:rest) <- map read . words <$> getContents :: IO [Int]
    let go [] = []
        go (r:e:c:xs) = solve r e c : go xs
    mapM_ putStrLn $ go rest
