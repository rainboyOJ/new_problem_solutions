---
oj: "roj"
problem_id: "1022"
title: "整型与布尔型的转换"
description: "两次类型转换等价于一次非零判断：int → bool 把非零压成真、零为假，bool → int 再把真/假编码回 1/0，即 n 不等于 0 则输出 1，否则输出 0。"
difficulty: "入门"
date: 2026-09-29 13:42
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
source: https://roj.ac.cn/problem/1022
---

[[TOC]]

## 题目描述

给定一个整数 $n$，先把它赋给布尔型变量，再把该布尔型变量的值赋回整型变量，求最终得到的整数。

输入一个整数；输出经过两次转换后的整数。数据范围为整型。

样例：输入 `3`，输出 `1`。

## 思路

`bool(n)` 只保留“是否非零”，`int(True)=1`、`int(False)=0`。因此非零整数输出 1，0 输出 0；负数也是非零，同样输出 1。

## 参考代码

@include-code(./main.cpp, cpp)
