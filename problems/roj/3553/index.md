---
oj: "roj"
problem_id: "3553"
title: "[NOIP2007-普及] 纪念品分组"
description: "排序后双指针贪心：每轮让最贵的纪念品与最便宜的凑组，凑不上就单独成组，交换论证保证组数最少，O(n log n)。"
difficulty: "普及"
date: 2026-10-02 07:08
updated: 2026-10-06 13:42
toc: true
tags: ["贪心", "双指针", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3553
---

[[TOC]]

## 题目描述

给定每组价格之和的上界 $w$ 与 $n$ 件纪念品的价格 $P_i$（$5 \le P_i \le w$），要把纪念品分组，每组最多 2 件且价格之和不超过 $w$，求最少分组数。

输入：第 1 行 $w$，第 2 行 $n$，接下来 $n$ 行每行一个 $P_i$。输出：最少分组数。

样例：$w=100, n=9$，价格 $90,20,20,30,50,60,70,80,90$，输出 $6$。数据范围 $1 \le n \le 30000$。

## 思路

排序后，设最便宜的未处理件为 $P_{\min}$，最贵的为 $P_{\max}$。若 $P_{\min}+P_{\max}>w$，则 $P_{\max}$ 只能单独成组；否则把两者配成一组不会使最优解变差（交换论证）。于是用双指针从两端向中间扫描，能凑就凑，凑不上就让贵的单独成组。

## 参考代码

@include-code(./main.cpp, cpp)
