module Main where

import Data.List (inits, tails, maximum)

-- | 核心逻辑：定义“是什么 (What)”
-- 答案是：在所有子串中，筛选出是双回文串的那些，然后取长度最大的那个
solve :: String -> Int
solve s = maximum [ length sub | sub <- allSubstrings s, isDoublePalindrome sub ]

-- | 定义：什么是双回文串？
-- 一个字符串 s 是双回文串，当且仅当：
-- 存在一种切分方式 (x, y)，使得 x 是回文串 且 y 是回文串
isDoublePalindrome :: String -> Bool
isDoublePalindrome s = any (\(x, y) -> isPalindrome x && isPalindrome y) (allSplits s)

-- | 定义：什么是回文串？
-- 正序读 和 逆序读 完全一致
isPalindrome :: String -> Bool
isPalindrome s = s == reverse s

-- | 辅助函数：生成一个字符串的所有非空切分 (x, y)
-- "What": 在索引 i 处切开，i 从 1 到 长度-1
allSplits :: String -> [(String, String)]
allSplits s = [ splitAt i s | i <- [1 .. length s - 1] ]

-- | 辅助函数：生成字符串 S 的所有子串
-- "What": 对于 S 的每一个后缀，取其所有的前缀
-- (过滤掉空串和长度小于2的串，因为双回文串至少由两个字符组成)
allSubstrings :: String -> [String]
allSubstrings s = [ sub | suffix <- tails s, sub <- inits suffix, length sub >= 2 ]

-- | 主函数：处理输入输出
main :: IO ()
main = do
    -- 获取输入并去除可能的空白符
    content <- getLine
    print (solve content)
