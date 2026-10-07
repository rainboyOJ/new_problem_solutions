---
oj: "roj"
problem_id: "1598"
title: "「一本通 5.5 例 2」最大连续和"
description: "把限长子段和写成前缀和之差，单调队列维护窗口内最小前缀和，O(n) 求最大连续和。"
difficulty: "普及"
date: 2026-09-30 20:52
updated: 2026-10-06 01:07
toc: true
tags: ["前缀和", "单调队列", "滑动窗口", "python", "一本通"]
favorite: false
favorite_reason: ""
categories:
  - "一本通"
showAtRbook: []
pre: []
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

@include-code(./main.cpp, cpp)
