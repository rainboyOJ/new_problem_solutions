---
oj: "luogu"
problem_id: "P2141"
title: "[NOIP 2014 普及组] 珠心算测验"
description: "枚举两个不同数的和，用集合判断和是否在原集合中，并用集合避免重复计数。"
difficulty: "入门"
date: 2026-07-15 18:54
toc: true
tags: ["枚举", "集合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2141
---

[[TOC]]

### 题意

给出 `n` 个互不相同的正整数，问其中有多少个数可以表示成集合中另外两个不同数的和。

### 思路

`n <= 100`，可以直接枚举两个加数。

先把所有数放进集合 `values`，这样可以快速判断一个和是否出现在原集合中。

枚举所有 `i < j` 的数对，计算：

```text
total = numbers[i] + numbers[j]
```

如果 `total` 在 `values` 中，说明这个数满足要求。因为同一个目标数可能由多组加数得到，所以用集合 `can_be_sum` 保存满足条件的目标数，最后输出集合大小。

这题是点对枚举和集合判重练习，不创建额外 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：使用 `list(map(int, input().split()))` 读取数组。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：`for i in range(n)` 和 `for j in range(i + 1, n)` 枚举无序点对。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`set` 适合做成员判断和去重。
- `total in values` 判断和是否存在，`can_be_sum.add(total)` 避免重复计数。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

集合推导：

@include-code(./main-pythonic.py, python)

### 复杂度

枚举数对需要 $O(n^2)$ 次，集合查询均摊 $O(1)$。空间复杂度是 $O(n)$。

### 总结

这题不能统计“有多少种加法”，而是统计“有多少个数能被表示”。用集合保存答案，可以自然避免重复。
