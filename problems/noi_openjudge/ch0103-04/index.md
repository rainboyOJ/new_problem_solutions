---
oj: "noi_openjudge"
problem_id: "ch0103-04"
title: "带余除法"
description: "按 C/C++ 向零整数除法计算商，再由 a-q*b 得到余数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "类型转换", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/04/
---

[[TOC]]

### 题意

输入被除数和非零除数，输出 C/C++ 默认整数除法的商和余数。

### 思路

先按向零规则求商 $q$，再用 $r=a-qb$ 计算余数。这样余数一定与被除数满足等式，也避免 Python `%` 对负数的符号规则和 C++ 不同。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

跨语言处理除法时，先定义商的舍入方向，再由等式恢复余数最稳妥。
