---
oj: "shumeng"
problem_id: "CSP201512A"
title: "数位之和"
description: "反复取十进制末位并除以 10，累加所有数位。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数位"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201512A
---

[[TOC]]

## 形式化题目

给定一个非负整数 $n$（$0 \le n \le 10^9$），求它所有十进制数位之和。

## 思路

十进制数位有两个基本运算：

- `n % 10` 取出最低位；
- `n / 10` 删除最低位。

不断重复这两个操作并累加取出的最低位，直到 `n` 变为 0 即可。注意 $n$ 可能等于 0，此时循环一次都不执行，答案保持初值 0。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：设数位数为 $d$，$d \leqslant 10$，$O(d)$。
- 空间：常量空间，$O(1)$。

## 总结

取模和整除是十进制数位模拟的基本操作。本题是数位类问题的入门题，后续的数位分离、数位统计题都会用到同样的 `%` 与 `/` 组合。