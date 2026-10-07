---
oj: "roj"
problem_id: "1342"
title: "【例4-1】最短路径问题"
description: "把连线看成带权无向边、边权为两端点的欧氏距离，用 Floyd 在 O(n^3) 内求出全源最短路，再读出 d(s,t)。"
difficulty: "普及-"
date: 2026-09-30 06:08
updated: 2026-10-05 10:47
toc: true
tags: ["图论", "最短路", "Floyd", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1342
---

[[TOC]]

## 题目描述

平面上 $n$ 个点，给出 $m$ 条连线。连线表示两点可通行，通路长度为两点间直线距离。给定源点 $s$ 和目标点 $t$，输出 $s$ 到 $t$ 的最短路径长度，保留两位小数。

## 思路

把每条连线看成边权为欧氏距离的无向边，构建邻接矩阵。由于 $n \leqslant 100$，直接跑 Floyd 求出全源最短路，输出 $d[s][t]$ 即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
