---
oj: "roj"
problem_id: "1413"
title: "确定进制"
description: "从小到大枚举进制 B（2~40），检查三个数的每一位数字是否合法并用 Horner 展开求值，第一个满足 p×q=r 的 B 即答案。"
difficulty: "入门"
date: 2026-09-30 09:24
updated: 2026-10-05 23:14
toc: true
tags:
  - 枚举
  - 进制
favorite: false
favorite_reason: ""
categories:
  - 枚举
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1413
---

[[TOC]]

## 题目描述

给定三个数字串 $p,q,r$（每位都是数字，$1\le p,q,r\le 10^6$），求最小的进制 $B$（$2\le B\le 40$），使得把它们按 $B$ 进制解释后满足 $p\times q=r$；不存在则输出 $0$。

## 思路

从小到大枚举 $B$，检查每位数字是否小于 $B$，再用 Horner 展开把三串转成十进制，若 $p\times q=r$ 则 $B$ 为答案。枚举范围仅 39 个，直接暴力即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
