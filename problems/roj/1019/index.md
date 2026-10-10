---
oj: "roj"
problem_id: "1019"
title: "浮点数向零舍入"
description: "向零舍入就是丢弃小数部分的截断语义，读入浮点数后直接转换为整数输出即可。"
difficulty: "入门"
date: 2026-09-29 13:31
updated: 2026-10-04 22:37
toc: true
tags: ["输入输出", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1019
---

[[TOC]]

## 题目描述

输入一个单精度浮点数，把它向零舍入到整数（正数向下舍入、负数向上舍入），输出一个整数。样例：输入 `2.3`，输出 `2`。

## 思路

向零舍入就是丢弃小数部分，如 $2.3 \to 2$、$-2.3 \to -2$。浮点数转整数正是这种截断语义，读入后直接转换输出即可，不要用向下取整或四舍五入。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
