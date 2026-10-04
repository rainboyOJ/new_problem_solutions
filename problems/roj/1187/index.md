---
oj: "roj"
problem_id: "1187"
title: "统计字符数"
description: "用 Counter 一次扫描统计 26 个小写字母频次，再以 (频次, -ASCII) 为关键字取最大。"
difficulty: "入门"
date: 2026-09-29 22:40
updated: 2026-10-04 14:35
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

## 形式化题目

给定字符串 $S$，$|S| \leqslant 1000$，$S_i \in \{a, \dots, z\}$。求字符 $c$ 使得 $c$ 在 $S$ 中出现次数最大；若有多个字符出现次数同为最大，取 ASCII 码最小者。输出 $c$ 与出现次数。

## 正解

### 思路

字符集只有 26 个小写字母，可直接统计每个字符出现次数。得到频次表后，按“次数最多、次数相同则 ASCII 最小”的规则选出答案。

Python 中 `collections.Counter` 能在一次扫描内完成频次统计。取最大时把关键字设为 $(\text{频次}, -\text{ASCII})$：`max` 优先比较频次；频次相同时会比较 $-\text{ASCII}$，其值越大代表原 ASCII 越小，因此自然得到 ASCII 最小的字符。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(|S|)$，空间复杂度 $O(1)$（最多 26 个不同字符）。

## 总结

本题是计数类入门题：一次扫描得到频次，再用复合关键字取最值即可。
