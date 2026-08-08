---
oj: "luogu"
problem_id: "P2880"
title: "[USACO07JAN] Balanced Lineup G"
description: "分别建立区间最小值和最大值 ST 表，让每次静态区间极差查询 O(1) 完成。"
difficulty: "普及/提高-"
date: 2026-01-17 20:25
toc: true
tags: ["ST表", "区间最值", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2880
---

[[TOC]]

### 题意

静态数组上回答大量区间最高值减最低值。

### 思路

ST 表第 `level` 层保存长度 $2^{level}$ 区间的最小值或最大值。查询 `[l,r]` 时取 `level=floor(log2(length))`，用左右两个允许重叠的长度 $2^{level}$ 区间覆盖查询范围；`min/max` 满足幂等性，重叠不会影响答案。

### Python 知识

- `array("i")` 紧凑保存各层数据，两个 ST 表总共只需 $O(n\log n)$ 个 32 位整数。
- 生成器直接构造下一层数组，不创建额外列表。
- 预处理 `logs[length]` 后，每次询问只做常数次下标访问。

### 代码

@include-code(./main.py, python)

### 复杂度

预处理 $O(n\log n)$，每次查询 $O(1)$，空间 $O(n\log n)$。

### 总结

静态、可重叠的区间最值查询是 ST 表的标准使用场景。
