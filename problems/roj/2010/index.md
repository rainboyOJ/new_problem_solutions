---
oj: "roj"
problem_id: "2010"
title: "修理牛棚"
description: "一整块板覆盖全部牛棚后，贪心地在最大的 C−M 个牛棚间隙处切开，砍掉的总长度恰好等于最小木板总长。"
difficulty: "入门"
date: 2026-10-01 02:41
updated: 2026-10-06 09:25
toc: true
tags: ["贪心", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2010
---

[[TOC]]

## 题目描述

编号 $1 \sim S$ 的牛棚排成一行，其中 $C$ 个有牛。可买至多 $M$ 块木板，每块覆盖一个连续区间，要求所有有牛牛棚都被覆盖，求木板总长度最小值。

数据范围：$1 \le M \le 50$，$1 \le S \le 200$，$1 \le C \le S$。

## 思路

先假设用一整块板覆盖最左到最右的有牛牛棚。相邻有牛牛棚之间的空棚间隙如果越大，在这里断开越省长度。因此把间隙从大到小排序，切掉前 $k-1$ 大的间隙（$k = \min(M, C)$），答案等于整块长度减去这些间隙之和。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
