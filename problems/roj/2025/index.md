---
oj: "roj"
problem_id: "2025"
title: "usaco-2.1.5 海明码"
description: "最优解首项必为 0（整体异或最小元），故按数值字典序逐位贪心：每次从上一个编码 +1 起扫描，接上第一个与已选集合两两 popcount(x xor y) >= D 的编码，O(N^2·2^B)。"
difficulty: "普及-"
date: 2026-10-01 03:37
updated: 2026-10-06 09:46
toc: true
tags: ["贪心", "位运算", "构造", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2025
---

[[TOC]]

## 题目描述

给定 $N, B, D$，在 $B$ 位编码的取值范围 $[0, 2^B-1]$ 中选出 $N$ 个互不相同的数，使得任意两个的海明距离（二进制不同位的个数）都不小于 $D$。输出按升序排列，每行 10 个；若有多解，输出化为 $2^B$ 进制后数值最小的那一组。

数据范围：$1 \le N \le 64$，$1 \le B \le 8$，$1 \le D \le 7$。

样例输入：`16 7 3`

样例输出：
```
0 7 25 30 42 45 51 52 75 76
82 85 97 102 120 127
```

## 思路

最优解首项必为 $0$：把任意合法解整体异或 $a_1$ 后仍合法且首项更小。于是逐位贪心：已选最后一个编码 $+1$ 开始往后扫，第一个与已选所有编码海明距离均 $\ge D$ 的数就接上去。高位优先保证了贪心正确。

## 参考代码

@include-code(./main.cpp, cpp)

