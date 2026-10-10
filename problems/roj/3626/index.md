---
oj: "roj"
problem_id: "3626"
title: "[noip2015-普及] 求和"
description: "把三元组条件翻译成两端下标同奇偶且同色，按 (颜色, 奇偶) 分桶后用 (k-2)·Σia + Σi·Σa 闭式一次算出组内全部两两贡献。"
difficulty: "普及"
date: 2026-10-02 11:19
updated: 2026-10-06 15:30
toc: true
tags: ["python", "数学", "NOIP"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3626
---

[[TOC]]

## 题目描述

$n$ 格纸带各有颜色 $color_i$ 与数字 $number_i$，求所有满足 $x<y<z$、$x+z=2y$、$color_x=color_z$ 的三元组分数 $(x+z)(number_x+number_z)$ 之和模 10007（$n \le 10^5$）。

## 思路

$x+z=2y$ 要求 $x,z$ 同奇偶，按奇偶、颜色分组后，枚举每组内配对并累计 $(x+z)(number_x+number_z)$；展开后维护 $\sum x$、$\sum number$ 等前缀量即可 $O(n)$ 合计，对 10007 取模。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
