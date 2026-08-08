import Data.List

main = do
    let n = 30
    let a = [ n `div` i | i <-[1..n]  ]
    putStrLn $ show a
