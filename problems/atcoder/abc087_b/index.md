---
oj: "atcoder"
problem_id: "abc087_b"
title: "ABC087B - Coins"
description: "枚举三种硬币分别选多少枚，用 Haskell 列表推导统计总金额等于目标值的方案数。"
difficulty: "入门"
date: 2026-07-10 10:49
toc: true
tags: ["枚举", "haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abs/tasks/abc087_b
---

[[TOC]]

### 题意

有 `A` 枚 500 日元硬币，`B` 枚 100 日元硬币，`C` 枚 50 日元硬币。
问有多少种选法，使得总金额正好等于 `X`。

同一种硬币之间不区分，只关心每种硬币分别选了多少枚。
也就是说，一个方案可以表示成三元组 `(x, y, z)`：

- `x` 表示选了多少枚 500 日元硬币；
- `y` 表示选了多少枚 100 日元硬币；
- `z` 表示选了多少枚 50 日元硬币。

这个方案合法，当且仅当：

$$
0 \leqslant x \leqslant A,\quad
0 \leqslant y \leqslant B,\quad
0 \leqslant z \leqslant C
$$

并且：

$$
500x + 100y + 50z = X
$$

### 思路

这题的数据很小，`A, B, C` 都不超过 `50`，所以可以直接枚举三种硬币各选多少枚。

Haskell 的列表推导很适合表达这种“枚举所有选择，再筛选合法方案”的过程：

```haskell
main :: IO ()
main = do
    input <- getContents
    let [a, b, c, target] = map read (words input) :: [Int]
    let ans = length
            [ ()
            | x <- [0..a]
            , y <- [0..b]
            , z <- [0..c]
            , x * 500 + y * 100 + z * 50 == target
            ]
    print ans
```

这里 `[0..a]` 表示 500 日元硬币可以选 `0` 到 `a` 枚。
后面的 `x <- [0..a]`、`y <- [0..b]`、`z <- [0..c]` 会枚举所有三元组 `(x, y, z)`。
最后一行条件 `x * 500 + y * 100 + z * 50 == target` 只保留总金额等于目标值的方案。

注意列表里面放的是 `()`，因为我们并不关心方案的具体内容，只关心合法方案有多少个。
每找到一个合法方案，就产生一个 `()`，最后用 `length` 数一数即可。

还可以利用一个小观察：枚举了 500 日元和 100 日元硬币后，剩下的钱必须全部由 50 日元硬币组成。
这样可以少枚举一层：

```haskell
main :: IO ()
main = do
    input <- getContents
    let [a, b, c, target] = map read (words input) :: [Int]
    let ans = length
            [ ()
            | x <- [0..a]
            , y <- [0..b]
            , let rest = target - x * 500 - y * 100
            , rest >= 0
            , rest `mod` 50 == 0
            , let z = rest `div` 50
            , z <= c
            ]
    print ans
```

这两个写法都正确。
第一种更直观，直接对应“三种硬币都枚举”；第二种稍微利用了金额关系，枚举次数更少。
作为入门练习，优先掌握第一种列表推导写法。

### 代码

@include-code(./main.hs, haskell)

### 复杂度

正式代码枚举 `x`、`y`、`z` 三层循环，时间复杂度为 $O(ABC)$。
更准确地说是 $O((A+1)(B+1)(C+1))$。

除了输入数组和枚举过程中产生的列表外，没有额外复杂数据结构。
空间复杂度可以理解为 $O(ABC)$，因为这里用列表推导构造了合法方案列表再取 `length`。
在本题约束下，最多约 $51^3$ 个枚举项，完全可以接受。

### 总结

这题适合用来练习 Haskell 的列表推导。
把每种硬币的数量范围写成生成器，再把金额相等写成过滤条件，代码就很接近题意本身。

`[ () | 条件 ]` 是一个常用计数技巧：当我们只需要统计满足条件的方案数，而不需要保存方案内容时，就可以用 `()` 作为占位值。
