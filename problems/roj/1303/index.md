---
oj: "roj"
problem_id: "1303"
title: "鸣人的影分身"
description: "方案是多重集合，用非递增序列作代表元去掉排列重复；按末位是否为 0 得到 f(M,N)=f(M,N-1)+f(M-N,N)，记忆化后 O(MN)。"
difficulty: "普及-"
date: 2026-09-30 04:05
updated: 2026-10-05 08:34
toc: true
tags: ["动态规划", "递推", "记忆化搜索", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1303
---

[[TOC]]

## 题目描述

鸣人的查克拉能量为 $M$，影分身个数最多为 $N$，每个分身可以分到 $0$ 点查克拉，问把 $M$ 点能量分完的不同分配方法数 $K$（交换两个分身的点数算同一种方案）。第一行是测试数据组数 $t$（$0 \leqslant t \leqslant 20$），以下每行两个整数 $M, N$（$1 \leqslant M, N \leqslant 10$），每组输出一行 $K$；样例输入 `1` / `7 3`，输出 `8`。

## 思路

把一种方案写成非递增序列 $a_1 \geqslant a_2 \geqslant \dots \geqslant a_N \geqslant 0$（不足 $N$ 个的位置补 $0$），它与分配方案一一对应，于是设 $f(M,N)$ 为和为 $M$ 的这类序列数。看末位 $a_N$：为 $0$ 时方案数是 $f(M,N-1)$，否则全体减 $1$ 后是 $f(M-N,N)$，故 $f(M,N)=f(M,N-1)+f(M-N,N)$；边界为 $M=0$ 或 $N=1$ 时 $f=1$，$M<N$ 时 $f(M,N)=f(M,M)$。记忆化后只有 $O(MN)$ 个状态，每组询问 $O(1)$ 查表。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
