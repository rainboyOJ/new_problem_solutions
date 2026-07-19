---
oj: "luogu"
problem_id: "P1923"
title: "【深基9.例4】求第 k 小的数"
description: "读入所有数字后用 Python 内置排序，输出排序后下标为 k 的元素。"
difficulty: "普及-"
date: 2025-12-31 17:10
toc: true
tags: ["排序", "选择", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1923
---

[[TOC]]

### 题意

给出 `n` 个数，最小的数编号为第 `0` 小，要求输出第 `k` 小的数。

### 思路

Python 竞赛中最稳的写法是先排序：

```python
numbers.sort()
print(numbers[k])
```

排序后，列表下标 `0` 是最小值，下标 `k` 正好是第 `k` 小。题面希望练习分治选择算法，但在本 Python 教学题单中，这题用来练习大量整数读入和内置排序。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`list.sort()` 原地升序排序。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量整数输入使用 `sys.stdin.buffer.read()`。
- Python 列表下标从 `0` 开始，正好对应题目的“第 0 小”。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sorted 第 k：

@include-code(./main-pythonic.py, python)


### 复杂度

排序时间复杂度是 $O(n\log n)$，保存输入需要 $O(n)$ 空间。

### 总结

第 k 小可以用选择算法优化，但 Python 入门阶段先掌握“读入、排序、取下标”这条稳定路径。
