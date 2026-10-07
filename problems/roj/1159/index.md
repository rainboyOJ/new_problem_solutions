---
oj: "roj"
problem_id: "1159"
title: "斐波那契数列"
description: "题面数列从 0 开始，第 n 项就是零起编号的 F(n-1)；用记忆化递归按递推式求，每个下标只算一次。"
difficulty: "入门"
date: 2026-09-29 21:26
updated: 2026-10-05 03:50
toc: true
tags: ["入门", "递推", "数学", "递归", "python"]
favorite: false
favorite_reason: ""
categories:
  - 数学
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1159
---

[[TOC]]

## 题目描述

题面数列为 $0,1,1,2,3,5,8,13,\ldots$，即首项为 $0$ 的斐波那契数列。给定正整数 $n$，用递归函数求第 $n$ 项。

**输入**：一个正整数 $n$。**输出**：第 $n$ 项。样例输入 `3`，输出 `1`（注意数列首项是 $0$，不是 $1$）。

## 思路

按定义 $F(0)=0$、$F(1)=1$、$F(i)=F(i-1)+F(i-2)$ 写递归，并为每个下标加记忆化，使同一项只算一次；题面数列首项是 $0$，第 $n$ 项对应 $F(n-1)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
