---
oj: "luogu"
problem_id: "P5720"
title: "【深基4.例4】一尺之棰"
description: "用 while 循环反复整除 2，并统计长度第一次变为 1 的天数。"
difficulty: "入门"
date: 2026-07-15 18:22
toc: true
tags: ["python", "入门", "循环", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5720
---

[[TOC]]

### 题意

第一天木棍长度为 `a`。从第二天开始，每天长度变为原来的一半并向下取整。问第几天长度会变成 `1`。

### 思路

第一天已经算一天，所以 `days = 1`。只要长度还大于 `1`，就做一次 `length //= 2`，同时天数加一。循环结束时，长度第一次不大于 `1`；由于题目长度为正整数，这时就是 `1`。

`brute.py` 不适合这题，因为这个 while 模拟就是完整解法。

### Python 知识

- `while length > 1:` 表示只要条件成立就继续循环。
- `length //= 2` 是整数除法赋值，相当于 `length = length // 2`。
- 循环计数时要先确定初始状态是否已经算一次，本题第一天长度为 `a`，所以初始天数是 `1`。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：整数除法相关工具。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

while 折半：

@include-code(./main-pythonic.py, python)

### 复杂度

每次长度至少减半，循环次数是 $O(\log a)$，空间复杂度 $O(1)$。

### 总结

当题目描述“反复做某个操作直到满足条件”时，`while` 循环很自然。关键是把初始天数和循环条件想清楚。
