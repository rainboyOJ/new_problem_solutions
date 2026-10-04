---
oj: "roj"
problem_id: "1260"
title: "【例9.4】拦截导弹(Noip1999)"
description: "第一问最长不升子序列，第二问由 Dilworth 定理等于最长严格上升子序列；两问共用一个二分 LIS 函数，O(n log n)。"
difficulty: "普及-"
date: 2026-09-30 02:15
updated: 2026-10-05 07:21
toc: true
tags: ["动态规划", "最长上升子序列", "Dilworth定理", "贪心", "二分", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1260
---
[[TOC]]
## 题目描述

一套导弹拦截系统的第一发炮弹可达任意高度，之后每一发都不能高于前一发。给定依次飞来的导弹高度（均为 $\leqslant 30000$ 的正整数，个数 $\leqslant 1000$），第一行输出最多能拦截多少导弹，第二行输出拦截所有导弹最少需要配备的系统套数。输入为一行以空格分隔的高度序列；样例输入 `389 207 155 300 299 170 158 65`，样例输出：

```
6
2
```

## 思路

第一问是"最长不升子序列"（翻转序列后求"最长不下降"）；第二问由 Dilworth 定理等于"最长严格上升子序列"。两问共用同一个二分 LIS 函数（参数 strict 切换比较方向），整体 $O(n \log n)$。

## 参考代码
@include-code(./main.cpp, cpp)