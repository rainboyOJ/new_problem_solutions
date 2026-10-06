---
oj: "roj"
problem_id: "3648"
title: "小凯的疑惑"
description: "互素两币值凑不出的最大价值是数论中的 Frobenius 数：按模 a 分余数类，每类的最小可达值最大为 (a-1)b，直接得公式 ab-a-b。"
difficulty: "普及"
date: 2026-10-02 12:46
updated: 2026-10-06 16:00
toc: true
tags: ["数论", "数学"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3648
---

[[TOC]]

## 题目描述

小凯手中有两种面值互素的金币，面值为正整数 $a, b$（$1 \le a, b \le 10^9$），每种都有无数个。在不找零的情况下，有些价值他无法准确支付，输入数据保证这样的价值存在。输入格式：一行两个正整数 $a, b$，用一个空格隔开；输出格式：一个正整数 $N$，表示不能准确支付的最贵物品的价值。样例：输入 `3 7`，输出 `11`（凑不出的是 $1, 2, 4, 5, 8, 11$，最大为 $11$）。

## 思路

经典 Frobenius 数（Chicken McNugget 定理）：互素两币值凑不出的最大价值为 $ab - a - b$。按模 $a$ 分余数类，每类的可凑出数由其最小可达值 $y_r b$（$y_r$ 为使 $y_r b \equiv r \pmod a$ 的最小非负 $y$）加任意多个 $a$ 构成，$y_r$ 最大取 $a-1$，故该类凑不出的最大数为 $(a-1)b - a$，即答案。正确性两半成立：$ab-a-b$ 本身凑不出（模 $a$ 导出 $y \equiv -1$ 与 $0 \le y \le a-1$ 矛盾），更大的数按余数取合适的 $y$ 即可凑出。

## 参考代码

@include-code(./main.cpp, cpp)
