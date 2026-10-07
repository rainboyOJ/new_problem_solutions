---
oj: "roj"
problem_id: "2004"
title: "usaco-1.2.1 挤牛奶"
description: "把每个农民的挤奶时段看成闭区间，按左端点排序后单趟扫描合并成极大连通块，最长块即为最长有奶时长，相邻块间距最大值即为最长空档。"
difficulty: "普及-"
date: 2026-10-01 02:28
updated: 2026-10-06 09:17
toc: true
tags:
  - "排序"
  - "区间合并"
  - "贪心"
favorite: false
favorite_reason: ""
categories:
  - "基础算法"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2004
---

[[TOC]]

## 题目描述

数轴上有 $N$ 条闭区间 $[s_i, e_i]$（$1 \leqslant N \leqslant 5000$，$0 \leqslant s_i \leqslant e_i < 10^6$）。

求所有区间并集中「至少有一段区间覆盖」的最长连续长度，以及相邻连通块之间「没有任何区间覆盖」的最长连续长度。两个答案按顺序输出一行。

## 思路

按左端点升序排序后，维护当前极大连通块 $[L,R]$。若下一个区间的左端点 $s \leqslant R$，则与之重叠或首尾相接，扩展右端 $R = \max(R, e)$；否则断开并开启新块。最长块长与相邻块间距的最大值即为答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
