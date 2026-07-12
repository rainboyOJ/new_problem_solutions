---
oj: "luogu"
problem_id: "P1035"
title: "[NOIP 2002 普及组] 级数求和"
description: "累加调和级数，直到前缀和第一次超过 k。"
difficulty: "入门"
date: 2026-06-18 20:24
toc: true
tags: ["模拟", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1035
---

[[TOC]]

### 题意

给出一个整数 `k`，求最小的 `n`，使得：

```text
1 + 1/2 + 1/3 + ... + 1/n > k
```

### 思路

先看一个可以直接验证想法的朴素解：

从 `n = 1` 开始累加前缀和，直到它第一次超过 `k`。

@include-code(./brute.cpp, cpp)

因为 `k <= 15`，这个直接模拟已经足够。
这题的关键只有一个：题目要的是“严格大于” `k`，所以停止条件必须写成 `sum > k`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度可以看作 $O(n)$，其中 `n` 是答案对应的项数。
空间复杂度是 $O(1)$。

### 总结

这题就是不断累加调和级数，第一次超过 `k` 时，当前项数就是答案。
