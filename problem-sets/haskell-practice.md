---
title: "Haskell 语法特性 OJ 入门题单"
description: "保留原 Haskell OJ 入门题目，按 Haskell 语法特性重新组织练习路径。"
---

# Haskell 语法特性 OJ 入门题单

这份题单保留原来的 30 道题，但学习主线从“算法阶段”改成“Haskell 语法特性”。目标不是把题写得最短，而是通过短题反复见到 Haskell 在 OJ 中最常用的写法。

每题复盘时重点看三件事：

1. 这题用到了哪些 Haskell 语法或标准库函数？
2. 输入解析那一行是怎么一步一步执行的？
3. 能不能写出一个清楚版本，再尝试写得更 Haskell 一点？

建议每题至少保留两个版本的理解：

```text
直白版本：变量多一点，步骤拆开，便于确认含义。
熟练版本：使用 <$>、函数组合、列表函数或标准库，让代码更紧凑。
```

## 阶段 1：程序入口、do 与基础 IO

目标：

- 理解 `main :: IO ()`
- 理解 `do` 块里的执行顺序
- 区分 `<-` 绑定 IO 结果和 `let` 绑定普通表达式
- 熟悉 `print`、`putStrLn`、字符串拼接和 `if ... then ... else ...`

小模板：

```haskell
main :: IO ()
main = do
    input <- getLine
    let n = read input :: Int
    print (n + 1)
```

题目：

- [ ] [[problem: atcoder,practice_1]]
  练习点：`do` 块中连续读取输入，`<-` 取出 IO 结果，`let` 计算普通值，`putStrLn` 拼接输出。
- [ ] [[problem: kattis,hello]]
  练习点：最小 `main :: IO ()` 程序，`putStrLn` 输出固定字符串。
- [ ] [[problem: kattis,r2]]
  练习点：读入两个整数，使用模式匹配 `[r1, s]` 拆列表，再用 `print` 输出表达式。
- [ ] [[problem: atcoder,abc086_a]]
  练习点：`if ... then ... else ...` 表达式，`odd` / `even` 判断，`read` 后指定整数类型。

## 阶段 2：输入解析、<$>、函数组合与类型标注

目标：

- 熟悉 `getContents`、`getLine`、`lines`、`words`
- 理解 `map read . words <$> getContents`
- 理解 `<$>`、`.`、`$` 在输入解析中的作用
- 学会在解析处写类型标注，避免 `read` 类型不明确

小模板：

```haskell
main :: IO ()
main = do
    xs <- map read . words <$> getContents :: IO [Int]
    print (sum xs)
```

这行可以按下面顺序理解：

```text
getContents                 :: IO String
words                       :: String -> [String]
map read                    :: [String] -> [Int]
map read . words            :: String -> [Int]
map read . words <$> input  :: IO [Int]
```

题目：

- [ ] [[problem: atcoder,abc081_a]]
  练习点：`getLine` 读取一行字符串，`filter (== '1')` 过滤字符，`length` 统计结果。
- [ ] [[problem: atcoder,abc081_b]]
  练习点：`map read . words <$> getContents` 读整数列表，用递归或 `takeWhile` 反复处理列表。
- [ ] [[problem: atcoder,abc083_b]]
  练习点：`show` 把数字转字符串，`digitToInt` 处理字符数字，函数组合写出数位和。
- [ ] [[problem: kattis,nastyhacks]]
  练习点：`lines` / `words` 处理多组输入，把每一行映射成一个判断结果。
