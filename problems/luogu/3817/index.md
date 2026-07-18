---
oj: "luogu"
problem_id: "P3817"
title: "小A的糖果"
description: "从左到右贪心处理相邻两盒的和，超出 x 时优先减少当前盒，避免影响已经处理好的左侧。"
difficulty: "普及-"
date: 2026-06-19 01:20
toc: true
tags: ["贪心", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3817
---

[[TOC]]

### 题意

给定 `n` 个糖果盒，第 `i` 个盒子里有 `a_i` 颗糖。每次可以从某个盒子里吃掉一颗糖，要求最后任意相邻两个盒子的糖果数之和都不超过 `x`。问最少要吃掉多少颗糖。

### 思路

朴素做法是枚举每个盒子最后剩多少颗糖，然后检查所有相邻对是否合法，保留总糖数最大的方案：

@include-code(./brute.cpp, cpp)

正解从左到右处理。假设已经处理完 `0..i-1`，现在只需要让 `a[i-1] + a[i] <= x`。

如果这一对超过了 `x`，必须吃掉 `a[i-1] + a[i] - x` 颗。优先从当前盒子 `a[i]` 里吃更好，因为左边盒子已经参与过上一对限制；减少右边不会破坏左边已经合法的部分，还会让后面的相邻对更容易合法。

所以扫描每一对：

1. 计算超出量 `extra = a[i-1] + a[i] - x`；
2. 若 `extra <= 0`，不处理；
3. 优先从 `a[i]` 中吃掉 `extra`；
4. 如果当前盒不够，再补吃 `a[i-1]`。

### Python 知识

- `sys.stdin.buffer.read().split()` 适合读取大量整数。
- 列表 `candies` 可以原地修改，直接保存贪心处理后的盒子数量。
- `continue` 可以让“不超标”的分支尽早结束，主逻辑更清楚。

C++ 里常写数组和 `long long`；Python 的 `int` 不会溢出，本题只需要注意用线性扫描避免超时。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

只扫描一遍数组，时间复杂度是 $O(n)$。

空间复杂度是 $O(n)$，如果不计输入数组就是 $O(1)$。

### 总结

这题的核心是“从左到右固定已经处理好的部分”。当前相邻对超标时，优先减少右边盒子，避免回头影响左侧。
