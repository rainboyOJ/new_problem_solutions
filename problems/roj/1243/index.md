---
oj: "roj"
problem_id: "1243"
title: "月度开销"
description: "二分最大段和，用贪心验证能否在不超过 M 段内完成划分。"
difficulty: "普及"
date: 2026-09-30 01:19
updated: 2026-10-05 06:30
toc: true
tags:
  - 二分答案
  - 贪心
  - 前缀和
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1243
---

[[TOC]]

## 题目描述

农夫约翰记录下接下来 N 天每天的开销（1 ≤ N ≤ 100,000，每天的开销 ≤ 10,000）。他要把这 N 天恰好分成 M（1 ≤ M ≤ N）个连续的财政周期，使开销最多的那个周期的开销尽可能小。输入第一行为 N、M，接下来 N 行每天的开销；输出最大月度开销的最小值。

样例：N=7, M=5, 开销 = 100, 400, 300, 100, 500, 101, 400，最优划分为 [100,400] | [300,100] | [500] | [101] | [400]，最大月度开销为 500。

## 思路

二分最大段和 X，贪心地从左到右把每段尽量延长（加到会超 X 就开新段），看最少段数是否 ≤ M；可行性随 X 单调，在 [max(ai), sum(ai)] 上二分即可。

## 参考代码

@include-code(./main.cpp, cpp)
