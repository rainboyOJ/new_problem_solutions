---
oj: "roj"
problem_id: "3531"
title: "[NOIP2004-普及] 火星人"
description: "排列按字典序对应整数，加 M 就是做 M 次 next_permutation：找枢轴、换最小可增大者、反转降序后缀，单步 O(N)，总复杂度 O(NM)。"
difficulty: "普及"
date: 2026-10-02 05:39
updated: 2026-10-06 13:16
toc: true
tags: [模拟, 排列, next_permutation]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3531
---

[[TOC]]

## 题目描述

$1 \sim N$ 的排列按字典序对应 $1 \sim N!$，给定 $N$、$M$（$M \le 100$）与当前排列，输出对应整数加 $M$ 后的排列（$N \le 10000$）。

## 思路

把排列看作康托展开的序号，加上 $M$ 后逆康托展开还原；因 $M$ 很小，等价于从排列尾部做 $M$ 次"下一个排列"，用栈/逆序对调整即可 $O(N+M \cdot \text{均摊})$。

## 参考代码

@include-code(./main.cpp, cpp)
