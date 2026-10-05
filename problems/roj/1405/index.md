---
oj: "roj"
problem_id: "1405"
title: "质数的和与积"
description: "埃氏筛预处理质数表后，从 S/2 向下枚举较小质数 p，第一个满足 p 与 S-p 均为质数的 p 直接给出最大乘积 p*(S-p)。"
difficulty: "入门"
date: 2026-09-30 09:00
updated: 2026-10-05 23:03
toc: true
tags: ["数论", "素数筛", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1405
---

[[TOC]]

## 题目描述

给定一个不大于 $10000$ 的正整数 $S$，求满足 $p+q=S$ 且 $p,q$ 均为质数的分解中，乘积 $p \cdot q$ 的最大值。数据保证有解。

## 思路

用埃氏筛预处理 $2 \sim S$ 的质数表，然后从 $p=\lfloor S/2 \rfloor$ 开始向下枚举。$p$ 与 $S-p$ 都是质数的第一个 $p$ 对应的乘积 $p(S-p)$ 就是最大值，因为两数之和固定时越接近乘积越大。

## 参考代码

@include-code(./main.cpp, cpp)
