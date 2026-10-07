---
oj: "roj"
problem_id: "3080"
title: "武士风度的牛"
description: "BFS 求网格上马步最短路，首次到达草地即最少跳跃次数。"
difficulty: "普及-"
date: 2026-10-01 15:14
updated: 2026-10-06 11:40
toc: true
tags: ["搜索", "BFS", "最短路", "网格", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3080
---

[[TOC]]

## 题目描述

给定 $C \times R$ 网格（$C,R \leqslant 150$），格子为 `.`、`*`、`K`、`H`。棋子从 `K` 出发按马走日跳跃，落点需在网格内且非障碍，求到 `H` 的最少跳跃次数。数据保证有解。

**输入**：$C\ R$，随后 $R$ 行地图。  
**输出**：最少跳跃次数。

## 思路

把非障碍格看成顶点、马步看成边权为 1 的边，得到无权无向图。BFS 按层扩展，dist 数组兼作判重，首次到达 `H` 时的层数就是答案。

## 参考代码

@include-code(./main.cpp, cpp)
