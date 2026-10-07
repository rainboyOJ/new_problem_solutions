---
oj: "roj"
problem_id: "1121"
title: "计算矩阵边缘元素之和"
description: "边缘元素之和等价于「全部元素之和 − 内部子矩阵之和」，直接读入累加即可。"
difficulty: "入门"
date: 2026-09-29 19:50
updated: 2026-10-05 02:32
toc: true
tags: ["入门", "数组", "矩阵"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1121
---

[[TOC]]

## 题目描述

给定 $m\times n$ 的整数矩阵（$m,n<100$），求第一行、最后一行、第一列、最后一列并集的元素之和，四个角只计一次。第一行输入 $m,n$，随后输入 $m$ 行每行 $n$ 个整数，输出边缘元素和。样例输入 `3 3 / 3 4 1 / 3 7 1 / 2 0 1`，样例输出 `15`。

## 思路

读入时累加全部元素得到 $S_{\text{全部}}$，再单独把内部子矩阵（第 $2\ldots m{-}1$ 行、第 $2\ldots n{-}1$ 列）累加得 $S_{\text{内部}}$，答案为 $S_{\text{全部}}-S_{\text{内部}}$；$m\le 2$ 或 $n\le 2$ 时内部区域为空，自动退化为整矩阵求和。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
