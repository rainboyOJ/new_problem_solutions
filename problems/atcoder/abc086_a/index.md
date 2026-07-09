---
oj: "atcoder"
problem_id: "abc086_a"
title: "ABC086A - Product"
description: "读取两个整数，判断乘积奇偶；用 Haskell 练习基础输入解析和字符串输出。"
difficulty: "入门"
date: 2026-07-09 19:36
toc: true
tags: ["模拟", "haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abs/tasks/abc086_a
---

[[TOC]]

### 题意

给定两个正整数 `a` 和 `b`，判断它们的乘积 `a * b` 是奇数还是偶数。

如果乘积是奇数，输出 `Odd`；如果乘积是偶数，输出 `Even`。

### 思路

这题没有复杂算法，只需要观察乘积的奇偶性：两个数相乘时，只要其中一个数是偶数，乘积就是偶数；只有两个数都是奇数时，乘积才是奇数。

可以用下面这张表理解：

| `a` 的奇偶 | `b` 的奇偶 | `a * b` 的奇偶 |
| --- | --- | --- |
| 奇数 | 奇数 | 奇数 |
| 奇数 | 偶数 | 偶数 |
| 偶数 | 奇数 | 偶数 |
| 偶数 | 偶数 | 偶数 |

代码里直接计算 `a * b` 再取模即可：

```haskell
let c = a * b
let res = if c `mod` 2 == 0 then "Even" else "Odd"
```

#### Haskell 读入

这一行负责把输入中的两个整数读出来：

```haskell
[a,b] <- map read . words <$> getContents :: IO [Int]
```

它可以按下面的顺序理解：

1. `getContents` 读取所有标准输入，类型是 `IO String`。
2. `<$>` 把右边 `IO String` 里的字符串取出来后，交给左边的函数处理。
3. `words` 把输入字符串按空白字符拆成 `["3", "4"]` 这样的列表。
4. `map read` 把字符串列表转成整数列表 `[3, 4]`。
5. `[a,b] <- ...` 把两个整数分别绑定到 `a` 和 `b`。

这里的 `:: IO [Int]` 是类型标注，用来告诉 Haskell：读出来的列表元素应该解析成 `Int`。

#### WA 点：`print` 和 `putStrLn`

注意输出字符串时要用 `putStrLn res`。如果写成 `print res`，Haskell 会按照 `Show String` 的形式输出，结果会变成 `"Even"` 或 `"Odd"`，多出双引号，提交会 WA。

也就是说：

```haskell
putStrLn "Even"
```

输出：

```text
Even
```

而：

```haskell
print "Even"
```

输出：

```text
"Even"
```

本题要求没有双引号，所以必须使用 `putStrLn`。

### 代码

@include-code(./main.hs, haskell)

### 复杂度

只读取两个整数并做一次乘法和取模。

- 时间复杂度：$O(1)$。
- 空间复杂度：$O(1)$。

### 总结

这题适合作为 Haskell 输入输出练习。判断逻辑是“乘积为偶数当且仅当至少有一个因子为偶数”，实现时可以直接计算乘积再判断。真正容易踩坑的是输出函数：`putStrLn` 输出裸字符串，`print` 会额外带上双引号。
