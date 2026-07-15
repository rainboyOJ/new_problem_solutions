---
oj: "luogu"
problem_id: "P1223"
title: "排队接水"
description: "按接水时间从小到大排序，时间相同按编号从小到大，累加每个人开始前的等待时间。"
difficulty: "入门"
date: 2026-07-15 22:30
toc: true
tags: ["贪心", "排序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1223
---

[[TOC]]

### 题意

给定每个人接水所需时间，安排排队顺序，使平均等待时间最小。等待时间不包括自己的接水时间。

### 思路

让接水时间短的人先接水，可以减少后面所有人的等待总量。因此按接水时间从小到大排序。

若两人时间相同，题目要求编号小的人在前。把每个人保存成：

```text
(time, id)
```

Python 元组排序自然先按时间，再按编号。

计算等待时间时，维护已经过去的时间 `elapsed`。每个人的等待时间就是他开始接水前的 `elapsed`。

### Python 知识

- `people.sort()` 会按元组第一项、第二项依次排序。
- `print(*order)` 可以输出编号序列。
- `f"{total_wait / n:.2f}"` 输出平均等待时间，保留两位小数。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

### 复杂度

排序时间复杂度为 $O(n\log n)$，扫描计算等待时间为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

这题是最短处理时间优先的贪心模型。排序键 `(time, id)` 正好对应题目的全部比较规则。
