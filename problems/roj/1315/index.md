---
oj: "roj"
problem_id: "1315"
title: "集合的划分"
description: "第二类 Stirling 数一维滚动递推，结果按 64 位有符号 long long 溢出处理。"
difficulty: "入门"
date: 2026-09-30 04:41
updated: 2026-10-04 13:25
toc: true
tags: ["dp", "组合数学", "斯特林数", "滚动数组"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1315
---

[[TOC]]

## 题目描述

把 $n$ 个互不相同的元素划分成 $k$ 个非空互不相交的子集，求划分数 $S(n,k)$（$0<k\leqslant n<30$）。输入一行 $n,k$，输出 $S(n,k)$。样例：输入 `10 6` 输出 `22827`。

## 思路

按第 $n$ 个元素去向分：单独成盒 $S(n-1,k-1)$ 种，或放入已有 $k$ 盒之一共 $k\cdot S(n-1,k)$ 种，得递推 $S(n,k)=S(n-1,k-1)+k\cdot S(n-1,k)$；用一维数组逆序滚动在 $O(n\cdot k)$ 内求出答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)