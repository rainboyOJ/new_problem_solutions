---
oj: "luogu"
problem_id: "P6492"
title: "[COCI 2010/2011 #6] STEP"
description: "维护二进制字符序列的最长交替连续子串，支持单点翻转。"
difficulty: "普及+/提高"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "字符串", "交替序列", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P6492
---

[[TOC]]

### 题意

初始全为 `L`，每次翻转一个位置的 `L/R`，输出最长相邻字符交替的连续子串长度。

### 思路

节点保存首字符、尾字符、交替前缀、交替后缀和最大交替段。合并时只有左尾和右首不同，跨越中点的后缀与前缀才能拼接；若整个左（右）段都是交替段，前（后）缀也可以延长。

### Python 知识

- `^= 1` 是布尔状态翻转的简洁写法。
- 初始化全相同序列时不必逐叶建值，只需把每个节点的长度作为交替前后缀。
- 首尾状态用 `bytearray`，长度统计用 `array("i")`，大规模节点也能保持紧凑。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次单点翻转 `O(log n)`，空间 `O(n)`。

### 总结

“交替”只依赖相邻边界是否不同，因此首尾字符加四个长度统计量就足够合并。
