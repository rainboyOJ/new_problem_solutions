---
oj: "luogu"
problem_id: "P1177"
title: "【模板】排序"
description: "读入所有数字后直接按从小到大排序输出，重点是理解排序结果的有序性。"
difficulty: "普及-"
date: 2026-07-06 20:42
toc: true
tags: ["排序", "模板题"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1177
---

[[TOC]]

### 题意

给出 `n` 个整数，把它们从小到大排序后输出。

### 思路

先看一个小数据朴素排序写法：

@include-code(./brute.cpp, cpp)

`brute.cpp` 使用选择排序：每次从还没有确定的位置里找出最小值，放到当前位置。它能直接说明“排序”要做什么，但时间复杂度是 `O(n^2)`，不能处理 `n=10^5` 的数据。

正式代码直接使用 C++ 标准库的 `sort`。它会把区间 `[a+1, a+n+1)` 按升序排列，然后顺序输出即可。

这题作为模板题，真正要掌握的是：

- 数组排序的调用范围；
- 输出时保留原题要求的空格格式；
- 数据值可能到 `10^9`，用 `int` 或 `long long` 都可以，本文用 `long long` 更稳。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：`O(n log n)`
- 空间复杂度：`O(n)`

### 总结

排序模板题没有隐藏模型。读入、排序、输出三步写稳即可。
