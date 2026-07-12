---
oj: "luogu"
problem_id: "P7772"
title: "[COCI 2009/2010 #2] FAKTOR"
description: "把上取整不等式化成 A * (I - 1) + 1。"
difficulty: "入门"
date: 2026-06-18 20:21
toc: true
tags: ["数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P7772
---

[[TOC]]

### 题意

给出 `A` 和 `I`，求最小的正整数 `N`，使得 `ceil(N / A) >= I`。

### 思路

先看一个可以直接验证想法的朴素解：

可以从 `N = 1` 开始往上枚举，找到第一个满足 `ceil(N / A) >= I` 的数。

@include-code(./brute.cpp, cpp)

不过这题其实可以直接化公式。
因为

```text
ceil(N / A) >= I
```

等价于

```text
N > A * (I - 1)
```

所以最小的正整数解就是 `A * (I - 1) + 1`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

`main.cpp` 是直接公式，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

把上取整条件改写成严格不等式后，答案就变成了一个非常直接的整数公式。
