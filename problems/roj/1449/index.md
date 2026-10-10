---
oj: "roj"
problem_id: "1449"
title: "「一本通 1.4 例 2」魔板"
description: "状态只有 8! 个，把每个排列看作节点、A/B/C 三种操作看作边，从基本状态 12345678 BFS，邻居按 A→B→C 顺序扩展且只在首达时记前驱，回溯即得字典序最小的最短操作序列。"
difficulty: "普及-"
date: 2026-09-30 11:11
updated: 2026-10-05 23:47
toc: true
tags:
  - BFS
  - 状态压缩
  - 置换
favorite: false
favorite_reason: ""
categories:
  - 搜索
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1449
---

[[TOC]]

## 题目描述

给定 $1\sim 8$ 的一个排列作为魔板状态（从左上角起顺时针读出）。三种操作：A 交换上下两行；B 最右列插入最左列；C 中央 $2\times2$ 顺时针旋转。

输入一行 8 个整数表示目标状态；输出最短操作序列的长度，以及字典序最小的最短操作串（除最后一行外每行 60 个字符）。样例：输入 `2 6 8 4 5 7 3 1`，输出 `7` / `BCABCCB`。

## 思路

状态总数只有 $8!=40320$，把每个排列看作节点、三种操作看作边，从基本状态 `12345678` 做 BFS；邻居固定按 A、B、C 顺序扩展且只在首次入队时记前驱，首次到达目标的路径就是字典序最小的最短操作序列，回溯前驱输出即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
