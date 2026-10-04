---
oj: "roj"
problem_id: "1248"
title: "Dungeon Master"
description: "三维网格建成无权图，可通行格是顶点、六方向相邻连边，BFS 入队即标记，命中 E 的层号就是最短分钟数。"
difficulty: "普及-"
date: 2026-09-30 01:34
updated: 2026-10-04 21:00
toc: true
tags: ["图论", "最短路", "搜索", "BFS", "网格", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1248
---

[[TOC]]

## 题目描述

你被困在一个 $L\times R\times C$（均 $\le 30$）的三维立方体空间里，每格为 `#`（不可通过）、`.`（可通行）、`S`（起点，唯一）或 `E`（出口，唯一）。每次只能朝上下前后左右六个方向之一移动到相邻格，耗时 1 分钟；不可对角线移动。求 `S` 到 `E` 的最少分钟数，不可达输出 `Trapped!`。多组数据，每组先给 `L R C`，再依次给 $L$ 层、每层 $R$ 行 $C$ 列的网格（层间有空行）；`0 0 0` 结束。样例 1：`3 4 5` + `S..../.###./.##../###.#` + `####/####/##.##/##...` + `####/####/#.###/####E` → `Escaped in 11 minute(s).`；样例 2：`1 3 3` + `S##/#E#/###` → `Trapped!`。

## 思路

把三维网格建成无权图：可通行格是顶点，六方向相邻就连一条无向边，`S` 到 `E` 的最短距离就是答案。边权全为 1，所以从 `S` 出发 BFS 的层号就是"已用分钟数"，命中 `E` 的层号直接返回；入队即标记保证每格只展开一次，复杂度 $O(LRC)$。

## 参考代码

@include-code(./main.cpp, cpp)
