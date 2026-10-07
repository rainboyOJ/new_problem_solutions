---
oj: "roj"
problem_id: "1280"
title: "【例9.24】滑雪"
description: "把格子按高度升序作为拓扑序，迭代填表求最长严格递减路径。"
difficulty: "普及-"
date: 2026-09-30 03:02
updated: 2026-10-05 07:50
toc: true
tags: ["普及-", "动态规划", "记忆化搜索", "DAG", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1280
---

[[TOC]]

## 题目描述

给定 $R \times C$（$1 \leqslant R,C \leqslant 100$）的高度矩阵。从任意格子出发，每一步只能滑向上下左右相邻且高度严格减小的格子，路径长度按经过格子数计算。求最长滑坡长度。

输入：第一行 $R$、$C$，接下来 $R$ 行每行 $C$ 个整数表示高度。  
输出：一个整数，最长滑坡长度。

样例输入：
```
5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
```
样例输出：
```
25
```

## 思路

设 $f(i,j)$ 为从 $(i,j)$ 出发的最长长度。严格递减的移动规则保证无环，按高度从小到大排序后依次填表：处理 $(i,j)$ 时所有更低邻居都已算完，$f(i,j)=1+\max$ 相邻更低格的 $f$ 值。全局最大值即为答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
