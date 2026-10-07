---
oj: "roj"
problem_id: "1402"
title: "Vigenère密码"
description: "把 Vigenère 表看成模 26 加法：解密逐位做 (密文序号 − 密钥偏移 + 26) mod 26，密钥按 i mod |k| 循环取位，明文大小写跟随密文，扫描一遍 O(|C|)。"
difficulty: "普及-"
date: 2026-09-30 08:47
updated: 2026-10-05 12:53
toc: true
tags: ["字符串", "模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1402
---

[[TOC]]

## 题目描述

Vigenère 密码用密钥串 $k$ 加密明文：密文第 $i$ 位 $c_i = m_i \circledast k_{i \bmod n}$，$\circledast$ 就是题面那张 $26 \times 26$ 的表（密钥位当行、明文字母当列），运算忽略大小写但保留明文字母的大小写；明文比密钥长时密钥循环使用。给定密钥和密文，求明文。

输入两行：第一行密钥 $k$（$n \leqslant 100$），第二行密文 $C$（$m \leqslant 1000$），都只含英文字母；输出一行明文。样例输入 `CompleteVictory`、`Yvqgpxaimmklongnzfwpvxmniytm`，样例输出 `Wherethereisawillthereisaway`。

## 思路

- 加密是 $c_i = (m_i + k_{i \bmod n}) \bmod 26$，那张表只是把模 26 加法画了出来；解密移项得 $m_i = (c_i - k_{i \bmod n}) \bmod 26$，每位 $O(1)$，不必建表。
- 密钥第 $i$ 位取 $k_{i \bmod n}$，明文大小写跟随密文：算出序号后加回密文同款的 `'a'` 或 `'A'`。
- 易错点：相减可能为负（如 $6-15=-9$），模 26 应回绕成 $17$；C++ 的 `%` 保留负号，需手动再 `+26`。

## 参考代码

@include-code(./main.cpp, cpp)
