---
oj: "atcoder"
problem_id: "practice_1"
title: "PracticeA - Welcome to AtCoder"
description: "按题意读入三个整数和一个字符串，输出整数和与字符串；重点练习 Haskell 的输入解析。"
difficulty: "入门"
date: 2026-07-09 17:55
toc: true
tags: ["模拟", "haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abs/tasks/practice_1
---

[[TOC]]

### 题意

输入三行：

- 第一行是一个整数 `a`；
- 第二行是两个整数 `b c`；
- 第三行是一个字符串 `s`。

要求输出：

```text
a + b + c s
```

也就是先输出三个整数的和，再输出一个空格，最后输出字符串 `s`。

### 思路

这题没有复杂算法，核心是把输入按格式读出来：

1. `readLn` 读取第一行整数 `a`。
2. `getLine` 读取第二行 `"b c"`。
3. `words` 把这一行按空白字符拆成字符串列表。
4. `map read` 把字符串列表转成整数列表。
5. 再读入第三行字符串，拼接输出。

这道题不需要暴力解或算法优化。它在这里的学习目标是 Haskell 输入解析，重点是理解下面这个表达式如何把一行字符串变成两个整数：

```haskell
map read . words <$> getLine
```

#### `<$>` 的作用

`<$>` 是 `fmap` 的中缀写法：

```haskell
(<$>) :: Functor f => (a -> b) -> f a -> f b
```

可以先把它理解成：“把一个普通函数放进某个上下文里执行”。

在 `IO` 里，`f <$> getLine` 的意思是：

1. 先执行 `getLine`，得到一行字符串；
2. 再把函数 `f` 作用到这个字符串上；
3. 整体结果仍然在 `IO` 里。

例如：

```haskell
main :: IO ()
main = do
    n <- length <$> getLine
    print n
```

如果输入：

```text
abcd
```

那么 `getLine` 得到 `"abcd"`，`length` 把它变成 `4`，所以最终输出：

```text
4
```

这段代码等价于：

```haskell
main :: IO ()
main = do
    line <- getLine
    let n = length line
    print n
```

所以 `<$>` 可以让我们少写一个临时变量。

#### `map read . words <$> getLine` 怎么执行

先看这句话：

```haskell
[b, c] <- map read . words <$> getLine
```

这里涉及三个重要优先级：

| 写法 | 含义 | 优先级 |
| --- | --- | --- |
| 函数应用，也就是空格 | 例如 `map read` | 最高 |
| `.` | 函数组合，先执行右边，再执行左边 | `infixr 9` |
| `<$>` | `fmap` 的中缀写法 | `infixl 4` |

所以：

```haskell
map read . words <$> getLine
```

会被解析成：

```haskell
((map read) . words) <$> getLine
```

而不是：

```haskell
map read . (words <$> getLine)
```

再一步一步看类型和执行顺序。

第一步，函数应用优先级最高：

```haskell
map read
```

它先形成一个新函数：

```haskell
map read :: Read a => [String] -> [a]
```

第二步，`.` 组合两个函数：

```haskell
(map read) . words
```

其中：

```haskell
words :: String -> [String]
map read :: Read a => [String] -> [a]
```

组合后得到：

```haskell
(map read . words) :: Read a => String -> [a]
```

它等价于：

```haskell
\line -> map read (words line)
```

第三步，`<$>` 把这个函数作用到 `getLine` 读出来的内容上：

```haskell
(map read . words) <$> getLine
```

因为：

```haskell
getLine :: IO String
```

所以整体类型是：

```haskell
(map read . words) <$> getLine :: Read a => IO [a]
```

如果这一行输入是：

```text
2 3
```

执行过程就是：

```text
getLine
  -> "2 3"

words "2 3"
  -> ["2", "3"]

map read ["2", "3"]
  -> [2, 3]
```

最后：

```haskell
[b, c] <- (map read . words) <$> getLine
```

把 `[2, 3]` 解构成：

```haskell
b = 2
c = 3
```

这里的 `[b, c]` 要求列表里正好有两个元素，正好对应题目第二行的两个整数。

### 代码

当前提交代码文件是 `main.rs`，内容为 Haskell：

@include-code(./main.rs, haskell)

### 复杂度

只读取常数个输入值并输出一行。

- 时间复杂度：$O(|s|)$，其中 $|s|$ 是字符串长度。
- 空间复杂度：$O(|s|)$，主要来自读入的字符串。

### 总结

这题的算法部分很简单，重点是 Haskell 输入解析：

- `.` 表示函数组合，`f . g` 等价于 `\x -> f (g x)`；
- `<$>` 是 `fmap`，在 `IO` 中可以理解成“读入后顺手做一次转换”；
- `map read . words <$> getLine` 的真实结构是 `((map read) . words) <$> getLine`；
- 对输入行 `"2 3"`，它会依次得到 `["2","3"]` 和 `[2,3]`。
