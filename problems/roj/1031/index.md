---
oj: "roj"
problem_id: "1031"
title: "反向输出一个三位数"
description: "反向即三段取余直出：个位、十位、剩余高位依次逐段打印，逐段输出天然保留前导零，C 的向零截断让负数也直接成立。"
difficulty: "入门"
date: 2026-09-29 14:40
updated: 2026-10-04 23:00
toc: true
tags: ["输入输出", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1031
---

[[TOC]]

## 题目描述

将一个三位数反向输出，例如输入 $358$，反向输出 $853$。输入是一个三位数 $n$；输出反向结果，低位零形成的前导零必须保留（如输入 $100$ 输出 $001$）。

## 思路

把"反向"直译成三段取余公式：个位段 $n \bmod 10$、十位段 $(n/10) \bmod 10$、剩余高位段 $n/100$，按顺序逐段打印。逐段输出天然保留前导零；C++ 的 `/`、`%` 向零截断，负数时三段各带负号也直接成立。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
