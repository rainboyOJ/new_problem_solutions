---
oj: "roj"
problem_id: "2046"
title: "阶乘最后面的非零位"
description: "把 n! 中每个 5 与一个偶数配成 10 消掉，推出 D(n)=D(n/5)·D(n%5)·2^(n/5) mod 10，递归 O(log n) 求阶乘末尾非零位。"
difficulty: "普及-"
date: 2026-10-01 04:53
updated: 2026-10-06 10:32
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2046
---

[[TOC]]

## 题目描述

给定整数 $N$（$1 \le N \le 4220$），求 $N!$ 十进制表示中最后一位非零数字（如 $5!=120$ 答案为 2）。

## 思路

末尾 0 全来自因子 $2\times5$，把每个 5 配一个偶数消掉后，按 5 个数一组递推 $D(n)=D(\lfloor n/5\rfloor)\times D(n\bmod 5)\times 2^{\lfloor n/5\rfloor} \bmod 10$（$n<5$ 出口为 $1,1,2,6,4$），$O(\log N)$ 求解。

## 参考代码

@include-code(./main.cpp, cpp)
