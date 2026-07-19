---
oj: "luogu"
problem_id: "P2676"
title: "[USACO07DEC] Bookshelf B"
description: "把奶牛身高从高到低排序，贪心选择最高的奶牛直到总高度达到书架高度。"
difficulty: "入门"
date: 2026-07-15 22:18
toc: true
tags: ["贪心", "排序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2676
---

[[TOC]]

### 题意

给出若干奶牛身高和目标高度 `B`。选择尽量少的奶牛，使身高总和至少为 `B`。

### 思路

要让奶牛数量尽量少，每次都应该优先选择最高的奶牛。因此：

1. 将身高从高到低排序；
2. 从高到低累加；
3. 第一次达到 `B` 时，当前数量就是答案。

这是直接的贪心排序题。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sort(reverse=True)` 可以降序排序。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多行整数可用 `sys.stdin.buffer.read()` 统一读取。
- `break` 在达到目标后提前结束循环。

### 代码

@include-code(./main.py, python)


### 复杂度

排序时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

### 总结

“最少个数达到总和”且每个元素贡献独立时，优先选最大的元素是自然贪心。
