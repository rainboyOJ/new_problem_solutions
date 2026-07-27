---
oj: "luogu"
problem_id: "P5724"
title: "【深基4.习5】求极差 / 最大跨度值 / 最大值和最小值的差"
description: "读入整数列表后分别求最大值和最小值，两者相减得到极差。"
difficulty: "入门"
date: 2026-07-15 18:35
toc: true
tags: ["模拟", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5724
---

[[TOC]]

### 题意

给出 `n` 个整数，求这一组数的极差，也就是：

```text
最大值 - 最小值
```

### 思路

Python 的列表可以直接配合 `max` 和 `min` 使用。

读入第二行的所有整数后：

```text
answer = max(numbers) - min(numbers)
```

就得到极差。

如果用手写循环，也是在扫描过程中维护当前最大值和最小值。本题数据范围很小，使用内置函数更适合教学：代码短，含义也和题意完全一致。

这题是列表与内置函数练习，`brute.py` 会重复同一件事，因此不创建额外暴力文件。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `list(map(int, input().split()))` 读取一行整数数组。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：本题是“第一行 `n`，第二行数组”的标准输入格式。
- `max(numbers)` 返回列表最大值。
- `min(numbers)` 返回列表最小值。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

max-min：

@include-code(./main-pythonic.py, python)


### 复杂度

`max` 和 `min` 都会扫描一遍列表，时间复杂度是 $O(n)$；存储输入列表需要 $O(n)$ 空间。

### 总结

极差就是最大值减最小值。Python 的 `max`、`min` 能直接表达这个定义，适合入门题中优先掌握。
