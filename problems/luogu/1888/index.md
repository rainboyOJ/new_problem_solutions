---
oj: "luogu"
problem_id: "P1888"
title: "三角函数"
description: "勾股数中较小锐角的正弦值等于最短边除以斜边，排序后约分输出即可。"
difficulty: "入门"
date: 2026-07-06 20:42
toc: true
tags: ["数学", "最大公约数", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1888
---

[[TOC]]

### 题意

给出一组三个勾股数，要求输出较小锐角的正弦值，格式为最简分数。

### 思路

先看一个直接做法：

@include-code(./brute.cpp, cpp)

直角三角形里：

- 最长边是斜边；
- 较小锐角对应的对边是最短边；
- 正弦值等于 `对边 / 斜边`。

所以只需要把三个数排序：

```text
最短边 / 最长边
```

然后用最大公约数约分即可。

例如 `3,4,5` 中，较小锐角的正弦值是 `3/5`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：`O(log V)`，主要来自求最大公约数
- 空间复杂度：`O(1)`

### 总结

这题的关键是先确定哪条边是“较小锐角的对边”。排序后最短边除以最长边，再约分输出。
