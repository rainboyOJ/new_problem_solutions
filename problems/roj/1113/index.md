---
oj: "roj"
problem_id: "1113"
title: "不与最大数相同的数字之和"
description: "先求序列最大值，再对所有不等于最大值的数求和；注意最大值重复出现时要全部排除。"
difficulty: "入门"
date: 2026-09-29 19:26
updated: 2026-10-05 02:16
toc: true
tags: ["入门", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1113
---

[[TOC]]

## 题目描述

给定 n（n ≤ 100，|a_i| ≤ 10^6）个整数，输出除去所有等于最大值的数后剩余数字之和。第一行 n，第二行 n 个整数；输出一行整数。

样例输入：`3\n1 2 3`，样例输出：`3`。

## 思路

两遍扫描：第一遍求最大值，第二遍把不等于最大值的数累加；最大值按值整体排除，重复出现的也要全部去掉。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)