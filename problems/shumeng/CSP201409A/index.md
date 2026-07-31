---
oj: "shumeng"
problem_id: "CSP201409A"
title: "相邻数对"
description: "排序后检查相邻元素是否相差 1，直接统计所有满足条件的数对。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["排序", "枚举"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201409A
---

[[TOC]]

### 题意

给定 $n$ 个互不相同的非负整数，统计其中有多少对数值正好相差 $1$。

### 思路

先看直接枚举所有下标对的做法：

@include-code(./brute.cpp, cpp)

它需要 $O(n^2)$ 次比较。由于数值只关心相差 $1$，可以先排序。排序后，若两个数值相差 $1$，它们一定在有序数组中相邻；反之，有序数组中相邻元素差为 $1$ 时，这一对就是答案中的合法数对。

因此从左到右检查 `numbers[i] - numbers[i-1] == 1` 即可。题目保证数值互不相同，所以不会出现重复计数。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序时间复杂度为 $O(n\log n)$，扫描复杂度为 $O(n)$，总时间复杂度为 $O(n\log n)$；额外空间复杂度为 $O(n)$。

### 总结

当目标只由数值大小关系决定时，排序可以把任意位置的配对关系转化为相邻位置的局部检查。这里“相差 1”的数在排序后必然相邻，因此只需线性扫描一次。
