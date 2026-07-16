---
oj: "luogu"
problem_id: "P2572"
title: "[SCOI2010] 序列操作"
description: "线段树用赋值和翻转懒标记维护 01 序列的计数与最长连续 1。"
difficulty: "提高"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "01序列", "懒标记", "区间翻转", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2572
---

[[TOC]]

### 题意

对 01 序列区间赋 0、赋 1、取反，并查询区间 1 的数量或最长连续 1。

### 思路

节点同时保存 1 和 0 的数量、前缀、后缀、最大连续段。翻转时交换两套统计量；赋值时直接设置对应套统计量并清除旧标记。赋值标记优先级高于翻转，向下传递时先赋值再翻转。

### Python 知识

- `bytearray` 保存翻转标记，`assigned = -1` 表示没有赋值标记。
- `array("i")` 紧凑保存 0/1 的八组区间统计量。
- 元组返回 `(sum, prefix, suffix, best, length)`，查询部分区间可以复用同一套合并公式。
- 对称维护 0/1 统计量，翻转操作只需交换列表中的两个值。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次更新或查询 `O(log n)`，空间 `O(n)`。

### 总结

复杂区间操作的核心是让每个懒标记都能在节点信息上“就地完成”，而不是下传到每个叶子。
