---
oj: "roj"
problem_id: "1219"
title: "马的遍历"
description: "≤5×5 棋盘上从给定起点出发、马走日不重复的全遍历路径条数，回溯按邻接表枚举合法马步，位图维护已访问集合。"
difficulty: "普及-"
date: 2026-09-30 00:15
updated: 2026-10-05 05:50
toc: true
tags: ["搜索", "回溯", "位运算", "cpp"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1219
---

[[TOC]]

## 题目描述

给定 $n \times m$（$n,m \le 5$）的棋盘和马的起点 $(x,y)$，马按中国象棋"日字"移动且不能重复经过同一个格子，求恰好遍历全部 $n\cdot m$ 个格子的路径条数；不存在则输出 $0$。第一行整数 $T<10$ 表示测试组数，随后每行四个整数 $n,m,x,y$（$0\le x<n,\,0\le y<m$）；每组一行输出。

样例：输入 `5 4 0 0` 输出 `32`。

## 思路

$n\cdot m\le 25$ 直接深度优先回溯：从起点出发，每步只在"当前格的合法日字落点"里挑未访问的格子走，用整型位图记录已访问集合；走到无剩余格子时计 $1$，累加所有分支即为答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
