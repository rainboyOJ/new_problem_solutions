---
oj: "roj"
problem_id: "8006"
title: "进制转换"
description: "以十进制为桥梁做任意进制互转：按权解析 a 进制，再除基取余压成 b 进制，两段各线性一遍。"
difficulty: "入门"
date: 2026-10-02 16:22
updated: 2026-10-06 16:42
toc: true
tags: ["进制转换", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/8006
---

[[TOC]]

## 题目描述

给定 $n$ 个用例，每行给出字符串 $S$ 与进制 $a,b$（$2\le a,b\le 36$）。$S$ 是 $a$ 进制数，数符为 `0-9A-Z`，求数值相等的 $b$ 进制表示。$S$ 的十进制值 $\le 2^{63}-1$。输入第一行 $n$，接下来 $n$ 行每行 `S a b`；输出 $n$ 行转换结果。样例：`123ABC 16 2` → `100100011101010111100`。

## 思路

以十进制为桥梁：先按权展开把 $a$ 进制转成十进制 `ll`，再反复除 $b$ 取余、倒序拼接得到 $b$ 进制。注意数值为 $0$ 时直接输出 `0`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
