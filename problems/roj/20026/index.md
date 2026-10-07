---
oj: "roj"
problem_id: "20026"
title: "非递减字符串"
description: "非递减的最终串只能是 A…AB…B 的形态，枚举分割点并用前缀和 O(1) 计算翻转代价。"
difficulty: "普及-"
date: 2026-09-06 15:54
updated: 2026-10-07 10:45
toc: true
tags: ["字符串", "枚举", "前缀和"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20026
---

[[TOC]]

## 题目描述

给定一个长度为 $n$ 的、仅由字符 `A` 和 `B` 组成的字符串 $S$。每次操作可以把任意一个字符翻成另一个。求最少多少次操作后，字符串变成非递减的（即最终串形如 $A^p B^{n-p}$）。

输入为一行字符串 $S$；输出一个整数表示最少操作次数。$1\le n\le 10^6$。

样例输入：`AABBA`，样例输出：`1`。

## 思路

最终合法串只能是前 $p$ 个 `A` 接后 $n-p$ 个 `B`，共 $n+1$ 种形态。枚举分割点 $p$，代价为前 $p$ 位中 `B` 的个数加上后 $n-p$ 位中 `A` 的个数，用前缀和 $O(1)$ 计算，取最小值。

## 参考代码

@include-code(./main.cpp, cpp)
