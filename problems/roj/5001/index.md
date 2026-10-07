---
oj: "roj"
problem_id: "5001"
title: "方圆游戏"
description: "每次合并都让 1 的个数奇偶翻转一次，合并 n-1 次后末位图形的值被奇偶闭式定死，A 胜当且仅当 1 的个数加长度为奇数。"
difficulty: "普及-"
date: 2026-10-02 15:16
updated: 2026-10-06 16:30
toc: true
tags: ["贪心", "博弈", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/5001
---

[[TOC]]

## 题目描述

给定一个长度为 $n$ 的 0/1 串，`0` 表示圆、`1` 表示正方形。A、B 轮流操作（A 先手），每步任选两块图形（不必相邻），按规则替换：两块相同 → 正方形；两块不同 → 圆。重复直到只剩一块，若最后是圆则 A 胜，否则 B 胜。$n \le 1000$，$T$ 组数据。

## 思路

设 $S$ 为当前串中 `1` 的个数。一次合并后 $S' \equiv S+1 \pmod 2$，即每合并一次奇偶必翻转，与选哪两块无关。$n$ 个字符恰好合并 $n-1$ 次，末位图形的值被闭式 $v \equiv S_0+n-1 \pmod 2$ 唯一确定。因此 A 必胜当且仅当 $S_0+n-1$ 为偶数。

## 参考代码

@include-code(./main.cpp, cpp)
