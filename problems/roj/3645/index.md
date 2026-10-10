---
oj: "roj"
problem_id: "3645"
title: "[noip2017-普及] 图书管理员"
description: "编码升序排序后，每个询问从左往右找第一个满足 code % 10^k == b 的编码，首个命中即最小答案。"
difficulty: "普及-"
date: 2026-10-02 12:32
updated: 2026-10-06 15:50
toc: true
tags:
  - 模拟
  - 排序
  - 数学
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3645
---
[[TOC]]

## 题目描述

图书馆中每本书有正整数编码。给出 $n$ 个图书编码和 $q$ 个询问，每个询问形如 $(k, b)$：若某编码的十进制末 $k$ 位恰好等于 $b$，则该书符合这位读者的需求。
对每个询问输出符合要求的最小图书编码，没有则输出 $-1$。
输入：第一行 $n, q$；随后 $n$ 行每行一个图书编码；随后 $q$ 行每行两个正整数 $k, b$。样例输入 `5 5 / 2123 1123 23 24 24 / 2 23 / 3 123 / 3 124 / 2 12 / 2 12`，输出 `23 / 1123 / -1 / -1 / -1`。数据范围：$n, q \leqslant 1000$，编码与需求码均不超过 $10^7$。

## 思路

把图书编码升序排序，再在有序数组里从左往右找第一个满足 `code % 10^k == b` 的编码，首个命中即候选中的最小者。用需求码长度决定模数 $10^k$，顺带处理了前导零。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
