---
oj: "roj"
problem_id: "3598"
title: "[NOIP2012-提高] Vigenère 密码"
description: "Vigenère 解密即逐位模 26 减法 m = (c − k) mod 26，负数加 26 归正，密钥循环复用，大小写沿用密文。"
difficulty: "普及-"
date: 2026-10-02 09:52
updated: 2026-10-07 12:15
toc: true
tags: ["模拟", "字符串", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0107-09"
    reason: "A 教的「字母平移后字母表回绕」这一步被 B 的解密公式逐位复用，只是把固定 +1 换成密钥位偏移并补上 i % len(key) 密钥循环与大小写跟随密文"
  - oj: "luogu"
    problem_id: "P1914"
    reason: "B 把 A 教的字母数值化后取模 26 平移，直接扩成逐位 (c − k) % 26 的逆运算，并叠加 i % len(key) 密钥循环与大小写保持"
  - oj: "noi_openjudge"
    problem_id: "ch0107-10"
    reason: "B 把 A 教的“字母转下标后减去偏移、%26 再转回字符”直接用作逐位解密，只是把固定偏移 5 换成密钥字母并叠加 i%len(key) 循环。"
common: []
recommend: []
source: https://roj.ac.cn/problem/3598
---

[[TOC]]

## 题目描述

给定密钥串 $k$ 和密文串 $C$（都只含大小写字母），Vigenère 加密是逐位模 26 加法 $c_i \equiv m_i + k_{i \bmod n} \pmod{26}$，运算忽略大小写，密钥不足时循环复用；求明文 $M$。输入两行：第一行密钥（长度不超过 100），第二行密文（长度不超过 1000）；输出一行明文。样例输入 `CompleteVictory` / `Yvqgpxaimmklongnzfwpvxmniytm`，样例输出 `Wherethereisawillthereisaway`。

## 思路

加密是逐位模 26 加法，解密就是逐位模 26 减法 $m_i = (c_i - k_{i \bmod n}) \bmod 26$。把 $c_i$、$k_i$ 都转小写做数值运算，负数加 26 归正，最后按密文自身的大小写还原。密钥下标用 $i \bmod n$ 取即可循环复用，整体 $O(m)$。

## 参考代码

@include-code(./main.cpp, cpp)
