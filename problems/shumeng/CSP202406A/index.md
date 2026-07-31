---
oj: "shumeng"
problem_id: "CSP202406A"
title: "矩阵重塑（其一）"
description: "把矩阵按行优先展平成一维序列，再按新矩阵的列数重新解释每个元素的位置。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "矩阵"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202406A
---

[[TOC]]

### 题意

给定一个 $n\times m$ 矩阵和目标形状 $p\times q$，保证两个矩阵的元素总数相同。按照行优先顺序读取原矩阵，再按照行优先顺序填入新矩阵并输出。

### 思路

行优先重塑不会改变元素在线性序列中的顺序。将输入元素依次保存到一维数组 `value` 中，新矩阵第 $(i,j)$ 个位置对应的线性下标就是 $i\times q+j$，直接输出即可。

`brute.cpp` 保留了二维矩阵到一维数组的显式过程，帮助对应题目中的定义；本题规模很小，不需要额外的随机对拍。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个元素读取和输出一次，时间复杂度为 $O(nm)$，空间复杂度为 $O(nm)$。

### 总结

矩阵重塑只改变二维下标，不改变行优先线性序列；先固定线性序号，再用新列数计算行列下标即可。
