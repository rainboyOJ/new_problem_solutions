---
oj: "roj"
problem_id: "1402"
title: "Vigenère密码"
description: "把 Vigenère 表看成模 26 加法：解密逐位做 (密文序号 − 密钥偏移 + 26) mod 26，密钥按 i mod |k| 循环取位，明文大小写跟随密文，扫描一遍 O(|C|)。"
difficulty: "普及-"
date: 2026-09-30 08:47
updated: 2026-10-06 02:35
toc: true
tags: ["字符串", "模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0107-09"
    reason: "A 教的是字母序号平移并在字母表末尾回绕，B 的减法解密正是把这一步按位复用（mod 26 回绕），再叠加密钥循环取位与大小写跟随密文。"
  - oj: "noi_openjudge"
    problem_id: "ch0107-10"
    reason: "B 的 Vigenère 解法正是把 A 教的「字母转下标后减位移再 % 26 回绕转回字符」这一凯撒移位步骤逐位套用，只把固定位移 5 换成密钥位 k_{i mod n} 并补上密钥循环与大小写跟随"
  - oj: "luogu"
    problem_id: "P1914"
    reason: "B 把 A 教的字母折算 0..25、(x±n)%26 后回写字符这一步逐位套用，只是把固定位移 n 换成循环密钥位 k_{i mod |k|} 的偏移并补上大小写基准"
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
