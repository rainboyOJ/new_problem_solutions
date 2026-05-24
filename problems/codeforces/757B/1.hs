import Data.Array

-- 定义最大值，题目中 s_i <= 100000
maxVal :: Int
maxVal = 100000

solve :: [Int] -> Int
solve xs = ans
  where
    -- 1. 构建频率数组 (桶)
    -- accumArray 的参数含义:
    -- (+) : 累积函数 (遇到相同的下标怎么处理？相加)
    -- 0   : 初始值
    -- (1, maxVal) : 数组下标范围
    -- [(x, 1) | x <- xs] : 数据源，把每个输入数字 x 变成 (下标, 增量) 的元组
    counts :: Array Int Int
    counts = accumArray (+) 0 (1, maxVal) [(x, 1) | x <- xs]

    -- 2. 定义计算函数：给定一个公因子 g，计算它的倍数出现次数之和
    -- [g, 2*g .. maxVal] 利用 Haskell 的语法糖生成公差为 g 的数列
    countMultiples g = sum [counts ! k | k <- [g, 2*g .. maxVal]]

    -- 3. 对 2 到 maxVal 之间的所有数计算结果，取最大值
    -- 注意列表推导式 [countMultiples g | g <- [2 .. maxVal]]
    allScores = [countMultiples g | g <- [2 .. maxVal]]
    
    -- 4. 处理边界情况
    -- 如果输入全是 1，allScores 里的值可能全是 0。
    -- 但题目允许至少带走 1 个（不能自己打自己），所以结果至少是 1。
    ans = max 1 (if null allScores then 0 else maximum allScores)

main :: IO ()
main = do
    -- 读取输入
    _ <- getLine -- 忽略第一行 n，因为 Haskell 处理列表不需要知道长度
    content <- getContents
    -- 将剩余输入转换为整数列表
    let nums = map read (words content) :: [Int]
    
    -- 计算并输出
    print (solve nums)
