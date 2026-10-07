---
oj: "roj"
problem_id: "1115"
title: "直方图"
description: "桶计数一次扫描：把值当下标建桶，按序输出 0 到最大值的频数，没出现的桶天然为 0。"
difficulty: "入门"
date: 2026-09-29 19:26
updated: 2026-10-05 02:26
toc: true
tags: ["入门", "桶计数", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1115
---

[[TOC]]

## 题目描述

给定一个非负整数数组，统计里面每一个数的出现次数，只统计到数组里最大的数 $F_{\max}$（$F_{\max} < 10000$）。输入第一行是数组大小 $n$（$1 \le n \le 10000$），紧接着一行是数组的 $n$ 个元素。按顺序输出 $0, 1, \dots, F_{\max}$ 中每个数的出现次数，一行一个数；没有出现过的数输出 $0$。

样例：输入 `5` 和 `1 1 2 3 1`，最大值是 3，因此统计 $\{0,1,2,3\}$，输出依次为 `0 3 1 1`（每行一个数）。

## 思路

把值当下标开桶，读入时给桶 $A_i$ 加一，一遍扫描就同时得到全部频数，复杂度 $O(n + F_{\max})$。桶的初值就是 0，天然覆盖"没出现过输出 0"；统计到 $F_{\max}$ 为止，共输出 $F_{\max}+1$ 行。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
