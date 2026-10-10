---
oj: "roj"
problem_id: "1373"
title: "鱼塘钓鱼(fishing）"
description: "枚举最远走到哪个鱼塘定下路程，把各塘递减的每分钟收益展开排序取前 k 大，O(N·S log S) 求出最大收获。"
difficulty: "普及-"
date: 2026-09-30 07:42
updated: 2026-10-07 13:50
toc: true
tags: ["贪心", "枚举", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "20022"
    reason: "B 在枚举最远鱼塘、把每塘递减收益摊平成表之后，直接复用 A 教的「排序取前 m 大」这一贪心步骤，把它改成对各塘合并表降序取前 left 项求和；A 特有的基准转换 d_i=a_i-b_i 未被使用，故属模板级复用。"
  - oj: "roj"
    problem_id: "1235"
    reason: "B 的 main.py 中 picks.sort(reverse=True); sum(picks[:left]) 直接套用 A 教的「降序排序后取前 k 大」，只是把单张数组换成一排鱼塘合并出的分钟收益表；B 自身的主要难度在枚举最远鱼塘 L、把递减收益摊平成表这两个 A 未教的新步骤，因此该复用属模板级而非决定本题难度。"
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

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
