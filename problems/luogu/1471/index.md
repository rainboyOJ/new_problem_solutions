---
oj: "luogu"
problem_id: "P1471"
title: "方差"
description: "线段树同时维护区间和与平方和，用懒标记支持区间加和方差查询。"
difficulty: "普及+/提高"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "懒标记", "方差", "浮点数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1471
---

[[TOC]]

### 题意

支持区间每项加上实数，查询区间平均数或方差，结果保留四位小数。

### 思路

方差可写成 `平均(x^2) - 平均(x)^2`，所以节点维护 `sum = Σx` 和 `squared = Σx²`。区间加 `d` 时：

`sum' = sum + length*d`，`squared' = squared + 2*d*sum + length*d²`。

代码先更新 `sum`，再用新旧关系计算平方和，并把 `d` 累加到懒标记。

### Python 知识

- 输入数值用 `float`，输出使用格式化表达式 `f"{value:.4f}"`。
- `array("d")` 紧凑保存双精度节点字段，避免大量浮点对象。
- 先保存区间长度 `count`，平均数和方差公式更直观。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

建树 `O(n)`，每次操作 `O(log n)`，空间 `O(n)`。

### 总结

遇到方差查询，先把定义改写成一阶矩和二阶矩，区间加就能在线维护。
