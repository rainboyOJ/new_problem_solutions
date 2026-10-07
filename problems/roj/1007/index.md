---
oj: "roj"
problem_id: "1007"
title: "计算(a+b)×c的值"
description: "读入三个整数 a,b,c，按 (a+b)×c 直接输出结果。"
difficulty: "入门"
date: 2026-09-29 12:42
updated: 2026-10-04 22:22
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1007
---

[[TOC]]

## 题目描述

给定三个整数 $a,b,c$（$-10{,}000<a,b,c<10{,}000$），计算 $(a+b)\times c$ 的值。输入一行三个整数；输出一个整数。

## 思路

按题面括号顺序，先加后乘，一步输出结果。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
