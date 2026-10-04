---
oj: "roj"
problem_id: "1137"
title: "加密的病历单"
description: "按加密逆序撤销三步变换：大小写反转、逆序、字母表循环右移 3，线性还原原文。"
difficulty: "入门"
date: 2026-09-29 20:26
updated: 2026-10-05 03:07
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1137
---

[[TOC]]

## 题目描述

给定一个长度小于 $50$、只含大小写字母的密文字符串。原文经过三步加密得到它：

1. 每个字母在字母表中循环左移 3 位；
2. 字符串整体逆序；
3. 大小写反转。

输出解密后的原文。

样例：输入 `GSOOWFASOq`，输出 `Trvdizrrvj`。

## 思路

加密顺序是“左移 3 → 逆序 → 大小写反转”，解密按相反顺序撤销。大小写反转和逆序都是自逆变换；左移 3 的逆是循环右移 3。对字符串先大小写反转，再逆序，最后每个字母右移 3 位即可。

## 参考代码

@include-code(./main.cpp, cpp)
