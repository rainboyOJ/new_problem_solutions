---
oj: "roj"
problem_id: "3544"
title: "明明的随机数"
description: "排序后 unique 去重，直接输出个数与升序结果。"
difficulty: "入门"
date: 2026-10-02 06:30
updated: 2026-10-06 13:35
toc: true
tags:
  - "排序"
  - "python"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3544
---

[[TOC]]

## 题目描述

输入 $N$（$N\leqslant100$）和 $N$ 个 $1\sim1000$ 的整数。先去重保留互异值，再从小到大输出互异值的个数 $M$ 及这 $M$ 个数。

## 思路

先 `sort` 排序，再用 `unique` 把相邻重复元素去掉，剩余前 $M$ 个即为升序互异值，直接输出即可。复杂度 $O(N\log N)$。

## 参考代码

@include-code(./main.cpp, cpp)
