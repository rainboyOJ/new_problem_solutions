---
oj: "roj"
problem_id: "1093"
title: "计算多项式的值"
description: "用前缀积递推把 O(n²) 的重复乘幂压成 O(n)，并保持自低次到高次的左折叠次序，使浮点结果与判题数据一致。"
difficulty: "入门"
date: 2026-09-29 18:48
updated: 2026-10-05 00:49
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1093
---

[[TOC]]

## 题目描述
求多项式 $x^n+x^{n-1}+\cdots+x+1$ 的值，输入单精度浮点数 $x$ 和正整数 $n$（$n\le 10^6$），结果保留两位小数。样例：输入 `2.0 4`，输出 `31.00`。

## 思路
维护前缀积 $p$，初始 $p=1$（即 $x^0$），每步把 $p$ 累加进答案再令 $p\gets p\cdot x$，一次扫描即可得到所有 $x^k$ 和部分和，避免对每个 $k$ 重新乘出 $x^k$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
