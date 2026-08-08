---
oj: "luogu"
problem_id: "P7257"
title: "[COCI 2009/2010 #3] FILIP"
description: "把两个三位数翻转后直接比较大小。"
difficulty: "入门"
date: 2026-06-18 20:18
toc: true
tags: ["模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P7257
---

[[TOC]]

### 题意

给出两个三位正整数，把它们分别翻转后，输出翻转结果中较大的那个。

### 思路

先看一个可以直接验证想法的朴素解：

这题直接按题意实现即可。
对每个数不断取个位，把个位接到新数末尾，就能得到翻转后的结果。

@include-code(./brute.cpp, cpp)

因为输入规模只有两个三位数，所以不需要任何优化。
把翻转过程封装成一个小函数，代码最清楚。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个数最多处理 3 位，时间复杂度是 $O(1)$，空间复杂度也是 $O(1)$。

### 总结

这题就是按位翻转和比较大小，照着定义写就行。
