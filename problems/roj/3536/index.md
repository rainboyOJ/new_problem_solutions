---
oj: "roj"
problem_id: "3536"
title: "[NOIP2005-普及] 陶陶摘苹果"
description: "把板凳并入伸手高度，一次线性扫描统计高度不超过「伸手高度+30」的苹果个数，O(10) 判定题。"
difficulty: "入门"
date: 2026-10-02 06:05
updated: 2026-10-06 13:27
toc: true
tags: ["入门", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3536
---

[[TOC]]

## 题目描述

陶陶家院子的苹果树结出 $10$ 个苹果。已知每个苹果离地高度，以及陶陶伸直手能达到的最大高度。她有一个 $30$ 厘米高的板凳，踩上去再够。求能摘到的苹果数目（碰到即掉）。

输入：第一行 $10$ 个整数（苹果高度），第二行 $1$ 个整数（伸手高度）。输出：能摘到的苹果个数。

样例输入：`100 200 150 140 129 134 167 198 200 111` / `110`，样例输出：`5`。

## 思路

踩板凳后最大够到高度为 `伸手高度 + 30`。遍历 $10$ 个苹果，统计高度不超过该值的个数即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
