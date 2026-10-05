---
oj: "roj"
problem_id: "1671"
title: "宇宙速度"
description: "把五档宇宙速度门槛收进数组，数出速度 v 达标的档数 k，再输出数字前缀串 12...k，k 为 0 时输出 0。"
difficulty: "入门"
date: 2026-10-01 01:29
updated: 2026-10-06 01:45
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1671
---

[[TOC]]

## 题目描述

给定五个宇宙速度门槛 $7960,11200,16700,115000,2000000$（米/秒），判断速度 $v$ 达到第几级。
输入整数 $v$（$1 \le v \le 123456789012346$），输出原速度 $v$ 和标记串。
样例：`1000` 输出 `1000 0`；`115000` 输出 `115000 1234`。

## 思路

用循环统计 $v$ 达标门槛个数 $k$；$k=0$ 时输出 `0`，否则输出 `1` 到 `k` 连成的字符串。

## 参考代码

@include-code(./main.cpp, cpp)
