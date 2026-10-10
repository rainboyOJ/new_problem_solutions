---
oj: "roj"
problem_id: "1153"
title: "绝对素数"
description: "枚举所有两位数，输出自身与十位个位对换后均为素数的数。"
difficulty: "入门"
date: 2025-01-12 11:47
updated: 2026-10-05 03:44
toc: true
tags:
  - 素数
  - 枚举
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1153"
---

[[TOC]]

## 题目描述

一个自然数是素数，且它的十位与个位对换后仍是素数，则称为绝对素数。求所有二位绝对素数，按从小到大顺序输出，每个数占一行。

## 思路

枚举 $10$ 到 $99$ 的每个数，用试除法判断它自身以及十位个位对换后的数是否都为素数，若是则输出。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
