---
oj: "POJ"
problem_id: "2976"
title: "Dropping tests"
date: 2026-01-05 15:01
toc: true
tags: ["01分数规划"]
desc: "01分数规划入门题"
source: https://vjudge.net/problem/POJ-2976#author=Aurora5090
---

[[TOC]]

## 题目解析

- 二分性: 如果分数 x 可以达到, 那么$query_max_sum(x) >=0 $ 成立,则分数 $x_i < x$ 都可以成立,我们要使得x尽可能的大
- 答案范围: $[0,1]$

## 代码 

@include-code(./1.cpp, cpp)

