---
oj: "roj"
problem_id: "1010"
title: "计算分数的浮点数值"
description: "一次真除法得到双精度商，再用 printf(\"%.9f\") 固定小数位输出，四舍五入、补零、负号全部交给格式说明符。"
difficulty: "入门"
date: 2026-09-29 12:55
updated: 2026-10-04 22:22
toc: true
tags: ["输入输出", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1010
---

[[TOC]]

## 题目描述

两个整数 $a$ 和 $b$（$b \neq 0$）分别作为分子和分母，输入仅一行两个整数；输出分数 $a/b$ 的浮点数值（双精度浮点数），保留小数点后 9 位——不足 9 位补 0，第 10 位四舍五入，负数带负号。样例：输入 `5 7`，输出 `0.714285714`。

## 思路

一次真除法 `1.0 * a / b` 得到双精度商，再用 `printf("%.9f", x)` 固定小数位输出即可，四舍五入、补零、负号全部由格式说明符处理，不需要任何分支。注意不能整除，也不要先 `round` 再打印（会丢失尾随零）。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
