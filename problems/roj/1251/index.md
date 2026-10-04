---
oj: "roj"
problem_id: "1251"
title: "仙岛求药"
description: "网格四连通 BFS，起点距离为 0，首次到达终点时的层号即最少步数。"
difficulty: "普及-"
date: 2026-09-30 01:45
updated: 2026-10-05 07:02
toc: true
tags: ["搜索", "BFS", "网格", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1251
---

[[TOC]]

## 题目描述

给定 $M$ 行 $N$ 列的迷宫（$M,N\leqslant20$），`@` 为起点，`*` 为仙药，`#` 为怪物不可走，`.` 为安全格。每步可上下左右移动一格，求从 `@` 到 `*` 经过的最少方格数；若无法到达输出 `-1`。输入含多组数据，以 `0 0` 结束。

## 思路

把每个可通行格看成图中的一个点，四方向相邻且均可通行的点之间连一条长度为 1 的边。边权全为 1，因此从起点开始 BFS，第一次到达终点时的层号就是最短步数；队列空仍未到达则输出 `-1`。

## 参考代码

@include-code(./main.cpp, cpp)
