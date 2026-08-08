---
oj: "luogu"
problem_id: "P5522"
title: "[yLOI2019] 棠梨煎雪"
description: "线段树按位合并区间字符串的 0/1 约束，统计所有兼容二进制串的数量。"
difficulty: "省选/提高"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "位运算", "字符串", "异或", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5522
---

[[TOC]]

### 题意

每封信是由 `0/1/?` 组成的字符串，区间内所有信件必须可能对应同一个二进制串；支持修改一封信，并把所有查询答案异或后输出。

### 思路

对每个字符串记录两个位掩码：出现 `0` 的位置集合 `zeros`、出现 `1` 的位置集合 `ones`。区间合并分别按位或；若 `zeros & ones` 非零，某一位同时被固定为 0 和 1，答案为 0。否则没有被固定的位置都可自由选择，答案是 `2 ** (n - (zeros | ones).bit_count())`。

### Python 知识

- `int` 位运算一次处理最多 30 个位置。
- 迭代线段树查询避免递归，适合最多百万次操作。
- `bit_count()` 和 `1 << k` 直接表达自由位数量与方案数。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次修改或查询 `O(log m)`，编码每个字符串 `O(n)`，空间 `O(m)`。

### 总结

把字符串约束转换为两个集合，区间问题就变成位掩码的 OR 与冲突检测。
