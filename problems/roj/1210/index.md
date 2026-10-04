---
oj: "roj"
problem_id: "1210"
title: "因子分解"
description: "试除法分解素因子并按升序输出表达式。"
difficulty: "入门"
date: 2026-09-29 23:36
updated: 2026-10-05 05:38
toc: true
tags: ["入门", "数学", "素数"]
favorite: false
favorite_reason: ""
categories: ["数学"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1210
---

[[TOC]]

## 题目描述

输入整数 $n$（$2 \le n < 100$），输出其素因子分解表达式；素因子从小到大排列，指数为 1 时只写因子，大于 1 时写成 `a^b`。输入是一行整数 $n$，输出是一行表达式，相邻项用 `*` 连接。样例：输入 `60`，输出 `2^2*3*5`。

## 思路

从 $d=2$ 试除到 $\sqrt{n}$，除尽每个 $d$ 并统计指数；若剩余 $n>1$ 则补为指数 1 的素因子，再按规则拼接输出。

## 参考代码

@include-code(./main.cpp, cpp)
