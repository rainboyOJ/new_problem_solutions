---
oj: "roj"
problem_id: "3634"
title: "[noip2016-普及] 买铅笔"
description: "三种包装各自向上取整算出最少份数，乘单价后取最小值，O(1) 枚举即可。"
difficulty: "入门"
date: 2026-10-02 11:56
updated: 2026-10-06 15:31
toc: true
tags: ["枚举"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3634
---

[[TOC]]

## 题目描述

P 老师要买至少 $n$ 支铅笔。商店有 $3$ 种整包包装，第 $i$ 种每包 $a_i$ 支、价格 $p_i$。只能买同一种包装，不能拆包。求最小花费。

**输入格式**：第一行 $n$；接下来三行每行两个正整数 $a_i, p_i$。所有数 $\le 10^4$。

**输出格式**：一个整数，表示最少花费。

**样例输入/输出**：见 `problem.md`。

## 思路

对每种包装，最少份数为 $\lceil n / a_i \rceil$，花费为份数乘单价。三种包装取最小值即可。

## 参考代码

@include-code(./main.cpp, cpp)
