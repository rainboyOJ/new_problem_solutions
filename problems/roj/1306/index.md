---
oj: "roj"
problem_id: "1306"
title: "最长公共子上升序列"
description: "以 B 序列每个位置作为结尾维护 LCIS 长度与方案，扫描 A 序列时复用当前最优前驱，O(n²) 完成并直接输出序列。"
difficulty: "普及+/提高-"
date: 2026-09-30 04:07
updated: 2026-10-07 11:01
toc: true
tags:
  - DP
  - 最长公共子序列
  - 最长上升子序列
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1306
---

[[TOC]]

## 形式化题目

给定两个整数序列 $A$（长度 $n$）和 $B$（长度 $m$），求一个最长的序列 $S$，使得：

- $S$ 是 $A$ 的子序列；
- $S$ 是 $B$ 的子序列；
- $S$ 严格递增。

输出 $|S|$ 以及 $S$ 本身（任意一个合法的最长序列均可）。

## 正解

### 思路

设 $f[j]$ 表示以 $B[j]$ 结尾的最长上升公共子序列（LCIS）的长度。当枚举到 $A$ 中的某个元素 $x$ 时，同时扫描 $B$：

- 若 $x > B[j]$，则 $B[j]$ 可以作为 $x$ 的前驱，更新当前最优前驱；
- 若 $x == B[j]$，则可以把 $x$ 接在当前最优前驱后面，得到以 $B[j]$ 结尾的更长 LCIS。

为了直接输出方案，额外维护以每个 $A[i]$ 结尾的完整序列。具体地，按 $B$ 的顺序扫描时，遇到 $A[i] < B[t]$ 就继承当前最优序列；遇到 $A[i] = B[t]$ 就把 $B[t]$ 接到该序列后，并保存到位置 $i$。最后在所有 $A[i]$ 的结尾序列中取最长的一个输出。

这样把朴素 $O(n^4)$ 或 $O(n^3)$ 的做法压缩成 $O(n \cdot m)$，空间 $O(n \cdot L)$，其中 $L$ 为答案长度。

### 代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(n \cdot m)$，$n, m \leqslant 500$。
- 空间复杂度：$O(n \cdot L)$，其中 $L$ 为 LCIS 长度，用于保存每个位置结尾的序列。

## 总结

本题是 LCS 与 LIS 的结合。关键观察是把“以 $B[j]$ 结尾”作为状态，在扫描 $A$ 时用滚动变量维护最优前驱，避免枚举第三维。保存完整序列即可直接输出任意一组最长上升公共子序列。
