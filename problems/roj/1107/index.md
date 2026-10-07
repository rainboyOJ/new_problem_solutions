---
oj: "roj"
problem_id: "1107"
title: "校门外的树"
description: "用布尔数组标记每个位置上的树是否被移走，最后统计剩余棵数。"
difficulty: "入门"
date: 2026-09-29 19:04
updated: 2026-10-05 01:40
toc: true
tags: ["区间合并", "贪心", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1107"
---

[[TOC]]

## 题目描述

数轴 $[0, L]$ 上每个整数点 $0,1,\dots,L$ 都种有一棵树。现要移走 $M$ 个区域内的所有树（含区域端点），区域之间可能重合，求移走后剩余树的数目。
输入：第一行两个整数 $L, M$（$1 \le L \le 10000$，$1 \le M \le 100$）；接下来 $M$ 行每行两个整数，为区域起始点和终止点坐标。输出：一行一个整数，表示剩余树的数目。
样例：输入第一行为 `500 3`，接下来三行为 `150 300`、`100 200`、`470 471`；输出为 `298`。

## 思路

用布尔数组 `removed` 标记被移走的位置：每个区域先规范化成左小右大，再把区间内含端点的所有点置为已移走。最后统计 $[0, L]$ 中未被标记的点的个数，即为答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
