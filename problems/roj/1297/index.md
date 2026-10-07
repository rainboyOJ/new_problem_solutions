---
oj: "roj"
problem_id: "1297"
title: "公共子序列"
description: "LCS 二维前缀 DP，两行滚动数组压缩空间，内层只扫较短串。"
difficulty: "普及"
date: 2026-09-30 03:53
updated: 2026-10-05 08:25
toc: true
tags: ["动态规划", "LCS", "滚动数组", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1297
---

[[TOC]]

## 题目描述

给定两个长度不超过 200 的字符串，求它们的最长公共子序列长度。输入多组数据，读到文件结束；每组输出一行答案。

## 思路

$f(i,j)$ 表示两串前缀 $X[1..i]$、$Y[1..j]$ 的 LCS 长度。字符相等时 $f(i,j)=f(i-1,j-1)+1$；否则取 $f(i-1,j)$ 与 $f(i,j-1)$ 较大者。用两行滚动数组，并把较短串放内层，空间压到 $O(\min(n,m))$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
