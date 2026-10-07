---
oj: "roj"
problem_id: "1075"
title: "药房管理"
description: "维护剩余库存线性模拟取药过程，统计库存不足被拒绝的病人数。"
difficulty: "入门"
date: 2026-09-29 17:30
updated: 2026-10-05 00:21
toc: true
tags: ["模拟", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1075
---

[[TOC]]

## 题目描述

药房已知某种药品每天开始时的库存总量 $m$，一天内不进货。当天有 $n$（$0 < n \leqslant 100$）个病人按时间先后顺序前来取药：若第 $i$ 个病人想取的 $a_i$ 不超过当时剩余库存则取药成功，否则请求被拒绝。输入共 3 行：$m$、$n$、以及 $n$ 个取药数量 $a_1, \dots, a_n$；输出一行，为没有取上药品的人数。样例输入 `30`、`6`、`10 5 20 6 7 8`，输出 `2`。

## 思路

按时间顺序线性模拟：用一个变量维护当前剩余库存，逐个读入需求，库存够就扣减、不够就把答案加一，边读边处理即可。时间复杂度 $O(n)$。样例中需求 $20,7,8$ 到来时库存不足，故答案为 $2$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
