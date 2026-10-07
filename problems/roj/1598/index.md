---
oj: "roj"
problem_id: "1598"
title: "「一本通 5.5 例 2」最大连续和"
description: "把限长子段和写成前缀和之差，单调队列维护窗口内最小前缀和，O(n) 求最大连续和。"
difficulty: "普及"
date: 2026-09-30 20:52
updated: 2026-10-07 13:50
toc: true
tags: ["前缀和", "单调队列", "滑动窗口", "python", "一本通"]
favorite: false
favorite_reason: ""
categories:
  - "一本通"
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P3353"
    reason: "B 的第一步直接复用 A 教的前缀和作差，把限长子段和写成 S_j - S_{i-1}（main.py 里 pres[i]-pres[dq[0]]），再叠加 A 未教的单调队列求窗口最小前缀。"
  - oj: "luogu"
    problem_id: "P8218"
    reason: "B 把 A 教的「前缀和作差得区间和」当作第一步复用（main.py 里 pres[i]-pres[dq[0]]），只是把固定询问区间换成限长子段，再叠加单调队列求窗口最小前缀"
common: []
recommend: []
source: https://roj.ac.cn/problem/1598
---

[[TOC]]

## 题目描述

给定长度为 $n$ 的整数序列，找出一段连续且长度不超过 $m$ 的子段，使其和最大（$1 \le n, m \le 2 \times 10^5$）。

## 思路

以 $i$ 结尾的最大子段和为 $S_i - \min S_j$（$j \in [i-m, i-1]$），用单调队列维护滑动窗口内前缀和最小值，队首过期弹出、队尾不小于当前值则淘汰，每个下标进出各一次，整体 $O(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
