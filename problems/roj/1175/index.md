---
oj: "roj"
problem_id: "1175"
title: "除以13"
description: "用字符串模拟竖式除法，逐位求出大整数除以 13 的商和余数。"
difficulty: "入门"
date: 2026-09-29 22:02
updated: 2026-10-05 04:18
toc: true
tags:
  - 高精度
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1175
---

[[TOC]]

## 题目描述

输入一个长度不超过 100 位的正整数 $N$，输出 $N \div 13$ 的商和余数，各占一行。样例输入 `2132104848488485`，样例输出第一行 `164008065268345`、第二行 `0`。

## 思路

$N$ 最多 100 位，超出 64 位整数范围，用字符串按位模拟竖式除法。从高位到低位维护余数 $r = (10r + d) \bmod 13$，当前位的商为 $(10r + d) / 13$，最后跳过商的前导零。

## 参考代码

@include-code(./main.cpp, cpp)
