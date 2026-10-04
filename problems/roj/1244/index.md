---
oj: "roj"
problem_id: "1244"
title: "和为给定数"
description: "排序后首尾双指针夹逼两数之和：和偏小放弃整行、和偏大放弃整列，首次命中天然就是题面要求的较小数最小的数对。"
difficulty: "入门"
date: 2026-09-30 01:22
updated: 2026-10-05 06:30
toc: true
tags: ["入门", "排序", "双指针", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1244
---

[[TOC]]

## 题目描述

给出 $n$ 个整数，问是否存在两个不同位置的数之和等于 $m$；存在则输出这对数（小的在前、大的在后，空格分隔），多解时取较小数最小的那对，否则输出 `No`。$0<n\le100000$，整数范围 $0\sim10^8$，$0\le m\le 2^{30}$。

输入第一行 $n$，第二行 $n$ 个整数，第三行 $m$。样例输入为三行：`4`、`2 5 1 4`、`6`；对应输出 `1 5`。

## 思路

把数列升序排序，用首尾双指针 $(i,j)$ 夹逼：$a_i+a_j<m$ 时 $a_i$ 与任何数都配不出 $m$，左指针右移；和偏大则右指针左移；相等即命中。左端点按从小到大被访问，所以首次命中的数对就是较小数最小的答案。

## 参考代码

@include-code(./main.cpp, cpp)
