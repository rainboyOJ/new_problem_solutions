---
oj: "roj"
problem_id: "1373"
title: "鱼塘钓鱼(fishing）"
description: "枚举最远走到哪个鱼塘定下路程，把各塘递减的每分钟收益展开排序取前 k 大，O(N·S log S) 求出最大收获。"
difficulty: "普及-"
date: 2026-09-30 07:42
updated: 2026-10-05 12:23
toc: true
tags: ["贪心", "枚举", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1373
---

[[TOC]]

## 题目描述

$N$ 个鱼塘排成一排，第 $i$ 个鱼塘第 1 分钟能钓 $f_i$ 条鱼，之后每分钟减少 $d_i$（减到非正数后无鱼）。从第 $i$ 个鱼塘走到第 $i+1$ 个需 $t_i$ 分钟，只能向右走。总时间 $T$，求最多能钓多少鱼。

**输入**：5 行，依次为 $N$；$f_1..f_N$；$d_1..d_N$；$t_1..t_{N-1}$；$T$。  
**输出**：一个整数，最多钓到的鱼数。  
**样例输入/输出**：见 `problem.md`。

## 思路

枚举最远走到第 $L$ 个塘，路程固定后剩余时间全部用于钓鱼。每个塘每分钟收益递减，把所有已到达鱼塘的每分钟收益展开成一个序列，取前 `剩余时间` 大的和即为该路线的最优值。

## 参考代码

@include-code(./main.cpp, cpp)
