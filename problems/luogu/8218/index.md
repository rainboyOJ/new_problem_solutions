---
oj: "luogu"
problem_id: "P8218"
title: "【深进1.例1】求区间和"
description: "用 accumulate 构造带前导零的前缀和，让每次区间询问都能 O(1) 作答。"
difficulty: "普及-"
date: 2026-07-16 17:48
toc: true
tags: ["前缀和", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P8218
---

[[TOC]]

### 题意

给定一个长度为 $n$ 的序列，回答 $m$ 个闭区间 $[l,r]$ 的元素和。

### 思路

令 `prefix[i]` 表示前 `i` 个数之和，则区间和为 `prefix[r] - prefix[l - 1]`。预处理一次后，每个询问只做一次减法。

### Python 知识

- `accumulate(a, initial=0)` 直接产生长度为 $n+1$ 的前缀和，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`。
- `"\n".join(...)` 一次输出多行答案，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`。
- 嵌套生成器按需读取每组 `l, r`，不必保存全部询问。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n+m)$，空间复杂度 $O(n)$。

### 总结

固定数组上的大量区间和询问，是前缀和最直接的应用。
