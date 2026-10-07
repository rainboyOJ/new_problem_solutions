---
oj: "roj"
problem_id: "1145"
title: "字符串p型编码"
description: "把数字串切成极大同字符段，每段输出长度加字符，线性扫描即可完成。"
difficulty: "入门"
date: 2026-09-29 21:04
updated: 2026-10-05 03:27
toc: true
tags: ["入门", "字符串", "游程编码", "groupby", "python"]
favorite: false
favorite_reason: ""
categories:
  - 字符串
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1145
---

[[TOC]]

## 题目描述

给定一个只含数字字符的字符串 $s$（长度不超过 $1000$），把它切成每个极大同字符段。对每一段依次输出「段长 + 段字符」即可得到 $s$ 的 p 型编码串。例如 `122344111` 的切分为 `1, 22, 3, 44, 111`，编码结果为 `1122132431`。

## 思路

维护当前段起点，从左向右扫描字符串，当遇到下一个字符不同或到达串尾时结算当前段，输出段长与段字符即可。段长需要用十进制完整输出（如 `00000000000` 输出 `110`）。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
