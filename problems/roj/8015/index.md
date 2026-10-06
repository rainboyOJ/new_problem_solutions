---
oj: "roj"
problem_id: "8015"
title: "纪念品"
description: "把最小删除转化为最长保留：类 LIS 的 O(n²) 线性 DP，f[i] = 1 + max{f[j] : |a[i]-a[j]|≠1}，答案 N - max f。"
difficulty: "普及-"
date: 2026-10-02 17:00
updated: 2026-10-06 16:51
toc: true
tags: ["线性dp", "LIS", "子序列"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/8015
---

[[TOC]]

## 题目描述

小 K 买回 $N$ 个纪念品，按购买顺序排成一排，每个纪念品有一个价格。她可以去掉一些，使剩下的纪念品中任意相邻两个的价格差的绝对值不等于 1（价格相同可以相邻），求最少去掉多少个。输入第一行一个整数 $N$，接下来 $N$ 行每行一个价格；输出最少去掉的个数。数据范围 $3 \le N \le 33$。样例输入为 `6` 及价格 `4 2 2 1 1 1`，输出 `2`。

## 思路

删得最少等价于留得最多，于是求最长的合法子序列。合法性只依赖相邻两个保留元素，仿照 LIS 设 $f[i]$ 表示一定保留第 $i$ 个纪念品时最多能保留多少个，转移为 $f[i] = 1 + \max\{f[j] : j < i,\ |a_i - a_j| \neq 1\}$，答案为 $N - \max f[i]$，复杂度 $O(N^2)$。注意差为 0 是允许的，判断条件是「不等于 1」。

## 参考代码

@include-code(./main.cpp, cpp)
