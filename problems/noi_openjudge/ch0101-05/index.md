---
oj: "noi_openjudge"
problem_id: "ch0101-05"
title: "输出保留12位小数的浮点数"
description: "使用 .12f 以固定小数点形式输出双精度浮点数的 12 位小数。"
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
source: http://noi.openjudge.cn/ch0101/05/
---

[[TOC]]

### 题意

读入一个双精度浮点数，输出时小数点后必须恰好有 12 位。

### 思路

Python 的 `float` 通常就是 IEEE 754 双精度，可以直接读入。格式说明 `.12f` 会进行四舍五入，并补足末尾的零：`f"{value:.12f}"` 就是本题所需的输出。

不要用 `round` 再 `print`。`round` 得到的数在普通输出时会省略末尾零，不能保证 12 位小数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

只处理一个浮点数，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

固定小数位数优先使用 f-string 的 `f` 格式：`.12f` 同时负责舍入和补零。
