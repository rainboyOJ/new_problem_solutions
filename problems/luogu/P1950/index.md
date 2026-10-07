---
oj: "luogu"
problem_id: "P1950"
title: "长方形"
description: "逐行构造空白高度，并用单调栈求所有以当前行结底的空白矩形数量。"
difficulty: "普及+/提高"
date: 2026-07-16 18:25
updated: 2026-10-06 07:45
toc: true
tags: ["单调栈", "组合计数", "矩阵", "python"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P2947"
    reason: "B 的递增栈沿用 A 教的单调栈弹出被挡住候选、保持栈单调的结算纪律，再叠加 (height,width_count) 合并等高宽度与子数组最小值贡献记账"
  - oj: "shumeng"
    problem_id: "CSP201312C"
    reason: "B 的矩形计数复用 A 教的「每根柱子作为最低高度的左右控制区间」这一步（直方图子数组最小值正由单调栈按控制区间统计），只是从求最大矩形面积变成把每个控制区间贡献求和，并叠加 A 未教的逐行高度转换与 (height,width_count) 合并宽度技巧。"
  - oj: "roj"
    problem_id: "3032"
    reason: "B 把 A 教的单调递增栈弹出时定出左右边界这一步搬到逐行直方图上，只是把结算最大面积换成用 width_count 合并等高宽度来累加子数组最小值之和"
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
