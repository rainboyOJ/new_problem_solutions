---
oj: "roj"
problem_id: "1186"
title: "出现次数超过一半的数"
description: "一遍哈希计数取众数，用整数不等式 2*times > n 判定严格过半，避开浮点与整除两类半判定错误。"
difficulty: "入门"
date: 2026-09-29 22:37
updated: 2026-10-05 04:41
toc: true
tags: ["入门", "计数", "哈希表", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1186
---

[[TOC]]

## 题目描述

给定 $n$（$0 < n \leqslant 1000$）个整数 $a_1, \dots, a_n$（$-50 < a_i < 50$），若存在某个值出现次数严格超过一半则输出这个数，否则输出 `no`。

第一行 $n$，第二行 $n$ 个整数。样例：`3 / 1 2 2` → `2`。

## 思路

一遍哈希计数得到每个值的出现次数，取最大值；若 `2 * times > n`（严格过半）则输出该值，否则 `no`。

## 参考代码

@include-code(./main.cpp, cpp)