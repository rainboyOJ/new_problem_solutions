---
oj: "roj"
problem_id: "1155"
title: "回文三位数"
description: "把三位回文数按 aba = 101a + 10b 直接生成 90 个候选，再对每个候选试除判素数；回文性由生成方式保证，无需运行期判回文。"
difficulty: "入门"
date: 2026-09-29 21:14
updated: 2026-10-05 03:45
toc: true
tags: ["入门", "枚举", "数论", "素数", "回文数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1155
---

[[TOC]]

## 题目描述

如果一个数从左边读和从右边读都是同一个数，就称为回文数，例如 6886 就是回文数。求所有的既是回文数又是素数的三位数。

**输入**：无。**输出**：每行一个满足条件的数，按从小到大顺序，共 15 个。

## 思路

三位回文数形如 $\overline{aba} = 101a + 10b$，直接枚举 $a \in [1,9]$、$b \in [0,9]$ 生成全部 90 个候选，回文性由生成方式本身保证，不必再判回文。对每个候选试除到 $\sqrt{x}$ 判断是否为素数，是素数就输出。

## 参考代码

@include-code(./main.cpp, cpp)
