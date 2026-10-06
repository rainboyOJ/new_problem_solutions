---
oj: "roj"
problem_id: "3584"
title: "[NOIP2011-普及] 数字反转"
description: "先取绝对值，再逐位取末位拼成反转数；负号最后拼回，原数为 0 时结果为 0。"
difficulty: "普及-"
date: 2026-10-02 09:04
updated: 2026-10-06 14:34
toc: true
tags: ["输入输出", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3584
---

[[TOC]]

## 题目描述

给定一个整数 $N$，把它十进制数位反转得到一个新数。负号不参与反转，结果仍为负数时负号在最前面；除 $N=0$ 外，反转后的最高位不能是 $0$。数据范围 $|N|\le 10^9$。

## 思路

先取绝对值，然后不断取末位拼到结果后面，循环自然吃掉末尾零带来的前导零；最后再根据原数符号给结果加上负号。

## 参考代码

@include-code(./main.cpp, cpp)
