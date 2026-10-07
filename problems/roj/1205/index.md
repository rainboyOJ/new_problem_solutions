---
oj: "roj"
problem_id: "1205"
title: "汉诺塔问题"
description: "递归分治：把 n-1 个盘移到辅助柱，移最大盘，再把 n-1 个盘移到目的柱。"
difficulty: "入门"
date: 2026-09-29 23:27
updated: 2026-10-05 05:32
toc: true
tags:
  - 递归
  - 分治
  - 汉诺塔
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1205
---

[[TOC]]

## 题目描述

经典汉诺塔：三根杆上，最左边的杆自上而下、由小到大串着 $n$ 个圆盘（编号 $1\sim n$），要把所有盘移到目标杆；一次只能移一个盘，且大盘不能压小盘。输入为一个整数 $n$（小于 20）和三个单字符，依次表示盘子数目、源杆、目标杆、辅助杆；每次移动输出一行 `a->3->b`，表示把编号为 3 的盘从 a 杆移至 b 杆。样例输入 `2 a b c`，样例输出：

```text
a->1->c
a->2->b
c->1->b
```

## 思路

递归分治：先把上面 $n-1$ 个盘借助目标杆移到辅助杆，再把最大的 $n$ 号盘直接移到目标杆，最后把 $n-1$ 个盘借助源杆从辅助杆移到目标杆；$n=0$ 时递归结束。注意题面中三个杆子的输入顺序是「源杆、目标杆、辅助杆」，不要按习惯当成「源、辅助、目标」。总步数为 $2^n-1$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
