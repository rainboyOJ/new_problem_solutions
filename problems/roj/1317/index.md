---
oj: "roj"
problem_id: "1317"
title: "【例5.2】组合的输出"
description: "组合看成严格递增序列，递归逐位选数：递增性天然保证不重不漏，层内从小到大枚举即得字典序。"
difficulty: "入门"
date: 2026-09-30 04:53
updated: 2026-10-05 09:17
toc: true
tags: ["递归", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1317
---

[[TOC]]

## 题目描述

从 $n$ 个元素（即自然数 $1,2,\dots,n$）中取出 $r$ 个数（$1 \leqslant r \leqslant n$，不分顺序），用**递归**的方法输出所有组合。每个组合占一行，元素按从小到大排列；所有组合按字典序输出。

输入：一行两个自然数 $n$、$r$。

输出：所有组合，每个数占三个字符的位置（固定两个空格 + 十进制）。

样例输入 `5 3` 对应的输出从 `  1  2  3` 开始，共 $\binom{5}{3}=10$ 行，最后一行为 `  3  4  5`。

## 思路

组合就是严格递增序列：递归逐位选数，第 $k$ 位必须大于第 $k-1$ 位，递增性天然保证不重不漏（不需要 vis 数组）。层内从小到大枚举，前序输出顺序恰好就是字典序；再剪枝——还要取 $h$ 个数时，本位最大到 $n-h+1$。输出格式注意「占三个字符」实为固定两个空格加十进制，用 `%3d` 右对齐会在两位数处出错。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
