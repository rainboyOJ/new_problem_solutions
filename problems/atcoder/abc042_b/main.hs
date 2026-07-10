{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 15:51
 update_at: 2026-07-10 15:51
-}
import Data.List (sort)

main = do
    input <- getContents
    let (_:ss) = lines input
    putStrLn $ concat (sort ss)
