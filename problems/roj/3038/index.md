---
oj: "roj"
problem_id: "3038"
title: "兔子与兔子"
description: "预处理前缀哈希 h[i]=h[i-1]*B+s[i]，每次询问用 h[r]-h[l-1]*B^(r-l+1) 在 O(1) 内取出子串指纹，比较两区间指纹判断子串是否相同。"
difficulty: "普及"
date: 2026-10-01 11:39
updated: 2026-10-06 11:33
toc: true
tags: ["字符串hash", "哈希"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3038
---

[[TOC]]

## 题目描述

给定一个长度为 $n$ 的小写字母串 $S$ 和 $m$ 次询问。每次询问给出四个整数 $l_1, r_1, l_2, r_2$（位置从 $1$ 开始），判断子串 $S[l_1..r_1]$ 与 $S[l_2..r_2]$ 是否完全相同，相同输出 `Yes`，否则输出 `No`。

## 思路

字符串哈希模板题：预处理前缀哈希 $h[i] = h[i-1] \times B + s_i$（$B=131$，模梅森素数 $2^{61}-1$）和 $B$ 的幂 $p[i]$，子串 $S[l..r]$ 的指纹为 $h[r] - h[l-1] \times p[r-l+1]$，每次询问 $O(1)$ 取出两个子串的指纹直接比较即可。注意 C++ 中减法可能得到负数，要手工加 $MOD$ 调整。

## 参考代码

@include-code(./main.cpp, cpp)
