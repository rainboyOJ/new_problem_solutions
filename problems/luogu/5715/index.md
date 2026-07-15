---
oj: "luogu"
problem_id: "P5715"
title: "【深基3.例8】三位数排序"
description: "读入三个整数，用 sorted 得到升序列表，再用星号展开输出。"
difficulty: "入门"
date: 2026-07-15 18:07
toc: true
tags: ["python", "入门", "排序", "输入输出"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5715
---

[[TOC]]

### 题意

输入三个整数，按从小到大输出。

### 思路

Python 已经提供排序工具。把输入的三个数读成列表，调用 `sorted(numbers)` 得到升序新列表，然后空格分隔输出。

`brute.py` 不适合这题，因为排序工具直接表达了完整解法。

### Python 知识

- `list(map(int, input().split()))` 把输入转成整数列表。
- `sorted(numbers)` 返回一个新的升序列表，不修改原列表。
- `print(*numbers)` 会把列表元素展开，默认用空格分隔输出。
- 不要直接 `print(numbers)`，那会输出 Python 列表格式，如 `[1, 5, 14]`。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sorted` 与 `list.sort`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：列表输入和多值输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：输出数组。

### 代码

@include-code(./main.py, python)

### 复杂度

这里只有三个数，可以看成时间复杂度 $O(1)$，空间复杂度 $O(1)$。如果推广到 $n$ 个数，排序时间复杂度是 $O(n\log n)$。

### 总结

Python 排序题先想到 `sorted`。输出列表时用 `print(*a)`，让格式变成 OJ 需要的空格分隔整数。
