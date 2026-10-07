---
oj: "roj"
problem_id: "1623"
title: "「一本通 6.2 练习 4」Sherlock and His Girlfriend"
description: "冲突边只存在于质数与它的倍数之间，质数涂 1、合数涂 2 即为最优，答案用一次埃氏筛求出。"
difficulty: "普及-"
date: 2026-09-30 22:43
updated: 2026-10-07 13:50
toc: true
tags: ["数论", "素数", "筛法", "二分图染色", "构造", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1151"
    reason: "B 的 prime_table 直接复用 A 教的埃氏筛「p 从 p^2 起整片划掉倍数」，只是筛区间换成价值上界 n+1，再叠加 A 未教的「冲突边必是质数—合数、二分染色数退化为 1 或 2」这一图论观察，属在 A 的筛法台阶上叠加额外构造流程。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1623
---

[[TOC]]

## 题目描述

Sherlock 买了 $n$ 件珠宝，第 $i$ 件的价值是 $i+1$，即价值分别为 $2,3,4,\cdots,n+1$。他要给珠宝染色，使得一件珠宝的价值是另一件的质因子时，两件珠宝颜色不同，并最小化使用的颜色数。
**输入**：一行一个整数 $n$。**输出**：第一行一个整数 $k$ 表示最少染色数；第二行 $n$ 个整数表示第 $1$ 到第 $n$ 件珠宝的颜色。若有多种答案，输出任意一种。
**样例输入**：`3`。
**样例输出**：

```
2
1 1 2
```

数据范围：$1 \leqslant n \leqslant 10^5$。
## 思路

一件珠宝是质因子时它本身必是质数，而被整除的一方必是合数，所以冲突只发生在「质数—合数」之间：质数全涂颜色 1、合数全涂颜色 2 即合法。$n \leqslant 2$ 时价值只有 $2,3$，没有冲突边，答案为 1；$n \geqslant 3$ 时 $2$ 与 $4$ 冲突，答案必为 2。因此只需用埃氏筛标记 $[2, n+1]$ 内的质数即可。
## 参考代码

@include-code(./main.cpp, cpp)
