---
oj: "roj"
problem_id: "1641"
title: "「一本通 6.5 例 1」矩阵 A×B"
description: "按矩阵乘法定义，三重循环直接计算结果矩阵每个元素。"
difficulty: "入门"
date: 2026-09-30 23:31
updated: 2026-10-06 01:29
toc: true
tags:
  - 矩阵
  - 模拟
favorite: false
favorite_reason: ""
categories:
  - 线性代数
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1641
---

[[TOC]]

## 题目描述

给定 $n \times m$ 矩阵 $A$ 与 $m \times p$ 矩阵 $B$，按定义 $c_{ij}=\sum_{k=1}^{m} a_{ik}b_{kj}$ 输出 $n \times p$ 的结果矩阵 $C$。数据范围：$1 \le n,m,p \le 100$，元素绝对值不超过 $10^4$。

## 思路

直接按定义枚举 $i,j,k$ 三重循环，计算 $A$ 的第 $i$ 行与 $B$ 的第 $j$ 列的点积；结果与中间乘积用 `long long` 避免溢出。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
