---
oj: "roj"
problem_id: "1061"
title: "求整数的和与均值"
description: "直接线性扫描所有整数，累加求和后除以个数得到平均值。"
difficulty: "入门"
date: 2026-07-06 10:30
updated: 2026-09-29 16:55
toc: true
tags: ["模拟", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1061
---

[[TOC]]

## 形式化题目

给定一个整数 $n$ 和 $n$ 个整数 $a_1, a_2, \dots, a_n$，要求输出它们的和 $S = \sum_{i=1}^{n} a_i$ 与平均值 $\bar{a} = S / n$（保留 5 位小数）。

### 样例

输入：

```
4
344
222
343
222
```

输出：

```
1131 282.75000
```

## 正解

### 思路

按顺序读入每个整数，维护一个累加器 `total`。读完全部数据后，`total` 就是所有数的和；再用 `total / n` 得到平均值，按 `%.5f` 的格式输出即可。

本题数据范围很小，$n \leqslant 10000$，直接线性扫描的复杂度已经完全足够，不需要额外优化。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，需要遍历所有 $n$ 个整数一次。
- 空间复杂度：$O(1)$，只使用常数个额外变量。

## 总结

求和与均值是最基础的线性扫描问题：用一个累加器维护总和，最后做一次除法并格式化输出。
