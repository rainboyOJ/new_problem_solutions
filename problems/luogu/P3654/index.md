---
oj: "luogu"
problem_id: "P3654"
title: "First Step (ファーストステップ)"
description: "枚举每个横向和纵向长度为 K 的连续区间，判断其中是否全部为空地；K=1 时单独计数空格。"
difficulty: "入门"
date: 2026-07-15 21:40
toc: true
tags: ["枚举", "矩阵", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3654
---

[[TOC]]

### 题意

给定一个 `R x C` 的矩阵，`.` 表示空地，`#` 表示障碍。要找出有多少种方法放下一条长度为 `K` 的直线队伍，方向可以横向或纵向，所有位置都必须是空地。

### 思路

直接枚举每个可能的起点。

横向放置时，起点 `(row, col)` 需要满足 `col + K - 1 < C`，然后检查这一段是否全是 `.`。

纵向放置时，起点 `(row, col)` 需要满足 `row + K - 1 < R`，然后检查这一段是否全是 `.`。

需要特别注意 `K = 1`。此时横向和纵向的同一个空格表示同一种站位，不能重复计数，所以直接统计空地数量。

### Python 知识

- `all(...)` 可以判断一段格子是否全部满足条件，并且遇到第一个不满足的格子会短路。
- `row.count(".")` 可以统计一行中的空地数量。
- 用 `range(c - k + 1)` 控制横向起点，避免越界。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

每个起点最多检查 `K` 个格子，时间复杂度为 $O(RCK)$，空间复杂度为 $O(RC)$。

### 总结

矩阵枚举题先确定“起点范围”，再写合法性检查。`K=1` 的重复计数是本题最容易漏掉的边界。
