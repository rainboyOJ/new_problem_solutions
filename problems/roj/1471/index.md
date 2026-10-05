---
oj: "roj"
problem_id: "1471"
title: "「一本通 2.3 例 1」Phone List"
description: "排序后只需检查相邻两串：字典序下前缀对必紧贴，一趟 sort 加相邻前缀判定即可。"
difficulty: "普及-"
date: 2026-09-30 12:43
updated: 2026-10-06 00:19
toc: true
tags: ["字符串", "排序", "前缀", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1471
---

[[TOC]]

## 题目描述

给定 $n$ 个长度不超过 $10$ 的数字串，判断是否存在两个串 $S,T$ 使 $S$ 是 $T$ 的前缀（两串相等也算）。多组数据：第一行组数 $T$，每组第一行 $n$，随后 $n$ 行是数字串；存在前缀对输出 `NO`，否则输出 `YES`（注意题面的反直觉对应）。数据范围 $1\le T\le 40$，$1\le n\le 10^4$。

样例：第一组 `911, 97625999, 91125426` 输出 `NO`（`911` 是 `91125426` 的前缀）；第二组 `113, 12340, 123440, 12345, 98346` 输出 `YES`。

## 思路

把所有串按字典序排序：若存在前缀对，则它们在排序中一定相邻，所以只需检查 $n-1$ 个相邻对。逐对判断前一串是否为后一串的前缀，命中即有前缀对，输出 `NO`，否则输出 `YES`。单组复杂度 $O(nL\log n)$，$L\le 10$ 为串长上限。

## 参考代码

@include-code(./main.cpp, cpp)
