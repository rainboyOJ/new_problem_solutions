---
oj: "noi_openjudge"
problem_id: "ch0105-32"
title: "求分数序列和"
description: "维护相邻两项的分子和分母递推，逐项累加分数序列。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["递推", "循环", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/32/
---

[[TOC]]

### 题意

分数序列首项为 $2/1$。若当前项为 $q_i/p_i$，则下一项满足 $q_{i+1}=q_i+p_i$、$p_{i+1}=q_i$。求前 $n$ 项之和。

### 思路

只需维护当前分子 `numerator` 和分母 `denominator`。先把当前分数加入 `total`，再用并行赋值更新为下一项：`numerator, denominator = numerator + denominator, numerator`。

并行赋值的右侧会先按旧值计算，所以不会在更新分子后误用新分子作为分母。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

循环 $n$ 次，时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

递推题常常不必保存整个序列，保留生成下一项所需的少量状态即可。
