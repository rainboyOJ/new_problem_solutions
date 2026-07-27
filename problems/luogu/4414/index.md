---
oj: "luogu"
problem_id: "P4414"
title: "[COCI 2006/2007 #2] ABC"
description: "排序三个数后建立 A/B/C 到小中大值的映射，再按给定顺序输出。"
difficulty: "入门"
date: 2026-07-15 18:17
toc: true
tags: ["python", "入门", "排序", "字典"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4414
---

[[TOC]]

### 题意

给出三个数，它们分别是 `A < B < C` 的某种乱序排列。第二行给出由 `A/B/C` 组成的输出顺序，要求按这个顺序输出对应数字。

### 思路

先排序三个数，得到小、中、大。然后建立映射：

- `A -> 最小值`
- `B -> 中间值`
- `C -> 最大值`

最后遍历顺序字符串，输出对应的数字。

`brute.py` 不适合这题，因为排序和映射就是完整解法。

### Python 知识

- `sorted(...)` 把三个数排成升序。
- 字典 `named` 可以保存字符到数字的映射。
- `print(*(named[ch] for ch in order))` 用星号展开生成器，空格分隔输出多个值。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sorted` 的用法。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典保存键到值的映射。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：输出数组。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

match-case + print*：

@include-code(./main-pythonic.py, python)

### match-case 写法

输出顺序中的 `A/B/C` 可用 `match ch` 映射到已排序的小中大：

@include-code(./match_case.py, python)

### 复杂度

只处理三个数，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

当题目给出符号顺序时，可以先把符号映射到实际值，再按顺序查表输出。字典能让这种对应关系很清楚。
