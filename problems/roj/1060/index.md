---
oj: "roj"
problem_id: "1060"
title: "均值"
description: "按定义 sum/n 求均值，用 fixed+setprecision(4) 定点输出 4 位小数。"
difficulty: "入门"
date: 2026-09-29 16:45
updated: 2026-10-04 23:49
toc: true
tags: ["入门", "模拟", "浮点输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1060
---

[[TOC]]

## 题目描述

给定 $n$（$n<100$）个绝对值不超过 $1000$ 的浮点数，求其均值，结果精确到小数点后 4 位（定点格式，末尾补零）。

输入第一行是整数 $n$，第二行是 $n$ 个浮点数；输出一行均值。

## 思路

直接累加求和再除以 $n$，用 `fixed` 和 `setprecision(4)` 保留 4 位小数输出。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
