---
oj: "roj"
problem_id: "1326"
title: "【例7.5】取余运算（mod）"
description: "用快速幂求 b^p mod k：把 p 拆成二进制，位为 1 时乘入答案，每轮底数平方取模。"
difficulty: "入门"
date: 2026-09-30 05:19
updated: 2026-10-05 09:49
toc: true
tags: ["数学", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1326
---

[[TOC]]

## 题目描述

输入三个长整型数 b、p、k，求 b^p mod k 的值，输出格式为 `b^p mod k=结果`。

## 思路

将 p 按二进制拆分，从低位到高位逐位处理：当前位为 1 时把底数乘进答案，每轮底数平方并对 k 取模；全程取模保证中间值不超过 k^2。

## 参考代码

@include-code(./main.cpp, cpp)
