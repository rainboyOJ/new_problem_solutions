---
oj: "roj"
problem_id: "1403"
title: "素数对"
description: "通过埃氏筛预处理素数表，并枚举奇数快速筛选输出不超过 n 的所有孪生素数对。"
difficulty: "入门"
date: 2026-09-30 08:46
updated: 2026-10-05 23:02
toc: true
tags:
  - "数学"
  - "素数筛法"
favorite: false
favorite_reason: ""
categories:
  - "基础算法"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1403
---

[[TOC]]

## 题目描述

两个相差为 2 的素数称为素数对，如 5 和 7、17 和 19。给定正整数 $n$（$1 \leqslant n \leqslant 10000$），要求找出所有两个数均不大于 $n$ 的素数对，每对输出一行，中间用单个空格隔开。若没有找到任何素数对，输出 `empty`。

## 思路

先用埃氏筛预处理出 $[0, n]$ 内的素数标记表；再枚举奇数 $p$，若 $p$ 与 $p + 2$ 均为素数则输出这一对。因为除 2 外素数都是奇数，而 $(2, 4)$ 不合法，所以从 $p = 3$ 开始按步长 2 枚举即可；一对手都没有时输出 `empty`。

## 参考代码

@include-code(./main.cpp, cpp)
