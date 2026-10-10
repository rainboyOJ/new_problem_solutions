---
oj: "roj"
problem_id: "1427"
title: "「一本通 1.1 练习 1」数列极差"
description: "贪心加堆：每次合并最小的两个数得 max，取负后每次合并最大的两个数得 min，两遍小根堆后作差，O(N log N)。"
difficulty: "普及-"
date: 2026-09-30 09:44
updated: 2026-10-05 23:26
toc: true
tags: ["贪心", "堆", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1427
---

[[TOC]]

## 题目描述

黑板上写了 $N$ 个正整数。每次操作擦去两个数 $a,b$，写入 $a\times b+1$，直到只剩一个数。不同操作顺序得到不同结果，最大者记为 $max$、最小者记为 $min$，求极差 $max-min$。输入第一行 $N$，第二行 $N$ 个正整数；输出极差。样例输入 `3 / 1 2 3`，样例输出 `2`。（原题面未给出 $N$ 的范围。）

## 思路

每次合并当前最小的两个数能得到最大值，每次合并当前最大的两个数能得到最小值——依据是三个数 $a<b<c$ 的展开式中最晚被合并的那个数单独贡献一项，大数留到最后更大。两个方向各做 $N-1$ 次合并，用小根堆维护最值；求最小方向把数取负放进同一个小根堆即可。复杂度 $O(N\log N)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
