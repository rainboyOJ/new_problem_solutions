---
oj: "roj"
problem_id: "2012"
title: "usaco-1.3.4 牛式"
description: "枚举由给定数字拼成的三位被乘数与两位乘数，只校验它们算出的三条乘积：两条部分积各三位、最终积四位，且每位数字都属于给定集合，统计成立的牛式个数。"
difficulty: "入门"
date: 2026-10-01 02:54
updated: 2026-10-06 09:25
toc: true
tags: ["枚举", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2012
---

[[TOC]]

## 题目描述

乘法竖式中，把 `*` 换成给定数字集合（数字 ∈ 1..9）里的数字且首位不为 0，使式子成立者称为牛式：三位被乘数 × 两位乘数，两条部分积各三位，最终积四位。输入第一行是数字个数 $N$（$N\le 9$），第二行是 $N$ 个数字；输出一行，表示牛式总数。样例输入 `5` / `2 3 4 6 8`，输出 `1`。

## 思路

枚举由给定数字拼成的三位被乘数 $a$ 与两位乘数 $b$（可重复取数）。只需校验它们算出的三条乘积：$a(b \bmod 10)$ 与 $a\lfloor b/10\rfloor$ 各为三位、$ab$ 为四位，且乘积的每一位数字都属于给定集合。位数与数字集合两项缺一不可。

## 参考代码

@include-code(./main.cpp, cpp)
