---
oj: "roj"
problem_id: "2028"
title: "usaco-2.2.3 循环数"
description: "从 M+1 起线性搜索，用位运算 O(L) 判定循环数：各位非零互异，且按下标跳格恰好走遍所有位回到起点。"
difficulty: "普及-"
date: 2026-10-01 04:05
updated: 2026-10-06 09:51
toc: true
tags:
  - 模拟
  - 枚举
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2028
---

[[TOC]]

## 题目描述

求严格大于 $M$ 的最小循环数。循环数要求十进制各位不含 $0$ 且两两不同；从下标 $0$ 开始，每步按当前位数字向右跳格并回卷，恰好走遍所有位后回到起点。

## 思路

从 $M+1$ 开始逐个整数枚举，先快速排除含 $0$ 或数字重复的情况，再 $O(L)$ 模拟跳格判是否走遍所有位；循环数最大为 $9682415$，超过即不存在。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
