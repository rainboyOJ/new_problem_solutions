---
oj: "roj"
problem_id: "3664"
title: "优秀的拆分"
description: "优秀拆分即二进制展开去掉 2^0 位：奇数无解，偶数从高到低输出所有置位对应的 2^k。"
difficulty: "入门"
date: 2026-10-02 14:09
updated: 2026-10-06 16:14
toc: true
tags: ["入门", "数学", "位运算", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3664
---

[[TOC]]

## 题目描述

给定正整数 $n$，判断能否把它拆成若干个**互不相同**的 $2$ 的**正整数**次幂之和。若能，从大到小输出这些数；若不能，输出 `-1`。方案唯一。

输入为一行整数 $n$；输出为拆分数字空格分隔，或 `-1`。$1\le n\le 10^7$。

## 思路

不同 2 的幂之和就是二进制展开，展开唯一。拆分合法当且仅当不需要 $2^0=1$，即 $n$ 为偶数。偶数时从高到低枚举第 $k\ge 1$ 位，若置位则输出 $2^k$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
