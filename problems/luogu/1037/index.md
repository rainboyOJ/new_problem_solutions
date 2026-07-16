---
oj: "luogu"
problem_id: "P1037"
title: "[NOIP 2002 普及组] 产生数"
description: "对十个数字求变换传递闭包，再把每一位的可达数字数相乘。"
difficulty: "普及-"
date: 2026-07-17 03:00
toc: true
tags: ["传递闭包", "乘法原理", "位运算", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1037
---

[[TOC]]

### 题意

每一位数字可按规则变换任意次，求整个整数能产生多少种不同结果。

### 思路

十个数字上做传递闭包，`reachable[d]` 得到数字 `d` 最终可变成的集合。不同数位独立，根据乘法原理把每一位集合大小相乘。

### Python 知识

- 每个数字集合只需一个整数位掩码。
- `bit_count()` 直接求可达数字种数。
- Python 大整数能直接保存最多 30 位数字产生的巨大答案。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

闭包是常数规模，扫描数字串 `O(len(n))`。

### 总结

每位独立选择时，先求单个符号的闭包，再用乘法原理组合。
