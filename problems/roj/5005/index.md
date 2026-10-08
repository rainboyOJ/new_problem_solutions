---
title: "【例4.1】for循环求和"
date: 2026-10-08 09:02
updated: 2026-10-08 09:02
oj: roj
problem_id: "5005"
source: "https://roj.ac.cn/problem/5005"
description: "使用简单的 for 循环计算 1 到 n 的累加和"
difficulty: "入门"
categories:
  - 基础算法
tags:
  - 循环结构
showAtRbook: []
pre: []
common: []
recommend: []
toc: true
favorite: false
favorite_reason: ""
---

[[TOC]]

## 形式化题目

给定一个整数 $n$，计算并输出等差数列 $1, 2, 3, \ldots, n$ 的前 $n$ 项和，即求 $\sum_{i=1}^{n} i$。要求使用 `for` 循环实现。

## 正解

### 思路

这是一道非常基础的循环练习题。题目明确要求使用 `for` 循环。因此，我们只需要初始化一个累加变量 `sum` 为 0，然后通过 `for` 循环让循环变量 `i` 从 1 遍历到 `n`，在每次循环中将 `i` 加到 `sum` 上即可。由于 $n \le 100$，最大和为 $\frac{100 \times 101}{2} = 5050$，使用普通的 32 位整型变量 (`int`) 就足够了，不会发生溢出。

### 代码

@include-code(./main.py, python)
@include-code(./main.cpp, cpp)

### 复杂度

- **时间复杂度**: $O(n)$。循环执行了 $n$ 次。
- **空间复杂度**: $O(1)$。只使用了常数个整型变量 `n` 和 `sum`。

## 总结

基础的 `for` 循环结构应用。注意累加器变量在循环前必须初始化为 `0`。虽然数学上可以直接用等差数列求和公式 $O(1)$ 算出答案，但作为循环语法的练习题，老老实实写一遍 `for` 循环是初学者巩固语法的正确方式。