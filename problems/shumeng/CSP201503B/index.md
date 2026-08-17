---
oj: "shumeng"
problem_id: "CSP201503B"
title: "数字排序"
description: "统计每个数的出现次数，再按频次降序、数值升序排序输出。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["排序", "计数"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201503B
---

[[TOC]]

## 形式化题目

给定 $n$ 个整数，输出每个出现过的整数及其出现次数。输出顺序按出现次数**从多到少**排列；次数相同时按数值**从小到大**排列。

## 思路

先看一个不借助计数数组的小数据基准：先收集互不相同的数字，再按“次数最多、值最小”的规则反复选出下一个要输出的数字。

@include-code(./brute.cpp, cpp)

`brute.cpp` 用两重循环统计频率，再每次扫描选出当前最优条目，逻辑最贴合题意，适合作为对拍基准。

**正式做法**分两步：

1. **统计**：给出的数都是 $0 \sim 1000$ 的非负整数，直接用大小为 $1001$ 的计数数组 `count_value` 记录每个数字的出现次数。
2. **排序**：把所有出现过的数字封装成 `(value, count)` 条目，按比较器排序——先让较大的 `count` 在前，`count` 相同时让较小的 `value` 在前。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：统计为 $O(n)$，设不同数字数为 $k$，排序为 $O(k\log k)$。
- 空间：$O(1001 + k)$。

## 总结

有重复元素的排序题，先压缩为“值和频次”的条目，再把题意的主关键字（次数降序）和次关键字（数值升序）完整写进比较器即可。计数数组比 `map` 更快，适合值域小的题目。