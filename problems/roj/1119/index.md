---
oj: "roj"
problem_id: "1119"
title: "矩阵交换行"
description: "读入固定 5×5 矩阵，直接交换指定两行后输出。"
difficulty: "入门"
date: 2026-09-29 19:38
updated: 2026-10-05 02:31
toc: true
tags:
  - 模拟
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1119
---

[[TOC]]

## 题目描述

给定一个 $5 \times 5$ 的整数矩阵，将第 $m$ 行与第 $n$ 行整体交换后输出。

输入共 6 行：前 5 行为矩阵的每一行，元素之间以一个空格分开；第 6 行为两个整数 $m, n$（$1 \leqslant m, n \leqslant 5$）。输出交换后的矩阵，每行元素占一行，元素之间以一个空格分开。

样例输入为五行矩阵 `1 2 2 1 2`、`5 6 7 8 3`、`9 3 0 5 3`、`7 2 1 4 6`、`3 0 8 2 4` 及 `1 5`；样例输出为 `3 0 8 2 4`、`5 6 7 8 3`、`9 3 0 5 3`、`7 2 1 4 6`、`1 2 2 1 2`。

## 思路

矩阵固定为 $5 \times 5$，直接模拟：读入后把第 $m$ 行与第 $n$ 行的对应元素逐个交换，再按行输出即可；$m = n$ 时交换等于不变，无需特判。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
