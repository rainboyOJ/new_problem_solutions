---
oj: "roj"
problem_id: "1331"
title: "【例1-2】后缀表达式的值"
description: "逐字符扫描后缀表达式，数字拼装入栈，运算符弹出右和左两个数把结果压回。"
difficulty: "入门"
date: 2026-09-30 05:43
updated: 2026-10-05 10:01
toc: true
tags: ["栈", "表达式求值", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1331
---

[[TOC]]

## 题目描述

从键盘读入一行后缀表达式，运算数是 `0-9` 组成的非负整数，运算符是 `+ - * /`，以 `@` 结束。运算数之间用空格隔开，但**运算符可以连写**（如 `+*-`）；长度小于 250，中间值与结果绝对值 $<2^{64}$，除法保证整除，输入保证合法。
样例输入：`16 9 4 3 +*-@`，样例输出：`-47`（对应中缀 $16 - 9 \times (4 + 3)$）。

## 思路

逐字符扫描：数字位用 `number = number*10 + 位` 边扫边拼多位数并设 `reading` 标志防止未读完的数提前入栈；遇到非数字位先结算可能存在的运算数，然后**正面枚举**四种之一才归约（弹出右、弹出左，算完压回），其它字符一律当分隔符；`@` 之后不看，扫描结束对 `reading` 收尾入栈。复杂度 $O(L)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)