---
oj: "roj"
problem_id: "1360"
title: "奇怪的电梯(lift)"
description: "每层楼的两个按钮对应两条无权有向边，从 A 开始做 BFS，第一次到达 B 的距离就是最少按键次数。"
difficulty: "普及-"
date: 2026-09-30 07:03
updated: 2026-10-05 12:00
toc: true
tags: ["图论", "BFS", "最短路", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1360
---

[[TOC]]

## 题目描述

大楼有 $N$ 层，第 $i$ 层写有数字 $K_i$。电梯在 $i$ 层时，可上移到 $i+K_i$（不超过 $N$），或下移到 $i-K_i$（不小于 $1$），每次有效移动算一次按键。给定 $N,A,B$ 和序列 $K_{1\dots N}$，求从 $A$ 楼到 $B$ 楼的最少按键次数，无法到达输出 $-1$。

## 思路

把每层看成一个顶点，两个按钮看成两条无权有向边，从 $A$ 开始 BFS。`dist[i]` 记录从 $A$ 到 $i$ 的最少按键次数（$-1$ 表示未访问），第一次到达 $B$ 时的距离就是答案。

## 参考代码

@include-code(./main.cpp, cpp)
