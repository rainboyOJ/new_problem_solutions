---
oj: "roj"
problem_id: "1029"
title: "计算浮点数相除的余"
description: "浮点取余直接按定义落地：math.fmod 给出精确余数 r=a-k·b，再用 .6g 按 6 位有效数字输出，与 C++ cout 参考解逐字一致。"
difficulty: "入门"
date: 2026-09-29 14:06
updated: 2026-10-04 22:52
toc: true
tags: ["入门", "输入输出", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1029
---

[[TOC]]

## 题目描述

给定两个双精度浮点数 $a$、$b$，求余数 $r$，使 $a = k \times b + r$、$k$ 为整数且 $0 \le r < b$。输入一行两个双精度浮点数；输出一行余数。
样例输入：`73.263 0.9973`
样例输出：`0.4601`

## 思路

直接调用 `fmod(a, b)` 得到精确余数（IEEE-754 保证结果落在 $[0, |b|)$），再用 `cout` 以默认 6 位有效数字输出即可。

## 参考代码

@include-code(./main.cpp, cpp)
