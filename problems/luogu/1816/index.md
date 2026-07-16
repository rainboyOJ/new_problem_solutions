---
oj: "luogu"
problem_id: "P1816"
title: "忠诚"
description: "建立区间最小值 ST 表，以两个允许重叠的 2 的幂区间回答静态 RMQ。"
difficulty: "普及/提高-"
date: 2026-07-16 18:28
toc: true
tags: ["ST表", "RMQ", "倍增", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1816
---

[[TOC]]

### 题意

给定一个不再修改的数组，多次询问闭区间 `[left, right]` 内的最小值。

### 思路

`table[level][i]` 保存从 `i` 开始、长度为 $2^{level}$ 的区间最小值。相邻两块长度 $2^{level-1}$ 的区间合并即可得到下一层。

查询长度为 `length` 的区间时，令 `level = floor(log2(length))`。取查询区间最左和最右的两个长度 $2^{level}$ 的块；它们可能重叠，但 `min` 重复计算元素不会改变结果。

### Python 知识

- `array("i")` 比 Python 整数列表紧凑，适合保存 $O(n\log n)$ 个 ST 表值。
- `logs[i] = logs[i // 2] + 1` 可线性预处理所有整数对数。
- 生成器表达式直接交给 `array`，避免先创建中间列表。
- `print(*answers)` 自动按空格输出所有询问答案。

### 代码

@include-code(./main.py, python)

原有 C++ 版本保留如下：

@include-code(./1.cpp, cpp)

### 复杂度

预处理时间与空间均为 $O(n\log n)$，每次询问 $O(1)$。

### 总结

数组静态、询问很多、运算允许区间重叠时，ST 表是比线段树更直接的选择。
