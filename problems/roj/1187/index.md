---
oj: "roj"
problem_id: "1187"
title: "统计字符数"
description: "统计 26 个小写字母的出现次数，再从 'a' 到 'z' 依次取严格更大者，即可得到次数最多且 ASCII 最小的字符。"
difficulty: "入门"
date: 2026-09-29 22:40
updated: 2026-10-05 04:41
toc: true
tags: ["字符串", "计数"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1187"
---

[[TOC]]

## 题目描述

输入一行由 26 个小写字母组成的字符串 $S$，$|S| \leqslant 1000$。输出 $S$ 中出现次数最多的字符及次数，中间用一个空格分隔；若有多个字符次数并列最多，输出 ASCII 码最小的那个。样例输入 `abbccc`，期望输出 `c 3`。

## 思路

字符集只有 26 个小写字母，用大小为 26 的数组一次扫描统计每个字母的频次；随后从 `a` 到 `z` 顺序扫描，只在频次严格更大时更新答案，这样并列最大时会自然保留 ASCII 码最小的字符。时间复杂度 $O(|S|)$。

## 参考代码

@include-code(./main.cpp, cpp)
