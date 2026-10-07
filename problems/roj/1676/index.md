---
oj: "roj"
problem_id: "1676"
title: "骨牌1"
description: "把 n 拆成恰好 k 个正整数之和的方案数，用 (剩余和, 剩余段数, 下一段下界) 三元组记忆化搜索。"
difficulty: "普及-"
date: 2026-10-01 02:10
updated: 2026-10-07 13:50
toc: true
tags: ["动态规划", "记忆化搜索", "整数划分", "数学", "递归"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "5000"
    reason: "B 直接沿用 A 的单调约定去重（非增/非降一一对应）并把边界量收进记忆状态，只是把上限收紧改成下界随 head 传递，再叠加恰好 k 段的新约束"
common:
  - oj: "roj"
    problem_id: "1675"
    reason: "数与数据完全相同的重题（1675「数的划分」），同样求 n 拆成恰好 k 个正整数之和的方案数，可作为同一模型的对读。"
recommend: []
source: https://roj.ac.cn/problem/1676
---

[[TOC]]

## 题目描述

给定正整数 $n$ 和 $k$，求把 $n$ 拆成恰好 $k$ 个正整数之和的方案数，顺序不同视为同一种。数据范围满足 $n \le 200$，$k \le 7$ 左右。

## 思路

由于加法可交换，每个方案都可以唯一对应一个非降序列 $1 \le a_1 \le a_2 \le \dots \le a_k$ 且和为 $n$。用 `ways(rest, parts, low)` 表示还要把 `rest` 分成 `parts` 段、且下一段最小为 `low` 的方案数。枚举当前段 `head`，下界是非降约束 `low`，上界收紧为 `rest / parts`（余下每段都至少为 `head`）。`parts == 1` 时只要 `rest >= low` 就唯一方案，`parts == 0` 时只有 `rest == 0` 才计 1。用记忆化数组保存三个参数的状态。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
