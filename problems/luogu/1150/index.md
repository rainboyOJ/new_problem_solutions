---
oj: "luogu"
problem_id: "P1150"
title: "Peter 的烟"
description: "不断用烟蒂兑换新烟，累加总烟数直到不足以换。"
difficulty: "入门"
date: 2026-06-18 20:27
toc: true
tags: ["模拟", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1150
---

[[TOC]]

### 题意

Peter 一开始有 `n` 根烟。
每吸完一根烟会留下一个烟蒂，`k` 个烟蒂可以换一根新烟。
求最终一共能吸到多少根烟。

### 思路

先看一个可以直接验证想法的朴素解：

直接模拟兑换过程即可。
初始答案就是 `n`，然后只要当前烟蒂数不少于 `k`，就继续兑换。

@include-code(./brute.cpp, cpp)

每轮兑换时，`n / k` 根新烟会带来 `n / k` 个新烟蒂，和剩下的 `n % k` 个烟蒂合在一起，就是下一轮的烟蒂数。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每一轮烟蒂数都会减少，所以循环次数很少。
时间复杂度可以看作 $O(log_k n)$，空间复杂度是 $O(1)$。

### 总结

这题的核心就是把“烟蒂换烟”写成一个循环更新公式。
