---
oj: "luogu"
problem_id: "P1714"
title: "切蛋糕"
description: "把限长子段和写成前缀和之差，用单调队列维护最近 m 个前缀和的最小值。"
difficulty: "普及/提高-"
date: 2025-12-26 19:34
toc: true
tags: ["前缀和", "单调队列", "python"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P2032"
    reason: "先掌握单调队列维护滑动窗口最值。"
common:
  - oj: "luogu"
    problem_id: "P2032"
    reason: "同为单调队列滑动窗口应用。"
recommend: []
source: https://www.luogu.com.cn/problem/P1714
---

[[TOC]]

### 题意

选择长度在 $1..m$ 之间的非空连续子段，使元素和最大。

### 思路

设 `prefix[i]` 为前 $i$ 项和。固定右端前缀 `i` 时，合法左端前缀 `j` 位于 `[i-m,i-1]`，子段和是 `prefix[i]-prefix[j]`。因此只需维护这个滑动窗口内最小的前缀和。

递增单调队列保存候选前缀；先删除过期队头并计算答案，再把当前前缀作为未来候选加入。

### Python 知识

- 不保存完整前缀数组，只用变量 `prefix` 在线累加。
- 两个紧凑数组分别保存候选下标与前缀值，适合五十万规模。
- 流式整数解析同时支持负数并控制内存。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

### 总结

限长最大子段和等价于“当前前缀减最近窗口内最小前缀”。
