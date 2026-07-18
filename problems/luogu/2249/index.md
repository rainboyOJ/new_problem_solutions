---
oj: "luogu"
problem_id: "P2249"
title: "【深基13.例1】查找"
description: "对单调不减数组使用 bisect_left，验证命中后返回目标第一次出现的下标。"
difficulty: "普及-"
date: 2026-07-16 17:49
toc: true
tags: ["二分", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2249
---

[[TOC]]

### 题意

给出一个单调不减数组和若干询问。每次要找目标值第一次出现的编号；不存在时输出 `-1`。题目使用从 `1` 开始的编号。

### 思路

`bisect_left(numbers, value)` 返回 `value` 应该插入的最左位置。若该位置仍在数组内，并且元素确实等于 `value`，它就是第一次出现的位置；否则数组中没有这个值。

例如数组为 `1 3 3 3 5`，查询 `3` 时得到下标 `1`。Python 下标从 `0` 开始，输出时加一得到题目编号 `2`。

### Python 知识

- `bisect_left` 等价于 C++ 的 `lower_bound`，返回第一个不小于目标的位置。
- `map(first_position, queries)` 把同一个查询函数应用到每个询问；`print(*)` 再把答案按空格展开。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量整数使用 `sys.stdin.buffer.read().split()` 一次读取。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：已有函数时，`map` 可以简洁表达一一映射。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

bisect + print*：

@include-code(./main-pythonic.py, python)

### 复杂度

每次查询时间复杂度为 $O(\log n)$，总时间复杂度为 $O(m\log n)$；保存数组和询问需要 $O(n+m)$ 空间。

### 总结

`bisect_left` 只给出插入位置，因此必须再检查该位置是否真的等于目标值，并注意把 Python 的零下标转换成题目的编号。
