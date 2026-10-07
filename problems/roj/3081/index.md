---
oj: "roj"
problem_id: "3081"
title: "乳草的入侵"
description: "八连通网格上从起点做 BFS 求最晚被占领格子的层数，起点算第 0 周，答案即所有格子距离的最大值。"
difficulty: "普及-"
date: 2026-10-01 15:14
updated: 2026-10-06 11:40
toc: true
tags: ["搜索", "广度优先搜索", "BFS"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3081
---

[[TOC]]

## 题目描述

$X$ 列 $Y$ 行的网格，`.` 为草地、`*` 为大石。乳草第 $0$ 周占领格 $(M_x,M_y)$，此后每周向八连通相邻的草地扩散（保证最终全部被占领），求完全占领所需的星期数。首行输入 $X,Y,M_x,M_y$，随后 $Y$ 行地图；输出一个整数。$1\le X,Y\le100$。样例输入 `4 3 1 1` / `....` `..*.` `.**.`，输出 `4`。

## 思路

从起点做八连通 BFS，每个格子被占领的星期数就是它到起点的最短路层数（起点为第 $0$ 周）。石头不入队，答案取所有格子的最大层数。

## 参考代码

@include-code(./main.cpp, cpp)
