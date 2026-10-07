---
oj: "roj"
problem_id: "1431"
title: "「一本通 1.1 练习 5」钓鱼"
description: "枚举最远走到哪个湖定下路程，剩余 5 分钟段用小根堆反复取当前产量最高的湖，O(n·12H·log n) 求最大收获。"
difficulty: "普及-"
date: 2026-09-30 09:58
updated: 2026-10-05 23:45
toc: true
tags: ["贪心", "堆", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: ["贪心"]
showAtRbook: []
pre: []
common:
  - oj: "roj"
    problem_id: "1373"
    reason: "同一模型（递减边际收益 + 预算分配）的按分钟版本，衰减量恒 ≥ 1，可对照两种「取前 k 大」的实现"
recommend: []
source: https://roj.ac.cn/problem/1431
---

[[TOC]]

## 题目描述

$n$ 个湖排成一排，从湖 $1$ 出发只能向右走，总时间 $H$ 小时切成 $12H$ 个 5 分钟段；湖 $i$ 钓一段的产量首段为 $F_i$、每段递减 $D_i$（负数按 0 计），从湖 $i$ 走到湖 $i+1$ 占 $T_i$ 段。选定终点湖后走路时间固定，其余时间自由分配给经过的湖钓鱼，求最多钓多少条鱼。

## 思路

枚举最远走到的湖 $L$，路程占用固定后，问题变成从各湖的逐段产量中取最大的 $k$ 段求和。所有湖的产量序列都是递减的，用一个大根堆每次弹出当前最大值、把该湖下一段产量入堆，贪心取满 $k$ 段即得该路线最优，取所有 $L$ 的最大值即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
