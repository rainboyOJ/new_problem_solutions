---
oj: "POJ"
problem_id: "2976"
title: "Dropping tests"
difficulty: "普及+/提高"
date: 2026-01-05 15:01
updated: 2026-06-21 21:34
toc: true
tags: ["01分数规划"]
desc: "01分数规划入门题"
pre:
  - oj: "luogu"
    problem_id: "P1873"
    reason: "先掌握二分答案的 check 函数设计和单调性，再理解分数规划中 D(x) = a_i - x*b_i 的转换思维。"
common:
  - oj: "luogu"
    problem_id: "P3199"
    reason: "同为分数规划问题，POJ 2976 用贪心排序验证，P3199 用 SPFA 判负环验证，对比不同检验手段。"
source: https://vjudge.net/problem/POJ-2976#author=Aurora5090
---

[[TOC]]

## 题目解析

- 二分性: 如果分数 x 可以达到, 那么$query_max_sum(x) >=0 $ 成立,则分数 $x_i < x$ 都可以成立,我们要使得x尽可能的大
- 答案范围: $[0,1]$

## 代码 

@include-code(./1.cpp, cpp)

