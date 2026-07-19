---
oj: "luogu"
problem_id: "P1088"
title: "[NOIP 2004 普及组] 火星人"
description: "手写原地 next permutation，连续执行 M 次，得到当前排列之后第 M 个字典序排列。"
difficulty: "普及-"
date: 2026-07-15 21:40
toc: true
tags: ["排列", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1088
---

[[TOC]]

### 题意

给定 `1..N` 的一个排列，以及一个很小的整数 `M`。要求输出这个排列在字典序中向后移动 `M` 次后的排列。

`N` 可以到 `10000`，不能生成所有排列。

### 思路

需要手写“下一个排列”。

从右往左看，找到第一个还能变大的位置 `i`，也就是：

```text
a[i] < a[i + 1]
```

此时 `i` 右边的后缀是降序的。为了得到刚好大一点的排列：

1. 在后缀中从右往左找第一个大于 `a[i]` 的数；
2. 交换它和 `a[i]`；
3. 把后缀反转成升序。

因为 `M <= 100`，执行 `M` 次 `next_permutation` 即可。

### Python 知识

- 列表可以原地交换：`a[i], a[j] = a[j], a[i]`。
- 切片赋值 `a[i + 1:] = reversed(a[i + 1:])` 可以把后缀反转后写回原列表。
- `print(*numbers)` 用空格输出整个排列。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)


### 复杂度

一次 `next_permutation` 是 $O(N)$，执行 `M` 次，总时间复杂度为 $O(MN)$。空间复杂度为 $O(N)$。

### 总结

这题不能把所有排列列出来，而是要掌握字典序下“下一个排列”的局部修改规则。
