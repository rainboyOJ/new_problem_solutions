---
oj: "roj"
problem_id: "3565"
title: "[NOIP2008-提高] 笨小猴"
description: "统计出现过的字母的次数，取最大值与最小值之差，试除判断差值是否为质数。"
difficulty: "入门"
date: 2026-10-02 08:01
updated: 2026-10-06 14:04
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3565
---

[[TOC]]

## 题目描述

给定一个只含小写字母、长度小于 $100$ 的单词，设 `maxn` 为出现次数最多的字母的出现次数，`minn` 为出现次数最少的字母的出现次数（都只在出现过的字母中比较）。输入一行一个单词；若 `maxn - minn` 是质数，输出两行 `Lucky Word` 与 `maxn - minn`，否则输出 `No Answer` 与 `0`。

样例 1：`error` → `Lucky Word` / `2`；样例 2：`olympic` → `No Answer` / `0`。

## 思路

统计每个出现过的字母的出现次数，取最大值与最小值之差 `diff`，再用试除法判断 `diff` 是否为质数即可，注意 $0$ 和 $1$ 都不是质数。单词长度不足 $100$，怎么写都能通过。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
