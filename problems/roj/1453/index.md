---
oj: "roj"
problem_id: "1453"
title: "「一本通 1.4 练习 3」移动玩具"
description: "将 4x4 网格的 01 状态压缩为 16 位整数，BFS 搜索最少交换步数。"
difficulty: "普及"
date: 2026-09-30 11:24
updated: 2026-10-05 23:55
toc: true
tags:
  - "广度优先搜索"
  - "状态压缩"
favorite: false
favorite_reason: ""
categories:
  - "搜索"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1453
---

[[TOC]]

## 题目描述

给定两个 $4 \times 4$ 的 01 矩阵（分别表示初始状态和目标状态，其中 1 表示有玩具，0 表示没有），保证两个矩阵中 1 的个数相同。每次操作可以选择上下或左右相邻的两个格子，若其中一个为 1、另一个为 0，则交换这两个格子的值。求将初始状态变为目标状态所需的最少操作次数。

## 思路

状态空间很小，用 16 位整数压缩 $4 \times 4$ 网格，枚举 24 对相邻格子进行状态转移，BFS 求最短路即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
