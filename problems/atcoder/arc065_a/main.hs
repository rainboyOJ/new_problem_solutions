{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 15:01
 update_at: 2026-07-10 15:01
-}
import Data.List (isPrefixOf)

ws = map reverse ["dream", "dreamer", "erase", "eraser"]

go [] = True
go s = case [ drop (length w) s | w <- ws, isPrefixOf w s ] of
           (s':_) -> go s'
           []     -> False

main = do
    s <- getLine
    putStrLn $ if go (reverse (filter (/= '\r') s)) then "YES" else "NO"