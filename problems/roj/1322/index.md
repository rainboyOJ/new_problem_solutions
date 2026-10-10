---
oj: "roj"
problem_id: "1322"
title: "【例6.4】拦截导弹问题(Noip1999)"
description: "最少非升子序列划分数等于最长严格上升子序列长度，用 tails 数组二分维护 LIS 即可。"
difficulty: "入门"
date: 2026-09-30 05:06
updated: 2026-10-05 09:41
toc: true
tags:
  - "动态规划"
  - "LIS"
  - "Dilworth定理"
  - "贪心"
favorite: false
favorite_reason: ""
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1322
---

[[TOC]]

## 题目描述

雷达依次给出 $n$（$1\leqslant n\leqslant 1000$）枚导弹飞来高度。一套拦截系统除第一发外，之后每一发都不能高于前一发。求拦截全部导弹最少需要配备多少套系统。

输入：一行依次飞来的高度（正整数，不超过 30000）。

输出：最少系统数 $k$。

样例输入：`389 207 155 300 299 170 158 65`，样例输出：`2`。

## 思路

严格上升的两枚导弹必须分到不同系统，因此最少系统数等于最长严格上升子序列长度（Dilworth 定理）。维护 `tails[len]` 表示长度为 `len` 的严格上升子序列的最小结尾高度，对每个高度二分找到第一个 `>=` 它的位置进行替换或延长，最终 `tail_cnt` 即为答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
