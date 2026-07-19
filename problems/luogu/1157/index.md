---
oj: "luogu"
problem_id: "P1157"
title: "组合的输出"
description: "用 itertools.combinations 按字典序枚举 1 到 n 中选 r 个数，并用格式化字符串控制每个数宽度为 3。"
difficulty: "入门"
date: 2026-07-15 21:30
toc: true
tags: ["枚举", "组合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1157
---

[[TOC]]

### 题意

从 `1..n` 中选出 `r` 个数，按字典序输出所有组合。每个数字输出时占 `3` 个字符宽度。

### 思路

组合要求：

- 每行内部数字递增；
- 所有行按字典序排列；
- 不关心选择顺序，只关心选出的集合。

`itertools.combinations(range(1, n + 1), r)` 正好满足这些条件。它会按照输入序列的顺序生成组合，所以输出顺序就是题目要求的字典序。

每个数占 `3` 个字符，可以写成：

```python
f"{number:3d}"
```

再把一行中的字段拼接起来输出。

### Python 知识

- `combinations(range(1, n + 1), r)` 表示从 `1..n` 中选 `r` 个。
- `f"{number:3d}"` 是格式化字符串，含义是整数右对齐，占 `3` 个字符宽度。
- `"".join(...)` 把一行的多个格式化字段拼成一个字符串。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)



### 复杂度

会输出 $\binom{n}{r}$ 行，每行有 `r` 个数。时间复杂度为 $O(r\binom{n}{r})$，空间复杂度为 $O(r)$。

### 总结

这题的重点不是手写递归，而是学会把“按字典序输出组合”直接交给 `itertools.combinations`。
