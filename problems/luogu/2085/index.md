---
oj: "luogu"
problem_id: "P2085"
title: "最小函数值"
description: "把每个递增二次函数看成有序序列，用堆做 n 路归并取前 m 项。"
difficulty: "普及/提高-"
date: 2026-07-16 21:00
toc: true
tags: ["多路归并", "二叉堆", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2085
---

[[TOC]]

### 题意

给出多个在正整数域递增的二次函数，输出所有函数值合并后的前 `m` 小。

### 思路

每个函数产生 `F(1),F(2),...` 一条有序序列。堆中先放每条序列第一项；弹出 `(value,function,x)` 后，输出它并压入同函数的 `x+1`，就是标准多路归并。

### Python 知识

- 堆元组自动按函数值优先排序，并用后续字段稳定打破平局。
- 局部 `value(function, x)` 集中表达二次式。
- `print(*answers)` 直接空格分隔输出。

### 代码

@include-code(./main.py, python)

### 复杂度

时间 $O((n+m)\log n)$，空间 $O(n+m)$（含答案）。

### 总结

看到许多单调序列的全局前若干小值，应优先想到“每路只保留当前头”的堆归并。
