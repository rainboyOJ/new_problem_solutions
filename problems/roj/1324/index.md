---
oj: "roj"
problem_id: "1324"
title: "【例6.6】整数区间"
description: "把区间按右端点升序排序，逐个检查是否被已选点覆盖；未被覆盖就取它的右端点，一次扫描得到最少点数。"
difficulty: "普及-"
date: 2026-09-30 05:19
updated: 2026-10-05 09:41
toc: true
tags: ["贪心", "区间贪心", "排序", "区间", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1324
---

[[TOC]]

## 题目描述

给定 $n$ 个闭区间 $[a_i, b_i]$（$0 \leqslant a_i \leqslant b_i \leqslant 10000$），求一个元素个数最少的整数集合 $S$，使每个区间内都至少有一个 $S$ 中的整数，输出 $|S|$。
输入第一行 $n$（$1 \leqslant n \leqslant 10000$），接下来 $n$ 行每行两个整数 $a,b$；输出最少元素个数。
样例输入：`4` 后接 `3 6`、`2 4`、`0 2`、`4 7`；样例输出：`2`。

## 思路

把区间按右端点升序排序。用 `last` 记录已选点中的最大值（初值 `-1` 表示还没选点），扫描时若 $a_i > \text{last}$，说明该区间没有被任何已选点覆盖，必须新增一个点，且取它的右端点 $b_i$ 能覆盖后面尽量多的区间。这种取法总可以延拓成最优解，因为每次触发新增点所对应的区间两两不相交。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
