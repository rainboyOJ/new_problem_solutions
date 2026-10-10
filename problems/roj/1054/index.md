---
oj: "roj"
problem_id: "1054"
title: "三角形判断"
description: "三边升序后只需判断短边之和是否严格大于最长边。"
difficulty: "入门"
date: 2026-09-29 16:34
updated: 2026-10-04 23:37
toc: true
tags: ["入门", "条件判断", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1054
---

[[TOC]]

## 题目描述

给定三个正整数表示三条线段长度，判断它们能否构成三角形：能输出 `yes`，否则输出 `no`。

输入一行三个正整数，空格分隔；输出 `yes` 或 `no`。

样例输入 `3 4 5`，样例输出 `yes`。

## 思路

把三边升序排序，定出最长边。此时三角形判定只剩下一条不等式：两条短边之和必须**严格**大于最长边；取等表示三边共线退化，应输出 `no`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
