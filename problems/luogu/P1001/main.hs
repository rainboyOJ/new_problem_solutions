main :: IO ()
main = do
    input <- getContents
    let [a, b] = map read (words input) :: [Integer]
    print (a + b)
