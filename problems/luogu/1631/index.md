---
oj: "luogu"
problem_id: "P1631"
title: "序列合并"
description: "每个 A[i] 与整个 B 形成一条有序和序列，用堆归并取最小 n 个。"
difficulty: "普及+/提高"
date: 2026-07-16 21:00
toc: true
tags: ["多路归并", "二叉堆", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1631
---

[[TOC]]

### 题意

两个不降数组产生 $n^2$ 个两两和，输出最小的 `n` 个。

### 思路

固定 `A[i]` 后，`A[i]+B[0..]` 有序。把每行第一项放入堆；弹出某行第 `j` 项后，只补入同一行第 `j+1` 项，弹 `n` 次即可。

### Python 知识

- 堆项 `(sum,row,column)` 完整记录下一候选来源。
- `enumerate(first)` 同时生成行号和行基值。
- 输入有序，因此无需额外排序。

### 代码

@include-code(./main.py, python)

### 复杂度

时间 $O(n\log n)$，空间 $O(n)$。

### 总结

不要枚举 $n^2$ 个和；把矩阵每一行当作一条有序流即可。
