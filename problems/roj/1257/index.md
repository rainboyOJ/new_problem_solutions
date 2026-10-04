---
oj: "roj"
problem_id: "1257"
title: "Knight Moves"
description: "棋盘上马的最少步数就是隐式无权图的单源最短路：边权全为 1，按步数分层 BFS，首次到达终点即答案。"
difficulty: "普及-"
date: 2026-09-30 02:01
updated: 2026-10-05 07:11
toc: true
tags: ["搜索", "BFS", "网格", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1257
---

[[TOC]]

## 题目描述

输入 $T$ 表示测试样例组数。每组给出棋盘边长 $L$（$4 \leqslant L \leqslant 300$）、马的起点与终点坐标（均在 $0..L-1$ 内）；马走「日」字，共 8 个方向。求从起点跳到终点的最少步数，起止相同输出 $0$。

样例：输入 `3 / 8 / 0 0 / 7 0 / 100 / 0 0 / 30 50 / 10 / 1 1 / 1 1`，输出 `5 / 28 / 0`。

## 思路

棋盘是隐式无权图，边权全为 1，用分层 BFS 求最短路：起点距离记 0，出队时把 8 个合法落点中未访问的记为「当前距离 +1」并入队，首次到达终点时的步数就是答案。入队即标记使每格至多扩展一次，复杂度 $O(L^2)$。

## 参考代码

@include-code(./main.cpp, cpp)
