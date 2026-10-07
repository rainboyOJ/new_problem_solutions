---
oj: "roj"
problem_id: "3627"
title: "推销员"
description: "按推销疲劳值降序排序后，用前缀和与后缀最大值维护「A 前缀和 + 2×最远距离」的两种贪心决策，对每个 X 取较大者。"
difficulty: "普及"
date: 2026-10-02 11:36
updated: 2026-10-06 15:25
toc: true
tags: ["贪心", "排序", "前缀和", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/3627"
---

[[TOC]]

## 题目描述

死胡同入口一侧有 N 家住户，第 i 家距入口 S_i 米、推销可得疲劳值 A_i。对每个 X=1..N，从入口出发依次访问其中 X 家再原路返回，求「2×最远被访问距离 + 推销疲劳值之和」的最大值，并输出 N 行答案。输入第一行为 N，第二行为递增的 N 个 S_i，第三行为 N 个 A_i。样例 1 输入 `5 / 1 2 3 4 5 / 1 2 3 4 5`，输出 `15 19 22 24 25`。

## 思路

路径代价只由最远的住户决定，所以把选 X 家的最优方案按最远点分类。按 A 降序（A 相同则距离大者优先）排序，预处理前缀和 sum_i、前缀最远距离 q_i 和后缀最大值 h_i = max_{j≥i}(2S_j+A_j)，则每个 X 的答案为 max(sum_i + 2q_i, sum_{i-1} + h_i)，总复杂度 O(N log N)。

## 参考代码

@include-code(./main.cpp, cpp)
