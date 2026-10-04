---
oj: "roj"
problem_id: "1068"
title: "与指定数字相同的数的个数"
description: "线性扫描序列，统计等于指定数字的元素个数。"
difficulty: "入门"
date: 2026-07-05 21:47
updated: 2026-10-05 00:05
toc: true
tags: ["入门", "计数", "线性扫描"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1068"
---

[[TOC]]

## 题目描述

给定长度为 $n$（$n \le 100$）的整数序列，统计其中等于 $m$ 的数的个数。输入第 1 行为 $n$ 和 $m$，第 2 行为 $n$ 个整数；输出满足条件的元素个数。

样例：输入 `3 2` 和 `2 3 2`，输出 `2`。

## 思路

依次读入每个数，若等于 $m$ 则计数器加一，最后输出计数器。

## 参考代码

@include-code(./main.cpp, cpp)
