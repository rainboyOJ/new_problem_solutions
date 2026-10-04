---
oj: "roj"
problem_id: "1164"
title: "digit函数"
description: "第 k 位数字就是 n 整除 10^(k-1) 之后对 10 取余。"
difficulty: "入门"
date: 2026-09-29 21:37
updated: 2026-10-05 04:06
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1164
---

[[TOC]]

## 题目描述

定义函数 `digit(n,k)`，分离出整数 n 从右边数第 k 个数字（个位算第 1 个）。输入一行两个正整数 n 和 k，输出对应的一个数字。例如输入 `31859 3`，输出 `8`。

## 思路

从右往左数第 k 位数字，等价于先整除 $10^{k-1}$ 砍掉低 $k-1$ 位，再对 10 取余取出新的末位，即答案为 `n / 10^(k-1) % 10`。位权 $10^{k-1}$ 用循环连乘算出即可，无需特判边界。

## 参考代码

@include-code(./main.cpp, cpp)
