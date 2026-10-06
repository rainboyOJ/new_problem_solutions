---
oj: "roj"
problem_id: "8007"
title: "数字转换错误"
description: "把二进制串逐位翻转、三进制串逐位换成另一个数字，各自枚举候选值，两个集合的交集就是唯一的 N。"
difficulty: "普及-"
date: 2026-10-02 16:22
updated: 2026-10-06 16:42
toc: true
tags: ["进制", "枚举", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/8007
---

[[TOC]]

## 题目描述

毛毛把正整数 $N$（$N \leqslant 10^9$）转成二进制和三进制时各写错了一个数字（不会多写少写）。给定她写下的两个串，求 $N$。

输入第一行是二进制串，第二行是三进制串，输出 $N$ 的十进制值。样例输入 `1010` / `212`，样例输出 `14`，题目保证解唯一。

## 思路

把二进制串逐位翻转、三进制串逐位换成另一个数字，各自枚举出候选值集合；答案必同时落在两个集合里，取交集即唯一解。注意首位也可能写错，前导 0 不影响数值。

## 参考代码

@include-code(./main.cpp, cpp)
