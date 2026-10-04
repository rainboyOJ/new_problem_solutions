---
oj: "roj"
problem_id: "1254"
title: "走出迷宫"
description: "把可通行格建成无权无向图，四方向 BFS 逐层扩展，层号就是最少步数；入队即标记保证每格只展开一次，不连通时无输出。"
difficulty: "普及-"
date: 2026-09-30 02:01
updated: 2026-10-05 07:12
toc: true
tags: ["搜索", "BFS", "最短路", "网格", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1254
---

[[TOC]]

## 题目描述

给定一个 $n \times m$ 的迷宫（$1 \leqslant n,m \leqslant 100$），求起点到出口的最少步数；走不到则不输出任何内容。每格是 `.`（空地）、`#`（墙）、`S`（起点）、`T`（出口）之一，每步沿上、下、左、右走到相邻可通行格。

**输入**：第一行两个整数 $n$ 和 $m$；接下来 $n$ 行，每行一个长为 $m$ 的字符串表示迷宫。

**输出**：输出最少需要走的步数。

**样例**：输入 `3 3`、`S#T`、`.#.`、`...`，输出 `6`。

## 思路

每步代价相同，把可通行格看成顶点、四方向相邻看成边，答案就是 `S` 到 `T` 的最短路；边权全为 1，BFS 逐层扩展，第一次碰到 `T` 时的层号就是答案。每个格子**入队时**就标记 `vis`，保证只入队一次，复杂度 $O(nm)$。

## 参考代码

@include-code(./main.cpp, cpp)
