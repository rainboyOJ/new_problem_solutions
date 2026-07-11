---
oj: "luogu"
problem_id: "P1887"
title: "乘积最大3"
description: "把 N 尽量平均拆成 M 份，商和余数直接决定最优方案。"
difficulty: "普及-"
date: 2026-06-18 20:42
toc: true
tags: ["数学", "贪心"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1887
---

[[TOC]]

### 题意

把整数 `N` 拆成 `M` 个正整数，要求它们的和等于 `N`，并且乘积尽可能大。
如果有多种最优方案，输出字典序最小的一种。

### 思路

先看一个可以直接验证想法的朴素解：

小数据时可以枚举所有非降序拆分方案，计算乘积并选最优。

@include-code(./brute.cpp, cpp)

关键结论是：如果两个数相差至少 2，那么把大的减 1、小的加 1，总和不变，但乘积会更大。
所以最优方案一定是“尽量平均分”的。

设：

```text
N = M * q + r
```

那么答案就是：

- `M - r` 个 `q`
- `r` 个 `q + 1`

把小的放前面，也正好满足字典序最小。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

只需要输出 `M` 个数，所以时间复杂度是 $O(M)$，空间复杂度是 $O(1)$。

### 总结

这题的关键不是搜索，而是发现“总和固定时，数越平均乘积越大”。
