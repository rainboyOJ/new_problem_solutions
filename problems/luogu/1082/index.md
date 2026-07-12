---
oj: "luogu"
problem_id: "P1082"
title: "[NOIP 2012 提高组] 同余方程"
description: "把 ax≡1(mod b) 改写成 ax+by=1，用扩展欧几里得求出一组解，其中 x 在模 b 意义下的最小正值就是答案。"
difficulty: "普及+/提高"
date: 2026-06-20 05:28
toc: true
tags: ["数论", "逆元"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1082
---

[[TOC]]

### 题意

求同余方程：

`a x ≡ 1 (mod b)`

的最小正整数解。

### 思路

先看一个最直接的小数据暴力：

@include-code(./brute.cpp, cpp)

暴力做法就是从 `1` 开始枚举 `x`，直到找到：

`(a * x) % b == 1`

这个思路最贴题意，但 `b` 最大到 `2e9`，显然不能枚举。

关键观察是，把题目改写一下：

`a x ≡ 1 (mod b)`

等价于：

`a x + b y = 1`

这正是扩展欧几里得处理的形式。

因为当 `gcd(a, b) = 1` 时，扩展欧几里得能求出一组整数解：

- `x`
- `y`

满足：

`a x + b y = 1`

那就说明：

`a x ≡ 1 (mod b)`

于是这个 `x` 就是 `a` 在模 `b` 下的一个逆元。  
最后把它调整到最小正整数范围：

- `(x % b + b) % b`

这就是答案。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

扩展欧几里得的时间复杂度是：

- $O(log b)$

空间复杂度：

- $O(1)$

### 总结

这题本质上就是一道模逆元模板题。

一旦看到：

- `a x ≡ 1 (mod b)`

就要想到把它改写成：

- `a x + b y = 1`

然后直接用 exgcd 求一组解。
