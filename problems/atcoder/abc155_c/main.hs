{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 22:33
 update_at: 2026-07-10 22:33
-}
import Data.List (sort, group)
import Data.Function (on)

main :: IO ()
main = do
    _ <- getLine
    ss <- lines <$> getContents
    let grouped = group (sort ss)
        maxCnt = maximum (map length grouped)
        ans = map head $ filter ((== maxCnt) . length) grouped
    mapM_ putStrLn ans
