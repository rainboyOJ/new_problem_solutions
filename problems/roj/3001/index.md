---
oj: "roj"
problem_id: "3001"
title: "64位整数乘法"
description: "把乘数 b 按二进制拆成若干 2 的幂之和，用逐位翻倍的加法代替乘法，每次取模使中间量不超过 2p，用 O(log b) 次加法求出 a*b mod p。"
difficulty: "普及-"
date: 2026-10-01 09:43
updated: 2026-10-07 13:50
toc: true
tags: ["数学", "位运算", "快速幂", "倍增", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1326"
    reason: "B 完整复用了 A 的二进制拆分与逐位倍增骨架：A 用底数平方升级+位为 1 才累乘求幂，B 把同一循环里的平方换成加数自加翻倍、累乘换成累加，从而在避免中间乘积溢出的同时保持 O(log b)。"
  - oj: "roj"
    problem_id: "1616"
    reason: "B 整体套用 A 教的『二进制拆分+相邻项只差一次递推+只在位为 1 时累乘』骨架，把底数平方换成加数自加、累乘换成累加，据此在 64 位溢出场景下仍保持 O(log b)，B 另叠加中间量不超过 2p 的取模论证。"
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
