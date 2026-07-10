---
title: "Haskell OJ 入门练习题单"
description: "以 AtCoder 为主、Kattis 为辅，面向 Haskell 竞赛输入输出和基础算法写法的入门练习。"
---

# Haskell OJ 入门练习题单

这份题单面向已经会一点 Haskell 语法、但还不熟悉 OJ 写法的学习者。目标不是学习函数式编程理论，而是把 Haskell 用在标准输入输出、短题模拟和基础算法上。

主线平台选 AtCoder，补充平台选 Kattis。AtCoder 题目以 ABC A/B/C、AtCoder Beginners Selection 和 Educational DP 入门题为主；Kattis 只选题意短、输入输出标准、适合练习解析和列表处理的小题。

建议做题时固定使用一套简单写法：

```haskell
main :: IO ()
main = do
    input <- getContents
    let xs = map read (words input) :: [Int]
    print (sum xs)
```

做完每题后，至少复盘三个问题：

1. 输入是一次性 `getContents` 读完，还是逐行读更清楚？
2. 数据适合用列表、`Set`、`Map`，还是数组 / DP 表？
3. 有没有因为惰性求值导致空间变大，需要用 `Data.Map.Strict` 或严格累积？

## 阶段 1：输入输出与基础表达式

目标：

- 熟悉 `getContents`
- 熟悉 `words` / `read` / `print`
- 会把输入拆成整数和字符串
- 会写简单条件表达式

小模板：

```haskell
main :: IO ()
main = do
    xs <- map read . words <$> getContents :: IO [Int]
    print (sum xs)
```

题目：

- [ ] [[problem: atcoder,practice_1]]  
- [ ] [[problem: atcoder,abc086_a]]  
- [ ] [[problem: atcoder,abc081_a]]  
- [ ] [[problem: kattis,hello]]  
- [ ] [[problem: kattis,r2]]
  练习点：读两个整数，直接套公式输出。

## 阶段 2：枚举、取模与简单累计

目标：

- 会用列表推导式枚举小范围
- 会写 `sum` / `length` / `filter`
- 会处理多行输入里的多个数字
- 会把题意直接翻译成表达式

小模板：

```haskell
main :: IO ()
main = do
    [a, b, c, x] <- map read . words <$> getContents :: IO [Int]
    print (length [() | i <- [0..a], j <- [0..b], k <- [0..c], 500*i + 100*j + 50*k == x])
```

题目：

- [ ] [[problem: atcoder,abc081_b]]  
  练习点：反复处理列表，统计所有数都能整除 2 的次数。
