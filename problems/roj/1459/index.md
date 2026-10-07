---
oj: "roj"
problem_id: "1459"
title: "「一本通 2.1 练习 3」Friends"
description: "通过奇偶性判断与前缀字符串哈希 O(1) 拼接比较，枚举删除位置求出唯一的原字符串"
difficulty: "普及"
date: 2026-09-30 11:51
updated: 2026-10-06 00:12
toc: true
tags:
  - "字符串"
  - "字符串哈希"
favorite: false
favorite_reason: ""
categories:
  - "字符串哈希"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1459
---

[[TOC]]

## 题目描述

给定长度为 $N$ 的字符串 $U$。$U$ 是由原串 $S$ 复制两遍得到 $T=S+S$ 后，在 $T$ 的任意位置插入一个字符得到的。求原串 $S$：不存在输出 `NOT POSSIBLE`，多个本质不同输出 `NOT UNIQUE`，唯一则输出 $S$。$2\le N\le 2000001$。

## 思路

$N$ 为偶数时不可能。$N$ 为奇数时原串长度 $L=N/2$。枚举删除位置 $p$，利用前缀哈希 $O(1)$ 比较删除后的前半段与后半段是否相等，收集本质不同的候选 $S$ 并判唯一性。

## 参考代码

@include-code(./main.cpp, cpp)
