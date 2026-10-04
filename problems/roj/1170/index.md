---
oj: "roj"
problem_id: "1170"
title: "计算2的N次方"
description: "N≤100，2^N 最多 31 位十进制数，超出 64 位整数，必须用十进制位数组做高精度乘 2。"
difficulty: "入门"
date: 2026-09-29 21:52
updated: 2026-10-05 04:11
toc: true
tags: ["入门", "数学", "高精度"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1170
---

[[TOC]]

## 题目描述

给定正整数 $N\ (N \leqslant 100)$，计算 $2^N$ 的精确值。

输入一个正整数 $N$；输出 $2^N$ 的精确十进制表示。

```
输入样例：
5
输出样例：
32
```

## 思路

N ≤ 100 时 2^N 最多 31 位十进制数字，超出 64 位整数范围，所以必须用十进制位数组做高精度：外层循环 N 轮，每轮把整组位乘 2 并从低位向高位处理进位；N 较小时最高位也可能再产生新进位，要把 carry 写到 0 为止。

## 参考代码

@include-code(./main.cpp, cpp)
