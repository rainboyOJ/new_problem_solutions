---
oj: "roj"
problem_id: "1252"
title: "走迷宫"
description: "网格 BFS：从左上角 BFS 到右下角，按层扩展，首次到达时的层号就是最少经过的格子数（含起点终点）。"
difficulty: "普及-"
date: 2026-09-30 01:46
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
source: https://roj.ac.cn/problem/1252
---

[[TOC]]

## 题目描述

给定 $R \times C$ 迷宫（$1 \le R, C \le 40$），`.` 可走、`#` 不可走，每步只能上下左右移到相邻 `.`。求左上角 $(1,1)$ 到右下角 $(R,C)$ 最少要经过的格子数（**含起点终点**）。第一行 $R$、$C$，接着 $R$ 行 $C$ 字符。

样例：`5 5 / ..### / #.... / #.#.# / #.#.# / #.#..` → `9`。

## 思路

把每个 `.` 看作顶点、四方向连边，对无权图做 BFS：起点层号记 1，每扩展一层 +1，首次到达终点时的层号就是最少经过格子数。入队即标记使每格只展开一次，复杂度 $O(RC)$。

## 参考代码

@include-code(./main.cpp, cpp)