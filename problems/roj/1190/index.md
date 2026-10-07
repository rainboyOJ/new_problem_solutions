---
oj: "roj"
problem_id: "1190"
title: "上台阶"
description: "按最后一步跨 1/2/3 阶分类得三阶线性递推，先打表再回答多组询问。"
difficulty: "入门"
date: 2026-09-29 22:51
updated: 2026-10-05 04:48
toc: true
tags: ["入门", "递推", "动态规划", "记忆化", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1190
---

[[TOC]]

## 题目描述

楼梯有 n（0 < n < 71）阶台阶，一步可上 1/2/3 阶，求走法总数。多行输入，每行一个 n，以 0 结束，每行输出对应方案数。样例：输入 `1 2 3 4 0` 输出 `1 2 4 7`。

## 思路

按最后一步跨 1/2/3 阶分三类得 $w(n)=w(n-1)+w(n-2)+w(n-3)$，边界 $w(0)=w(1)=1, w(2)=2$；先递推打表 $w[0..70]$，询问时 $O(1)$ 查表。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)