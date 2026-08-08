---
oj: "luogu"
problem_id: "P1516"
title: "青蛙的约会"
description: "把两只青蛙第 t 次跳跃后位置相等写成 (m-n)t≡y-x(mod L)，再用扩展欧几里得求最小非负解；若 gcd(m-n,L) 不能整除 y-x，则无解。"
difficulty: "普及+/提高"
date: 2026-06-20 05:32
toc: true
tags: ["数论"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1516
---

[[TOC]]

### 题意

两只青蛙分别从位置 `x`、`y` 出发，每次分别向前跳 `m`、`n` 米。  
整条环形纬线总长是 `L`。

问它们最少跳多少次会落到同一个位置。  
如果永远碰不到，输出 `Impossible`。

### 思路

先看一个最直接的小数据暴力：

@include-code(./brute.cpp, cpp)

暴力就是直接模拟每一次跳跃，看两只青蛙是否相遇。  
这个思路最贴题意，但 `L` 很大，不能真模拟到天荒地老。

关键观察是：  
如果它们在第 `t` 次跳跃后相遇，那么一定满足：

`x + m t ≡ y + n t (mod L)`

整理一下就是：

`(m-n)t ≡ y-x (mod L)`

这已经变成了标准的一次同余方程。

再把它写成整数方程：

`(m-n)t + Lk = y-x`

这正是扩展欧几里得处理的形式。

若设：

- `a = m-n`
- `c = y-x`

则方程：

`a t ≡ c (mod L)`

有解的充要条件是：

- `gcd(a, L)` 能整除 `c`

如果不能整除，答案就是 `Impossible`。  
如果能整除，就用 exgcd 求出一组解，再把 `t` 调整到最小非负值即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

扩展欧几里得时间复杂度：

- $O(log L)$

空间复杂度：

- $O(1)$

### 总结

这题最核心的一步，就是把“第几次相遇”翻译成同余方程：

- `(m-n)t ≡ y-x (mod L)`

一旦写出这个式子，后面就是一次同余方程模板题了。
