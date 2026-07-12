---
oj: "luogu"
problem_id: "P2669"
title: "[NOIP 2015 普及组] 金币"
description: "按工资段分组累加，每段连续 x 天每天发 x 枚金币。"
difficulty: "入门"
date: 2026-06-18 20:48
toc: true
tags: ["模拟", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2669
---

[[TOC]]

### 题意

第 1 段连续 1 天每天发 1 枚金币，第 2 段连续 2 天每天发 2 枚金币，第 3 段连续 3 天每天发 3 枚金币，依次类推。
给出 `k`，求前 `k` 天一共能得到多少金币。

### 思路

先看一个可以直接验证想法的朴素解：

按天模拟即可，记录当前每天发多少金币，以及这个数值已经持续了多少天。

@include-code(./brute.cpp, cpp)

不过这题更适合按“段”来算。
如果当前段是数值 `x`，那么这一段最多持续 `x` 天，每天都发 `x` 枚金币。
所以这一段的贡献就是：

```text
实际使用天数 * x
```

这样就可以一段一段累加，直到前 `k` 天全部覆盖完。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

循环次数大约是 $O(\sqrt{k})$，空间复杂度是 $O(1)$。

### 总结

这题的关键是把逐天发工资改写成分段累加。
