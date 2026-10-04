---
oj: "roj"
problem_id: "1037"
title: "计算2的幂"
description: "2^n 的二进制就是 1 后跟 n 个 0，用左移 1 << n 一次算出：纯整数运算无浮点误差，比参考解的 pow(2,n) 截断更稳妥。"
difficulty: "入门"
date: 2026-09-29 15:24
updated: 2026-10-04 23:06
toc: true
tags: ["入门", "数学", "位运算", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1037
---

[[TOC]]

## 题目描述

给定非负整数 $n$（$0 \leqslant n < 31$），求 $2^n$ 的值。输入一个整数 $n$，输出一个整数，即 $2$ 的 $n$ 次方。

样例输入：`3`；样例输出：`8`。

## 思路

$2^n$ 的二进制表示恰好是 1 后面跟 $n$ 个 0，等价于把整数 1 左移 $n$ 位，因此 `1 << n` 就是答案。整数左移是纯整数运算，无浮点误差，比 `pow(2,n)` 截断更稳妥。

## 参考代码

@include-code(./main.cpp, cpp)