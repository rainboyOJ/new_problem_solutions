---
oj: "roj"
problem_id: "1081"
title: "分苹果"
description: "n 个人拿互不相同且至少 1 个苹果，总和最小为 n(n+1)/2。"
difficulty: "入门"
date: 2026-09-29 18:01
updated: 2026-10-05 00:27
toc: true
tags: ["入门", "数学", "等差数列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1081
---

[[TOC]]

## 题目描述

把一堆苹果分给 $n$ 个小朋友，要求每个人至少拿到 1 个且每人拿到的苹果数互不相同，问这堆苹果最少有多少个。$1 \leqslant n \leqslant 1000$。

输入：一个正整数 $n$。输出：满足条件的最少苹果个数。

样例输入 `8` → 样例输出 `36`。

## 思路

n 个互不相同的正整数最小的一组就是 $1,2,\ldots,n$，总和即等差数列求和 $\frac{n(n+1)}{2}$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)