- [ ] [AtCoder ABC087B - Coins](https://atcoder.jp/contests/abs/tasks/abc087_b)  
  练习点：列表推导式，多重枚举。
- [ ] [[problem: atcoder,abc083_b]]  
  练习点：数字拆位，`show`、`digitToInt`、范围过滤。
- [ ] [[problem: kattis,nastyhacks]]  
  练习点：多组数据，逐组判断并输出字符串。
- [ ] [Kattis - QALY](https://open.kattis.com/problems/qaly)  
  练习点：浮点数读取，`map` 后求和。

## 阶段 3：字符串、列表变换与排序

目标：

- 熟悉 `String` 本质上是 `[Char]`
- 会用 `isPrefixOf` / `drop` / 递归处理字符串
- 会用 `sort` 排序字符串列表
- 会写简单的最长连续段或子串统计

小模板：

```haskell
import Data.List (sort)

main :: IO ()
main = do
    (_:ss) <- lines <$> getContents
    putStrLn (concat (sort ss))
```

题目：

- [ ] [AtCoder ABC049C - Daydream](https://atcoder.jp/contests/abs/tasks/arc065_a)  
  练习点：字符串递归匹配，可以从后往前消去单词。
- [ ] [[problem: atcoder,abc122_b]]  
  练习点：连续合法字符段，`takeWhile` / 递归 / 分段统计。
- [ ] [AtCoder ABC042B - Iroha Loves Strings](https://atcoder.jp/contests/abc042/tasks/abc042_b)  
  练习点：读取多行字符串，排序后拼接。
- [ ] [Kattis - Autori](https://open.kattis.com/problems/autori)  
  练习点：按 `-` 分隔字符串，取每段首字母。
- [ ] [Kattis - Filip](https://open.kattis.com/problems/filip)  
  练习点：字符串反转，比较两个数字字符串。

## 阶段 4：排序、集合与去重

目标：

- 会使用 `Data.List.sort`
- 会用 `group` 统计连续相同元素
- 会用 `Data.Set` 去重
- 会处理排序后的贪心 / 模拟

小模板：

```haskell
import qualified Data.Set as Set

main :: IO ()
main = do
    xs <- map read . words <$> getContents :: IO [Int]
    print (Set.size (Set.fromList xs))
```

题目：

- [ ] [AtCoder ABC088B - Card Game for Two](https://atcoder.jp/contests/abs/tasks/abc088_b)  
  练习点：降序排序，交替取数。
- [ ] [AtCoder ABC085B - Kagami Mochi](https://atcoder.jp/contests/abs/tasks/abc085_b)  
  练习点：`Set.fromList` 去重。
- [ ] [AtCoder ABC143C - Slimes](https://atcoder.jp/contests/abc143/tasks/abc143_c)  
  练习点：`group` 统计压缩后的段数。
- [ ] [AtCoder ABC128B - Guidebook](https://atcoder.jp/contests/abc128/tasks/abc128_b)  
  练习点：元组排序，自定义排序键。
- [ ] [Kattis - Cold-puter Science](https://open.kattis.com/problems/cold)  
  练习点：过滤负数，统计数量。

## 阶段 5：Map、计数与查找

目标：

- 会用 `Data.Map.Strict` 统计频率
- 会用 `Data.Set.member` 做存在性判断
- 会处理字符串计数和分组
- 知道什么时候要选严格 Map，避免空间变大

小模板：

```haskell
import qualified Data.Map.Strict as Map

freq :: Ord a => [a] -> Map.Map a Int
freq = foldl (\mp x -> Map.insertWith (+) x 1 mp) Map.empty
```

题目：

- [ ] [AtCoder ABC155C - Poll](https://atcoder.jp/contests/abc155/tasks/abc155_c)  
  练习点：字符串频率统计，找最大出现次数。
- [ ] [AtCoder ABC137C - Green Bin](https://atcoder.jp/contests/abc137/tasks/abc137_c)  
  练习点：把字符串排序作为 key，统计组合数。
- [ ] [AtCoder ABC170C - Forbidden List](https://atcoder.jp/contests/abc170/tasks/abc170_c)  
  练习点：`Set.member`，从候选答案里找最近值。
- [ ] [AtCoder ABC071B - Not Found](https://atcoder.jp/contests/abc071/tasks/abc071_b)  
  练习点：字符集合，找第一个没出现的小写字母。
- [ ] [Kattis - I've Been Everywhere, Man](https://open.kattis.com/problems/everywhere)  
  练习点：多组数据，城市名去重。

## 阶段 6：递归、扫描与入门 DP

目标：

- 会把状态转移写成列表递推
- 会用 `scanl` / 递归维护前缀状态
- 会写最基础的动态规划
- 开始注意 `Int`、`Integer`、数组和列表的选择

小模板：

```haskell
main :: IO ()
main = do
    (_:hs) <- map read . words <$> getContents :: IO [Int]
    print (solve hs)

solve :: [Int] -> Int
solve (a:b:rest) = go rest 0 (abs (b - a)) a b
  where
    go [] x y _ _ = min x y
    go (c:cs) x y prev cur =
        let z = min (y + abs (c - cur)) (x + abs (c - prev))
        in go cs y z cur c
solve _ = 0
```

题目：

- [ ] [AtCoder Educational DP Contest A - Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a)  
  练习点：一维 DP，状态只依赖前两项。
- [ ] [AtCoder Educational DP Contest B - Frog 2](https://atcoder.jp/contests/dp/tasks/dp_b)  
  练习点：一维 DP，向前看最多 `k` 步。
- [ ] [AtCoder Educational DP Contest C - Vacation](https://atcoder.jp/contests/dp/tasks/dp_c)  
  练习点：三状态 DP，不能连续选同一类。
- [ ] [Kattis - Speed Limit](https://open.kattis.com/problems/speedlimit)  
  练习点：多段累计，维护上一段时间。
- [ ] [Kattis - Pot](https://open.kattis.com/problems/pot)  
  练习点：按数字最后一位拆指数，累加幂。

## 后续扩展方向

这 30 题做完后，可以继续扩展三条线：

- AtCoder ABC C/D：练更完整的算法建模。
- Educational DP Contest：系统练 DP。
- Kattis 短题：补充字符串、格式化输出和多组输入解析。

如果后续把某些题写进本仓库题解，可以再把外链逐步替换成 `[[problem: oj,pid]]` 形式。
