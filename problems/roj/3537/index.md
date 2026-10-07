---
oj: "roj"
problem_id: "3537"
title: "校门外的树"
description: "开长度 $L+1$ 的布尔桶给每个整数点打删除标记，重叠区间重复置 1 幂等，最后数 0 的个数即剩余树数。"
difficulty: "入门"
date: 2026-10-02 06:04
updated: 2026-10-06 13:26
toc: true
tags: ["入门", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3537
---

[[TOC]]

## 题目描述

马路长 $L$（$1\le L\le 10000$），数轴上整数点 $0,1,\dots,L$ 各种一棵树。给出 $M$（$1\le M\le 100$）个区域，每个用两个整数端点表示，端点顺序不保证、区间之间可能重合；移走每个区域内（含两端端点）的树，问还剩多少棵。

**输入格式：** 第一行 $L$ 和 $M$，接下来 $M$ 行每行一个区域的两个整数端点；**输出格式：** 一个整数，表示剩余的树数。
**样例输入：**
```text
500 3
150 300
100 200
470 471
```
**样例输出：** `298`。

## 思路

对每个整数点建一个删除标记，被区间覆盖就置 1；标记是幂等的，重叠区间重复置 1 不会多删，最后统计仍为 0 的点数即剩余树数。

## 参考代码

@include-code(./main.cpp, cpp)
