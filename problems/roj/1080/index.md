---
oj: "roj"
problem_id: "1080"
title: "余数相同问题"
description: "三个数除以 x 余数相同 ⇔ x 整除任意两数之差，答案即 gcd 的最小大于 1 的因子。"
difficulty: "入门"
date: 2026-09-29 17:43
updated: 2026-10-05 00:28
toc: true
tags: ["数学", "数论", "gcd", "c++"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1080
---

[[TOC]]

## 题目描述

已知三个正整数 a, b, c，求最小的大于 1 的整数 x，使得 a, b, c 分别除以 x 所得余数相同。数据保证有解。

## 思路

同余意味着 x 整除任意两数之差，因此 x 必须整除 gcd(a-b, b-c)。当 a=b=c 时答案为 2；否则答案是该 gcd 的最小大于 1 的因子，直接枚举到 √g 即可。

## 参考代码

@include-code(./main.cpp, cpp)
