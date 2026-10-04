---
oj: "roj"
problem_id: "1215"
title: "迷宫"
description: "把迷宫可达性转成网格图连通性，从 A 出发用入栈即标记的 visited 做一次迭代 DFS，O(n²) 判断 B 是否同属一个连通分量。"
difficulty: "普及-"
date: 2026-09-29 23:49
updated: 2026-10-05 05:42
toc: true
tags: ["搜索", "深度优先搜索", "网格", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1215
---

[[TOC]]

## 题目描述

`n×n`（`1≤n≤100`）网格迷宫，每格 `.` 可走 / `#` 障碍；只能上下左右四方向相邻移动到 `.`。Extense 要从 A 走到 B（均 0 起始坐标），起点或终点为 `#` 视为不能。`k` 组输入：每组先 `n`，再 `n` 行矩阵，再 `ha la hb lb`；每组输出一行 `YES`/`NO`。

## 思路

把每个 `.` 看顶点、四方向相邻 `.` 连边，A→B 可达即二者同属一个连通分量。从 A 做一次带 `visited` 的迭代 DFS（显式栈），入栈即标记，弹到 B 返回 `YES`、栈空返回 `NO`，每组 `O(n²)`。

## 参考代码

@include-code(./main.cpp, cpp)
