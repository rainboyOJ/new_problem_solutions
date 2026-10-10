---
oj: "roj"
problem_id: "1008"
title: "计算(a+b)/c的值"
description: "直接用 C++ 整数除法计算 (a+b)/c，向零取整的语义与题目一致，一步 O(1) 求解。"
difficulty: "入门"
date: 2026-09-29 12:42
updated: 2026-10-04 22:22
toc: true
tags: ["输入输出", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1008
---

[[TOC]]

## 题目描述

给定三个整数 $a,b,c$（$|a|,|b|,|c|<10000$，$c\neq 0$），求 $\dfrac{a+b}{c}$ 的值并舍去小数部分。输入一行三个整数，用一个空格隔开；输出一行，即表达式的值。样例输入 `1 1 3`，样例输出 `0`。

## 思路

直接算 `(a+b)/c`：C/C++ 的整数除法是向零取整，正是本题要求的取整方式，输出即可。注意不要换成向下取整，否则异号时会比答案小 1。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
