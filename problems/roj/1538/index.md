---
oj: "roj"
problem_id: "1538"
title: "清点人数"
description: "查询位置单调递增，用一个只前进的指针维护前缀和：走过车厢时累加，未到车厢的上下车直接改状态，总复杂度 O(n+k)。"
difficulty: "普及-"
date: 2026-09-30 16:54
updated: 2026-10-06 00:42
toc: true
tags: ["前缀和", "双指针", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1538
---

[[TOC]]

## 题目描述

$n$ 节车厢初始没人。处理 $k$ 个事件：`B m p` 表示第 $m$ 节上车 $p$ 人，`C m p` 表示下车 $p$ 人，`A m` 询问前 $m$ 节车厢总人数。每次询问的 $m$ 严格递增，主任只往前走不回头。数据范围 $1\le n,k\le 5\times10^5$。

## 思路

用 `pos` 记录主任已走到的车厢，`total` 维护前 `pos` 节人数和。`A m` 时把 `pos` 一路推进到 $m$ 并累加经过车厢的净人数；`B/C` 若 $m\le pos$ 直接改 `total`，否则先记在对应车厢。指针只前进，总推进次数不超过 $n$，时间复杂度 $O(n+k)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
