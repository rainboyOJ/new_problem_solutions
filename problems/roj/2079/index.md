---
oj: "roj"
problem_id: "2079"
title: "usaco-5.2.1 蜗牛的旅行"
description: "起步方向和每个撞墙点的左/右转向构成决策树，回溯枚举所有走法并刷新走过的最大格数，撞上自己足迹即结束。"
difficulty: "普及-"
date: 2026-10-01 07:22
updated: 2026-10-06 10:38
toc: true
tags: ["搜索", "DFS", "回溯", "网格", "python"]
favorite: false
favorite_reason: ""
categories: ["搜索"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2079
---

[[TOC]]

## 题目描述

$N \times N$ 的棋盘上有 $B$ 个路障，蜗牛从左上角 A1 出发，起步只能向右或向下；选定方向就直行到底，撞到棋盘边缘或路障时才转 90°（左转、右转任选），若撞到自己走过的格子则整段散步立即结束。求能走过的最多格子数（起点计入，$1<N<120$，$1\le B\le200$）。输入第一行 `N B`，随后 $B$ 行路障坐标（如 `E2`，字母为列、数字为行）；样例输入 `8 4 / E2 / A6 / G1 / F5`，输出 `33`。

## 思路

主动的选择只有起步方向（右或下）和每个撞墙点的左/右转向，于是把"起步方向 + 每次撞墙的转向"当成决策树回溯枚举：直行段按规则被动走到底，并沿途刷新走过的最大格数。撞上自己的足迹要立即结束、不再转弯；足迹属于单条分支，回溯时必须撤销。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
