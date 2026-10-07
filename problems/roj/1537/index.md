---
oj: "roj"
problem_id: "1537"
title: "「一本通 4.1 例 3」校门外的树"
description: "动态区间相交计数化归为两个端点前缀计数：答案 = 左端点 ≤ r 的段数 − 右端点 < l 的段数，两棵树状数组在线维护，O(m log n)。"
difficulty: "普及-"
date: 2026-09-30 16:53
updated: 2026-10-06 00:42
toc: true
tags: ["树状数组", "前缀和", "python"]
favorite: false
favorite_reason: ""
categories: ["一本通"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1537
---

[[TOC]]

## 题目描述

一条长为 $n$ 的道路上有 $m$ 个操作 $(K, l, r)$：$K=1$ 表示在 $[l, r]$ 之间种上一种树，每次操作种的树种互不相同，且每个位置都可以重复种树；$K=2$ 表示询问 $[l, r]$ 之间有多少种树。输入第一行为 $n, m$，接下来 $m$ 行每行三个整数 $K, l, r$；对每个 $K=2$ 的操作输出一行答案。数据范围：$1 \le n, m \le 5 \times 10^4$，保证 $l, r > 0$。样例：输入 `5 4`、`1 1 3`、`2 2 5`、`1 2 4`、`2 3 5`，输出 `1`、`2`（先种 $[1,3]$ 后问 $[2,5]$ 得 $1$，再种 $[2,4]$ 后问 $[3,5]$ 得 $2$）。

## 思路

每种树只在一段上种一次且无删除，问题就是在线统计与询问区间相交的线段条数；由 $[L,R]$ 与 $[l,r]$ 相交 $\Leftrightarrow L \le r$ 且 $R \ge l$，容斥后得答案 $= \#\{L \le r\} - \#\{R < l\}$，用两棵分别按左端点、右端点计数的树状数组在线维护即可，复杂度 $O(m \log n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
