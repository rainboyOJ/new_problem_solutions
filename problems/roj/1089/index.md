---
oj: "roj"
problem_id: "1089"
title: "数字反转"
description: "把整数 N 拆成符号与数位串，r = r * 10 + n % 10 循环反转数位，符号最后乘回，O(d) 完成。"
difficulty: "入门"
date: 2026-09-29 18:17
updated: 2026-10-05 00:41
toc: true
tags: ["入门", "字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1089
---

[[TOC]]

## 题目描述

给定一个整数 N（-1,000,000,000 ≤ N ≤ 1,000,000,000），把它各个位上的数字反转得到一个新数，符号不变，最高位的零要去掉。输入一行整数 N，输出一行反转后的整数。

样例：输入 `123` 输出 `321`；输入 `-380` 输出 `-83`。

## 思路

把符号单独摘出来，只对 |N| 的数位做反转：循环 `r = r * 10 + n % 10; n /= 10;`，末位的 0 自然不会进入结果，正好满足"去前导零"的要求；最后把符号乘回去，N 为 0 时循环不执行、结果就是 0。

## 参考代码

@include-code(./main.cpp, cpp)
