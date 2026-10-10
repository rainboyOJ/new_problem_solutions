---
oj: "roj"
problem_id: "1542"
title: "「一本通 4.2 例 2」最敏捷的机器人"
description: "两个单调队列分别维护窗口最值候选：队尾淘汰被新元素支配的下标、队首弹出过期下标，每个元素进出各一次，O(n) 求出全部滑动窗口的最大值与最小值。"
difficulty: "普及"
date: 2026-09-30 17:05
updated: 2026-10-06 00:41
toc: true
tags: ["单调队列", "滑动窗口", "最值", "python", "一本通"]
favorite: false
favorite_reason: ""
categories:
  - "一本通"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1542
---

[[TOC]]

## 题目描述

给定长度为 $n$ 的序列与窗口长度 $k$（$1 \le k \le n \le 10^5$），对每个窗口 $[i, i+k-1]$ 输出最大值与最小值，共 $n-k+1$ 行。

## 思路

用两条单调队列（存下标）分别维护窗口最大值（值递减）与最小值（值递增）。新元素入队时从队尾弹出被支配的候选；队首下标若已滑出窗口则弹出。每个下标进出各一次，均摊 $O(1)$，总时间 $O(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