- [ ] [Kattis - QALY](https://open.kattis.com/problems/qaly)
  练习点：`read` 解析 `Double`，把扁平数字列表按两两一组处理，再用 `sum` 汇总。

## 阶段 3：列表、字符串与列表推导式

目标：

- 熟悉 `String` 本质是 `[Char]`
- 熟悉 `map`、`filter`、`length`、`reverse`
- 会用列表推导式表达枚举
- 会用 `takeWhile`、`dropWhile`、字符串分割和反转处理短题

小模板：

```haskell
main :: IO ()
main = do
    xs <- map read . words <$> getContents :: IO [Int]
    print (length [x | x <- xs, x < 0])
```

题目：

- [ ] [AtCoder ABC087B - Coins](https://atcoder.jp/contests/abs/tasks/abc087_b)
  练习点：列表推导式 `[() | ...]` 表示多重枚举，用 `length` 统计满足条件的方案数。
- [ ] [[problem: atcoder,abc122_b]]
  练习点：把字符串看成字符列表，使用 `takeWhile`、`dropWhile` 或递归统计连续合法段。
- [ ] [Kattis - Autori](https://open.kattis.com/problems/autori)
  练习点：字符串分段，取每段首字符，练习 `head`、模式匹配或手写 split。
- [ ] [Kattis - Filip](https://open.kattis.com/problems/filip)
  练习点：`reverse` 反转数字字符串，字符串比较和 `read` 比较两种写法都可以练。
- [ ] [Kattis - Cold-puter Science](https://open.kattis.com/problems/cold)
  练习点：`filter (< 0)` 过滤列表，`length` 统计数量，写出表达式式解法。

## 阶段 4：模式匹配、递归、where 与 case

目标：

- 用模式匹配拆列表和字符串
- 会写递归函数的终止条件和递推分支
- 熟悉 `where` 放局部函数
- 在多分支判断时比较 `if`、guards 和 `case`

小模板：

```haskell
solve :: [Int] -> Int
solve [] = 0
solve (x:xs)
    | x < 0     = 1 + solve xs
    | otherwise = solve xs
```

题目：

- [ ] [[problem: atcoder,arc065_a]]
  练习点：字符串递归匹配，`isPrefixOf` / `stripPrefix`，从后往前消去时练习函数拆分。
- [ ] [[problem: atcoder,abc143_c]]
  练习点：用递归或 `group` 压缩相邻相同字符，比较手写递归和标准库写法。
- [ ] [Kattis - Speed Limit](https://open.kattis.com/problems/speedlimit)
  练习点：递归处理一组组数据，维护上一段时间，练习局部状态参数。
- [ ] [Kattis - Pot](https://open.kattis.com/problems/pot)
  练习点：拆数字最后一位，使用 `div` / `mod` 或字符串模式匹配处理指数。

## 阶段 5：排序、元组、sortOn 与 Down

目标：

- 熟悉 `sort` 和 `sortOn`
- 用元组作为排序 key
- 用 `Down` 表示降序
- 用 `zip [1..]` 保留原始编号

小模板：

```haskell
import Data.List (sortOn)
import Data.Ord (Down(..))

main :: IO ()
main = do
    let xs = [("tokyo", 80, 1), ("osaka", 90, 2)]
    print (sortOn (\(city, score, _) -> (city, Down score)) xs)
```

题目：

- [ ] [[problem: atcoder,abc042_b]]
  练习点：`lines` 读取多行字符串，`sort` 排序字符串列表，`concat` 拼接结果。
- [ ] [[problem: atcoder,abc088_b]]
  练习点：降序排序可以用 `reverse . sort`，也可以用 `sortOn Down`；再配合下标奇偶分组。
- [ ] [[problem: atcoder,abc128_b]]
  练习点：`zip [1..]` 保留原始编号，`sortOn` 使用元组排序键，`Down` 实现分数降序，`mapM_ print` 批量输出。

## 阶段 6：Set、Map.Strict、计数与查找

目标：

- 会用 `Data.Set` 去重和查找
- 会用 `Data.Map.Strict` 统计频率
- 理解 `insertWith (+)` 的计数写法
- 区分普通列表扫描和集合 / 映射结构

小模板：

```haskell
import qualified Data.Map.Strict as Map

freq :: Ord a => [a] -> Map.Map a Int
freq = foldl (\mp x -> Map.insertWith (+) x 1 mp) Map.empty
```

题目：

- [ ] [[problem: atcoder,abc085_b]]
  练习点：`Set.fromList` 去重，`Set.size` 统计不同元素数量。
- [ ] [[problem: atcoder,abc155_c]]
  练习点：用 `Map.Strict` 统计字符串频率，找最大值，再输出所有达到最大频率的 key。
- [ ] [AtCoder ABC137C - Green Bin](https://atcoder.jp/contests/abc137/tasks/abc137_c)
  练习点：把 `sort word` 当作 Map key，统计同类字符串数量，再计算组合数。
- [ ] [AtCoder ABC170C - Forbidden List](https://atcoder.jp/contests/abc170/tasks/abc170_c)
  练习点：`Set.member` 做禁用值查询，从候选列表里找距离最近的答案。
- [ ] [AtCoder ABC071B - Not Found](https://atcoder.jp/contests/abc071/tasks/abc071_b)
  练习点：字符集合，`['a'..'z']` 生成候选字符，`find` 找第一个没出现的字符。
- [ ] [Kattis - I've Been Everywhere, Man](https://open.kattis.com/problems/everywhere)
  练习点：多组字符串去重，练习每组构造一个 `Set`，避免组间状态混在一起。

## 阶段 7：fold、scan 与入门 DP

目标：

- 熟悉 `foldl'` 维护累计状态
- 熟悉 `scanl` 生成前缀状态
- 把 DP 状态写成列表递推或局部递归
- 开始注意惰性求值下的空间问题

小模板：

```haskell
import Data.List (foldl')

sumStrict :: [Int] -> Int
sumStrict = foldl' (+) 0
```

题目：

- [ ] [AtCoder Educational DP Contest A - Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a)
  练习点：用递归参数或列表递推维护前两个 DP 值，理解状态只依赖前两项。
- [ ] [AtCoder Educational DP Contest B - Frog 2](https://atcoder.jp/contests/dp/tasks/dp_b)
  练习点：每个状态查看前 `k` 项，体会列表下标访问不方便时为什么需要数组。
- [ ] [AtCoder Educational DP Contest C - Vacation](https://atcoder.jp/contests/dp/tasks/dp_c)
  练习点：三元组表示当天三种状态，使用 `foldl'` 逐天更新 DP。

## 后续扩展方向

这 30 题做完后，可以按语法继续扩展：

- 输入解析：多练 `ByteString`，解决大输入性能问题。
- 数据结构：继续练 `Map.Strict`、`IntMap`、`Set`、数组。
- 表达能力：每题写一个直白版，再写一个使用函数组合或标准库的版本。
- 算法进阶：从 Educational DP、ABC C/D 继续把 Haskell 写法和算法模型结合起来。

如果后续把某些外链题写进本仓库题解，可以再把外链逐步替换成 `[[problem: oj,pid]]` 形式。
