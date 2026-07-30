---
oj: "noi_openjudge"
problem_id: "ch0101-07"
title: "输出浮点数"
description: "分别用固定小数、科学计数法和通用格式输出同一个双精度浮点数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["浮点数", "输出", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0101/07/
---

[[TOC]]

### 题意

对同一个双精度浮点数输出四行：默认 `%f` 形式、保留 5 位小数的 `%f` 形式、`%e` 科学计数法形式和 `%g` 通用形式。

### 思路

Python 的 `.6f` 对应默认 `%f` 的 6 位小数，`.5f` 对应保留 5 位小数；`.6e` 与 `.6g` 分别给出默认精度为 6 的科学计数法和通用格式。

题目样例中的指数部分固定为 3 位，例如 `e+001`。Python 默认会输出 `e+01`，因此把结果按 `e` 拆开，保留符号后把指数的绝对值补到 3 位。对于普通小数形式的 `%g`，辅助函数会原样返回。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

输出次数固定为 4 次，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

浮点题先区分“有效数字”和“小数位数”：`f` 控制固定小数位，`g` 控制有效数字，`e` 使用科学计数法。样例对指数位数有额外要求时，再单独格式化指数。
