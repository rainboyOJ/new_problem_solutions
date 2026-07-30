---
oj: "noi_openjudge"
problem_id: "ch0106-15"
title: "阶乘和"
description: "递推维护当前阶乘并累加，利用 Python 任意精度整数计算阶乘和。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["高精度", "数学", "递推", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/15/
---

[[TOC]]

### 题意

计算 $S=1!+2!+\cdots+n!$，其中 $n\leqslant50$。

### 思路

维护当前 `factorial`。第 $i$ 轮乘以 $i$ 得到 $i!$，再加入 `total`。Python 的整数会自动扩展，能直接保存阶乘和。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

循环次数为 $n$；实际运行时间还受高精度整数位数增长影响，额外空间为结果所需空间。

### 总结

阶乘和仍然只需保存一个当前阶乘和一个累计和，无需存储所有阶乘。
