---
oj: "roj"
problem_id: "1133"
title: "输出亲朋字符串"
description: "把字符串看成环，每位输出字符是原串该位与下一位（末位绕回首位）的 ASCII 值之和。"
difficulty: "入门"
date: 2026-09-29 20:14
updated: 2026-10-05 02:58
toc: true
tags: ["入门", "字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1133
---

[[TOC]]

## 题目描述

给定长度 $2 \le n \le 100$ 的字符串 $s$。亲朋字符串 $s_1$ 的第 $i$ 个字符为 $s_i$ 与 $s_{(i+1)\bmod n}$ 的 ASCII 值之和对应的字符（末位绕回首位）。输出 $s_1$。

样例：输入 `1234`，输出 `cege`。

## 思路

按定义逐位模拟：对每一位 $i$，用取模得到环形下一位，两字符 ASCII 值相加即为输出字符。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
