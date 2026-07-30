---
oj: "noi_openjudge"
problem_id: "ch0105-38"
title: "计算多项式的导函数"
description: "将每项系数乘以原指数，并按降幂顺序输出导函数系数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "数学", "数组", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/38/
---

[[TOC]]

### 题意

给出多项式从最高次到常数项的系数，输出其导函数的系数；若导函数为零，输出 `0`。

### 思路

输入系数 `C_n, C_{n-1}, ..., C_0` 已按降幂排列。前 $n$ 个系数依次对应指数 $n,n-1,\ldots,1$，导数系数就是“原系数乘原指数”。常数项导数为零，不输出。

当原多项式次数为 $0$ 时，单独输出 `0`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，存储输入和结果使用 $O(n)$ 空间。

### 总结

按降幂输入时，用递减的指数序列与系数配对即可直接落实求导公式。
