---
oj: "roj"
problem_id: "1047"
title: "判断能否被3，5，7整除"
description: "沿 3、5、7 从小到大依次检查整除，能整除就按顺序输出、空格分隔，一个都不行输出 n。"
difficulty: "入门"
date: 2026-09-29 16:10
updated: 2026-10-04 23:29
toc: true
tags: ["入门", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1047
---

[[TOC]]

## 题目描述

给定一个整数，判断它能否被 3、5、7 整除：同时被三个整除输出 `3 5 7`；只被其中两个整除输出这两个数，小的在前；只被其中一个整除输出这个除数；都不能整除输出小写 `n`。

输入一行一个整数（可能为负数），输出一行按上述规则给出结果。

样例输入：

```
105
```

样例输出：

```
3 5 7
```

## 思路

把候选除数按 3、5、7 从小到大排好，依次检查 `n % d == 0`，能整除就直接输出并用空格分隔，"小的在前"由检查顺序自然保证，题面的四种情形统一成这一趟顺序检查。负数输入时余数符号跟随被除数，但"余数为 0"当且仅当整除，判据依然安全；一个都整除不了时输出 `n`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
