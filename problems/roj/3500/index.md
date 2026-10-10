---
oj: "roj"
problem_id: "3500"
title: "[noip2000]进制转换"
description: "把 N 反复 divmod 负基数，余数为负时借一位（商 +1、余数 +R）规范化到 [0,R)，低位到高位收集后反转即为答案。"
difficulty: "普及-"
date: 2026-10-02 03:23
updated: 2026-10-06 12:08
toc: true
tags:
  - "进制转换"
  - "数学"
  - "模拟"
favorite: false
favorite_reason: ""
categories:
  - "基础算法"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3500
---

[[TOC]]

## 题目描述

给定十进制数 $N$（$|N| \le 32767$）和负进制基数 $-R$（$2 \le R \le 20$），把 $N$ 转换为该负进制下的表示。数码超过 $9$ 时用 `A`..`J` 表示 $10$..$19$。

输入每行两个整数 $N$ 和 $-R$；输出格式为 `N=数码串(base-R)`。

样例：
```
30000 -2
-20000 -2
28800 -16
-25000 -16
```

对应输出 `30000=11011010101110000(base-2)` 等。

## 思路

从低位向高位逐次做除法取余。C++ 的 `%` 向零截断，余数可能为负；若余数 $r<0$，则给商加 $1$、余数加上 $R$（即 `r -= base`，因为 base 为负），把数码规范化到 $[0,R)$。低位收集完后反转即可。$N=0$ 时直接输出 `0`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
