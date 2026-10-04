---
oj: "roj"
problem_id: "1148"
title: "连续出现的字符"
description: "线性扫描维护连续计数 run，每个位置先判 run 是否已达 k 再向右更新，逐点复刻标准程序的先判后更语义。"
difficulty: "入门"
date: 2026-09-29 20:49
updated: 2026-10-05 03:37
toc: true
tags: ["字符串", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1148
---

[[TOC]]

## 题目描述

给定正整数 $k$（$1 \leqslant k \leqslant 1000$）和字符串 $s$（$1 \leqslant |s| \leqslant 2500$，不含空白符），输出 $s$ 中第一个连续出现至少 $k$ 次的字符；若不存在，输出 `No`。

输入：第一行为正整数 $k$，第二行为字符串 $s$。输出：一个字符或 `No`。

样例输入 $k=3$、$s=$ `abcccaaab` 时，字符 `c` 连续出现 3 次，输出 `c`。

## 思路

维护当前段计数 `run`，逐位置扫描：每个位置**先判** `run == k`（成立则输出当前字符），**再**按 $s[i]$ 与 $s[i+1]$ 是否相同决定 `run+1` 或归 1。这样末端段恰好在串尾凑满 $k$ 时不会再触发检查（其后无位置），$k=1$ 时输出的是第一个与前一个相同的字符，均与标准程序行为一致。时间复杂度 $O(|s|)$。

## 参考代码

@include-code(./main.cpp, cpp)
