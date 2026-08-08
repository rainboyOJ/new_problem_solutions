---
oj: "luogu"
problem_id: "P1950"
title: "长方形"
description: "逐行构造空白高度，并用单调栈求所有以当前行结底的空白矩形数量。"
difficulty: "普及+/提高"
date: 2026-07-16 18:25
toc: true
tags: ["单调栈", "组合计数", "矩阵", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1950
---

[[TOC]]

### 题意

统计网格中完全由 `.` 组成的轴对齐子矩形数量。

### 思路

逐行维护每列连续空白高度。固定当前行为矩形下边界时，选择一段连续列的可选高度数等于这段高度的最小值，所以要计算直方图所有子数组最小值之和。

递增栈保存 `(height, width_count)`。弹出更高或相等项时，从 `ending_here` 中删掉它对所有对应左端点的贡献，并把这些左端点合并给当前高度。每处理一列，`ending_here` 就是所有以该列结尾矩形数。

### Python 知识

- 直接遍历字节行，`.` 的字节值是 46，省去字符解码。
- 栈中把相同高度用 `width_count` 合并，避免逐个左端点维护。
- Python 整数可直接保存最多约 $10^{12}$ 的答案。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(nm)$，空间复杂度 $O(m)$。

### 总结

矩形计数转成“每行直方图的所有子数组最小值之和”。
