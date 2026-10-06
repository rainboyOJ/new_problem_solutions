---
oj: "roj"
problem_id: "3001"
title: "64位整数乘法"
description: "把乘数 b 按二进制拆成若干 2 的幂之和，用逐位翻倍的加法代替乘法，每次取模使中间量不超过 2p，用 O(log b) 次加法求出 a*b mod p。"
difficulty: "普及-"
date: 2026-10-01 09:43
updated: 2026-10-06 10:53
toc: true
tags: ["数学", "位运算", "快速幂", "倍增", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3001
---

[[TOC]]

## 题目描述

求 $a$ 乘 $b$ 对 $p$ 取模的值。输入共三行，每行一个整数，依次为 $a$、$b$、$p$；输出一个整数，表示 $a \times b \bmod p$ 的值。

数据范围：$1 \le a, b, p \le 10^{18}$。输入样例为 `3`、`4`、`5`（各占一行），输出样例为 `2`。

## 思路

$a \times b$ 最大约 $10^{36}$ 会溢出 `long long`，所以把乘数 $b$ 按二进制拆成若干 $2$ 的幂之和：$b$ 的最低位为 1 时把当前加数 $a \cdot 2^k \bmod p$ 累进答案，然后加数自加翻倍、$b$ 右移一位。答案与加数始终保持在 $[0, p)$，每次加法后取模的中间量不超过 $2p$，不会溢出，总时间 $O(\log b)$。

## 参考代码

@include-code(./main.cpp, cpp)
