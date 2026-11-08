---
oj: "luogu"
problem_id: "B3611"
title: "【模板】传递闭包"
description: "中转点 k 置于最外层 + 用 i→k 与 k→j 的可达关系累积 i→j + 一趟求出整张传递闭包"
difficulty: "普及"
date: 2026-07-17 03:00
updated: 2026-11-08 15:54
toc: true
tags: ["传递闭包", "Floyd", "warshall", "位运算"]
categories: []
showAtRbook: ["rbook1:floyd"]
rbookLinks:
  - id: "rbook1:floyd"
    reason: "模板题目：本题就是 Floyd 的布尔版（传递闭包），先看这篇把中转点 k 放最外层、两段拼接，再把 min+加 换成 或+与"
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/B3611
---

[[TOC]]

## 形式化题目

给定一个有向图：$n$ 个点，用邻接矩阵 $A$ 表示，$a_{ij}=1$ 表示有边 $i \to j$，且 $a_{ii}=0$（无自环）。求它的传递闭包 $B$：$b_{ij}=1$ 当且仅当从 $i$ 出发可以沿若干条边到达 $j$。

## 正解

### 思路

传递闭包只关心「能不能到」，不关心怎么到，于是和全源最短路一样用 Floyd（Warshall）的骨架：

- 枚举中转点 $k$，若 $i$ 能到 $k$、且 $k$ 能到 $j$，则 $i$ 也能到 $j$，把 $b_{ij}$ 置为真；
- 中转点 $k$ **必须放在最外层**，这样所有「允许经过前 $k$ 个点」的路径都会被逐层累积进来，循环结束后就是全部可达关系。

这就是把 Floyd 的 `min(dis[i][k]+dis[k][j])` 换成布尔「或」：一旦 $i\to k$、$k\to j$ 同时成立，就令 $i \to j$ 成立。中途剪掉「$i$ 到不了 $k$」和「$k$ 到不了 $j$」的情况，可少做无用的赋值。

### 代码

@include-code(./main.cpp, cpp)

同一套转移也可以用别的存储方式表达，关键思维完全相同：

- Python 用整数把一行可达集合压成位集，`mask |= value << index` 编码一行，`if rows[start] & middle_bit: rows[start] |= middle_row` 一次按位或同时处理所有终点，只是把最内层循环交给位运算；
- 朴素三重循环版本只把最内层的布尔判断换成按位或，逻辑更直白。

@include-code(./main.py, python)

@include-code(./main-user.py, python)

### 复杂度

三重循环对每个中转点枚举所有起点与终点对，时间 $O(n^3)$，空间 $O(n^2)$。$n\le 100$ 时约 $10^6$ 次运算，非常宽裕。位集写法把最内层换成一次大整数按位或，常数更小。

## 总结

传递闭包就是「布尔版 Floyd」：把最短路里的加法与取最小，换成逻辑或与赋值，中转点 $k$ 放最外层，一次跑完即得任意两点可达性。
