---
oj: "roj"
problem_id: "1455"
title: "「一本通 2.1 例 1」Oulipo"
description: "KMP 单趟扫描统计模式串在文本中（可重叠）出现的次数：fail 数组预处理 + 主串扫一遍，均摊 O(|s1|+|s2|)。"
difficulty: "普及-"
date: 2026-07-05 21:47
updated: 2026-10-06 00:13
toc: true
tags: ["字符串", "KMP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1455
---
[[TOC]]

## 题目描述

给出两个只含大写字母的字符串 $s_1, s_2$，求 $s_1$ 在 $s_2$ 中作为子串出现了多少次，允许重叠。例如 $s_1=\texttt{ABA}$，$s_2=\texttt{ABAABA}$，答案为 $2$（两个 `ABA` 共享了字母 `A`）。输入第一行是数据组数 $T$，接下来每组两行依次给出 $s_1$ 和 $s_2$，对每组数据输出一行，即出现次数。$1 \le |s_1| \le 10^4$，$1 \le |s_2| \le 10^6$。

## 思路

经典 KMP 计数：先对 $s_1$ 预处理 fail 数组（$\mathrm{fail}[i]$ 为 $s_1[:i]$ 的最长相等真前后缀长度），再单趟扫 $s_2$，失配时沿 fail 链回退、不回退主串指针，均摊 $O(|s_1|+|s_2|)$。扫到匹配长度等于 $|s_1|$ 时计数加一，并回退到 $\mathrm{fail}[|s_1|-1]$ 而不是清零，这样重叠的出现也会被数到。

## 参考代码

@include-code(./main.cpp, cpp)
