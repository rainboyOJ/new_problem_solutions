---
oj: "roj"
problem_id: "1021"
title: "打印字符"
description: "读入一个 ASCII 码值，用 C++ 的 %c 输出对应可见字符。"
difficulty: "入门"
date: 2026-09-29 13:41
updated: 2026-10-04 22:43
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1021
---

[[TOC]]

## 题目描述

输入一个整数，即字符的 ASCII 码，保证存在对应的可见字符。输出相对应的字符。

输入格式：一个整数，即字符的 ASCII 码。

输出格式：一行，包含相应的字符。

样例输入 `65`，样例输出 `A`。

## 思路

ASCII 码值和可见字符一一对应，读入整数后用 `printf("%c", code)` 直接把码值按字符输出即可。注意 `%c` 要求 `int` 类型的码值，所以码值用 `int` 保存避免类型转换。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
