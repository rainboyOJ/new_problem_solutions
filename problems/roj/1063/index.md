---
oj: "roj"
problem_id: "1063"
title: "最大跨度值"
description: "序列的极差：只需两个极值，用 max/min 一次扫描即可，注意最小值不能初始化成 0。"
difficulty: "入门"
date: 2026-09-29 16:57
updated: 2026-10-04 23:57
toc: true
tags: ["入门", "数组", "最值", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1063
---

[[TOC]]

## 题目描述

给定一个长度为 $n$（$1 \leqslant n \leqslant 1000$）的非负整数序列，每个数不超过 1000，求序列的**最大跨度值**（最大跨度值 = 最大值减去最小值）。输入共 2 行：第一行为序列的个数 $n$，第二行为 $n$ 个以空格分隔的非负整数；输出一行，表示序列的最大跨度值。样例输入第一行为 `6`，第二行为 `3 0 8 7 5 9`，对应样例输出为 `9`。

## 思路

答案只由最大值和最小值决定：把两个极值都初始化为第一个元素，逐个读入并同步更新，最后输出差值，一次扫描 $O(n)$，无需排序。注意最小值不能初始化成 0——非负只是取值范围，所有元素都大于 0 时会算错。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
