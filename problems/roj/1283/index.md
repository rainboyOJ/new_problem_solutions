---
oj: "roj"
problem_id: "1283"
title: "登山"
description: "按峰顶拆分：以每个景点为峰，正反各做一次 O(n^2) 的最长严格上升子序列 DP，ups[i]+downs[i]-1 的最大值即最多浏览景点数。"
difficulty: "普及-"
date: 2026-09-30 03:15
updated: 2026-10-05 07:50
toc: true
tags:
  - DP
  - LIS
  - 动态规划
favorite: false
favorite_reason: ""
categories:
  - 动态规划
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1283
---

[[TOC]]

## 题目描述

按编号递增的顺序浏览 $N$ 个景点，不能连续浏览海拔相同的两个景点，且一旦开始下山就不再向上走。给定 $N$（$2 \le N \le 1000$）和各景点海拔，求最多能浏览的景点数。

输入第一行为 $N$，第二行为 $N$ 个海拔；输出最多能浏览的景点数。样例输入 `8` 与 `186 186 150 200 160 130 197 220`，输出 `4`。

## 思路

即求最长的「先严格上升、后严格下降」子序列。枚举峰顶 $i$：`up[i]` 为以 $i$ 结尾的最长严格上升长度，`down[i]` 为从 $i$ 开始向右的最长严格下降长度（把序列反转后跑同一个 LIS，再把结果翻回原下标）。峰顶在两侧各被数一次，故答案为 $\max_i(up[i]+down[i]-1)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
