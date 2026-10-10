---
title: "【例1.1】计算机输出"
description: "非常基础的输出练习，直接输出指定的字符串。"
date: 2026-10-08 09:03
updated: 2026-10-08 09:03
tags:
  - 基础
  - 输出
favorite: false
favorite_reason: ""
difficulty: "入门"
oj: "roj"
problem_id: "5006"
source: "https://roj.ac.cn/problem/5006"
toc: true
categories:
  - 基础
showAtRbook: []
pre: []
common: []
recommend: []
---

[[TOC]]

## 形式化题目

无输入，直接输出指定的字符串 `Hello World!`。

## 正解

### 思路

这是一个最基础的编程练习题，目的是让初学者了解如何使用编程语言输出指定的字符串到屏幕。
在 C++ 中，我们可以使用 `std::cout` 或 `printf` 进行输出。
在 Python 中，我们可以使用 `print()` 函数进行输出。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**: $\mathcal{O}(1)$，仅进行一次输出操作。
- **空间复杂度**: $\mathcal{O}(1)$，不使用额外空间。

## 总结

这是一道非常基础的入门题目，熟悉编程语言的输出语法即可。本题的测试数据为自造。
