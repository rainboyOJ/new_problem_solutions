---
oj: "roj"
problem_id: "1307"
title: "【例1.3】高精度乘法"
description: "两个 100 位十进制数相乘远超 64 位整型，需用高精度乘法：把每位拆出来做竖式双重循环累乘，再从低位到高位进位即可。"
difficulty: "入门"
date: 2026-09-30 04:18
updated: 2026-10-05 08:49
toc: true
tags: ["高精度", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1307
---

[[TOC]]

## 题目描述

输入两个高精度正整数 $M$、$N$（均小于 100 位），输出 $M \times N$。两行各一整数。样例：输入 `36` `3`，输出 `108`。

## 思路

把 $M$、$N$ 逆序拆到 `int` 数组（下标 1 是最低位），双重循环把每位乘积累加到 `c[i+j-1]`，再从低位到高位统一进位，最后倒序输出。整体 $O(pq)$，$p$、$q$ 都百位以内，轻松通过。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
