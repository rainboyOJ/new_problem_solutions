---
oj: "roj"
problem_id: "1044"
title: "判断是否为两位数"
description: "判断输入的正整数是否落在 [10, 99] 区间内，满足则输出 1，否则输出 0。"
difficulty: "入门"
date: 2026-09-29 16:32
updated: 2026-10-04 23:24
toc: true
tags: ["入门", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1044
---

[[TOC]]

## 题目描述

给定一个不超过 1000 的正整数，判断它是否为两位数（大于等于 10 且小于等于 99）。是输出 1，否则输出 0。

## 思路

用一次区间比较 `n >= 10 && n <= 99` 判定即可，成立输出 1，否则输出 0。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
