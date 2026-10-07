---
oj: "roj"
problem_id: "1061"
title: "求整数的和与均值"
description: "线性扫描累加求和，再用总和除以个数得到平均值。"
difficulty: "入门"
date: 2026-07-06 10:30
updated: 2026-10-04 23:49
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

## 题目描述

读入 $n$（$1 \le n \le 10000$）个整数（每个绝对值不超过 $10000$），求它们的和与均值。输入第一行是整数 $n$，接下来 $n$ 行每行一个整数；输出共一行，先输出和，再输出均值（保留到小数点后 5 位），中间用单个空格分隔。样例：输入 `4 / 344 / 222 / 343 / 222`，输出 `1131 282.75000`。

## 思路

顺序读入 $n$ 个整数，用 `total` 累加；全部读完即得总和，再做 `total / n` 并按 `%.5f` 输出均值即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)