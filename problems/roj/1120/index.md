---
oj: "roj"
problem_id: "1120"
title: "同行列对角线的格"
description: "用行号、列号、行减列、行加列四个不变量刻画四条线，再用 max/min 裁出对角线在棋盘内的行号区间，按指定方向枚举输出。"
difficulty: "入门"
date: 2026-09-29 19:38
updated: 2026-10-05 02:31
toc: true
tags: ["入门", "输入输出"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1120
---

[[TOC]]

## 题目描述

给定 $N\times N$ 棋盘（行列从 1 开始）上的格子 $(i,j)$，输出与它在同一行、同一列、同一主对角线、同一副对角线上的所有格子坐标。同行从左到右、同列从上到下、主对角线从左上到右下、副对角线从左下到右上；每个坐标格式为 `(x,y)`，相邻坐标间用一个空格隔开。$1\le N\le 10$。

## 思路

行固定 $i$、列固定 $j$ 即可直接枚举；主对角线满足 $r-c=i-j$，副对角线满足 $r+c=i+j$，再用 $\max/\min$ 与棋盘边界 $[1,N]$ 取交得到对角线的行号区间。四条线统一格式化输出，复杂度 $O(N)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
