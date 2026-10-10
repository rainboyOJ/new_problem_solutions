---
oj: "roj"
problem_id: "1176"
title: "谁考了第k名"
description: "把每个学生存成（学号, 成绩）二元组，按成绩降序排序后取第 k 个；注意学号按字符串读入保留前导零，成绩用 %g 输出。"
difficulty: "入门"
date: 2026-09-29 22:15
updated: 2026-10-05 04:26
toc: true
tags: ["排序", "浮点数", "python", "数组"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1176
---

[[TOC]]

## 题目描述

考试中每个学生的成绩互不相同，已知每个学生的学号和成绩，求考第 $k$ 名学生的学号和成绩。
输入：第一行两个整数 $n$（$1 \leqslant n \leqslant 100$）和 $k$（$1 \leqslant k \leqslant n$）；其后 $n$ 行，每行一个学号（整数）和一个成绩（浮点数），用空格分隔。
输出：第 $k$ 名学生的学号和成绩，中间用空格分隔，成绩请用 `%g` 输出。样例（期望输出 `90788004 68.4`）：

```text
5 3
90788001 67.8
90788002 90.3
90788003 61
90788004 68.4
90788005 73.9
```

## 思路

成绩降序排序后的第 $k$ 个学生就是答案：把（学号，成绩）放在一起按成绩从大到小排序后输出第 $k$ 个。两个易错点：学号可能带前导零（如 `092`），要用字符串原样读入输出；成绩必须按数值比较并按 `%g` 输出（`68.4` 不带尾零、`61.0` 输出成 `61`）。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
