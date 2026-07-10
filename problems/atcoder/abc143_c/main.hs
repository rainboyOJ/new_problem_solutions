{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 21:37
 update_at: 2026-07-10 21:37
-}
import Data.List

main = do
    [_ ,xs] <- lines <$> getContents :: IO [[Char]]
    --print xs
    print $ length . group $ xs
