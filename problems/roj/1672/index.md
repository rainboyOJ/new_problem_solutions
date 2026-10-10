---
oj: "roj"
problem_id: "1672"
title: "种玉米"
description: "通过一次遍历找出二维网格中所有整数的最大值与最小值，计算两者之差即为玉米杆高度差。"
difficulty: "入门"
date: 2026-10-01 01:23
updated: 2026-10-06 01:45
toc: true
tags:
  - "模拟"
  - "极值"
favorite: false
favorite_reason: ""
categories:
  - "基础题"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1672
---

[[TOC]]

## 题目描述

给定 $m$ 行 $n$ 列的玉米杆高度（整数），求最高与最低玉米杆的高度差。$1 \le m,n \le 1000$。

## 思路

遍历所有高度，维护最大值与最小值，两者相减即为答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
