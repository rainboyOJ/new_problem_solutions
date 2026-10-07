---
oj: "roj"
problem_id: "1083"
title: "计算星期几"
description: "星期以 7 天为周期，用快速幂求 a^b mod 7 后查星期表即可。"
difficulty: "入门"
date: 2026-09-29 17:55
updated: 2026-10-05 00:33
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1083
---

[[TOC]]

## 题目描述

假设今天是星期日，那么过 $a^b$ 天之后是星期几？输入两个正整数 $a$、$b$（$0 < a \leqslant 100$，$0 < b \leqslant 10000$），输出一个英文星期名（Monday、Tuesday、Wednesday、Thursday、Friday、Saturday、Sunday）。样例输入 `3 2000`，样例输出 `Tuesday`。

## 思路

星期以 $7$ 天为周期，答案只由 $r = a^b \bmod 7$ 决定，用快速幂（边乘边取模）求出 $r$，避免直接计算巨大的 $a^b$。今天是星期日，把星期表按 Monday 开头存放，输出 `week[r-1]`：$r=0$（过了整数个星期）时下标 $-1$ 恰好取到末尾的 Sunday，无需特判。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
