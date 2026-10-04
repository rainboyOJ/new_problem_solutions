---
oj: "roj"
problem_id: "1082"
title: "求小数的某一位"
description: "用长除法逐位模拟：每轮余数乘 10 除以 b 得到当前位小数，循环 n 次即得第 n 位，余数恒小于 b 不会溢出。"
difficulty: "入门"
date: 2026-09-29 17:54
updated: 2026-10-05 00:27
toc: true
tags: ["数学", "数论", "大整数"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1082
---

[[TOC]]

## 题目描述

分数 $a/b$ 化为小数后，求小数点后第 $n$ 位的数字。输入三个正整数 $a、b、n$（$0<a<b<100$，$1 \leqslant n \leqslant 10000$），输出一个数字。样例输入 `1 2 1`，样例输出 `5`。

## 思路

用长除法逐位模拟：余数初值为 $a$，每轮把余数乘 $10$ 除以 $b$ 即得当前位数字，余数取模后继续下一轮，循环 $n$ 次得到第 $n$ 位。余数恒小于 $b<100$，运算不会溢出。

## 参考代码

@include-code(./main.cpp, cpp)
