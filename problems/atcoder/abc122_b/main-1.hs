isACGT c = c `elem` "ACGT"

solve = go 0 0
  where
    go cur ans [] = ans
    go cur ans (c:cs)
        | isACGT c  = go (cur+1) (max ans (cur+1)) cs
        | otherwise = go 0 ans cs

main = do
    s <- getLine
    print $ solve s
