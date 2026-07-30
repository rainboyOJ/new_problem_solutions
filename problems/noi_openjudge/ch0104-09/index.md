---
oj: "noi_openjudge"
problem_id: "ch0104-09"
title: "判断能否被3，5，7整除"
description: "按 3、5、7 的固定顺序收集可整除的数，再用空格连接输出。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/09/
---

[[TOC]]

### 题意

依次输出能整除输入数的 3、5、7；若一个也没有，输出 `n`。

### 思路

按题目要求的顺序遍历 `(3, 5, 7)`，列表推导式只保留能整除的数。结果非空时 `" ".join(...)` 自动控制空格；空列表时输出 `n`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

只检查三个除数，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

当多个条件的输出规则一致时，先收集结果再统一格式化，比枚举所有组合更容易维护。
