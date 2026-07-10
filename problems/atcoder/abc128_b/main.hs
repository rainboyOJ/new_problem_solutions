{-
 Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 rainboy的学习导航网站: https://idx.roj.ac.cn
 create_at: 2026-07-10 22:00
 update_at: 2026-07-10 22:00
-}
import Data.List (sortOn)
import Data.Ord (Down(..))

type Restaurant = (String, Int, Int)  -- (city, score, index)

parseLine :: Int -> String -> Restaurant
parseLine i line =
    let [city, s] = words line
    in (city, read s, i)

main = do
    input <- getContents
    let (_:lns) = lines input
        restaurants = zipWith parseLine [1..] lns
        sorted = sortOn (\(city, score, _) -> (city, Down score)) restaurants
    mapM_ (print . (\(_,_,i) -> i)) sorted
