---
oj: "luogu"
problem_id: "P5718"
title: "【深基4.例2】找最小值"
description: "读入整数列表后直接用 min 得到最小值。"
difficulty: "入门"
date: 2026-07-15 18:17
toc: true
tags: ["python", "入门", "枚举", "输入输出"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5718
---

[[TOC]]

### 题意

给出 `n` 个整数，输出其中的最小值。

### 思路

Python 内置 `min` 可以直接求可迭代对象中的最小值。读入第二行整数列表后，输出 `min(numbers)` 即可。

`brute.py` 不适合这题，因为内置最小值函数就是完整解法；若手写循环，本质也只是逐个比较。

### Python 知识

- `n = int(input())` 读取个数；本题代码不必使用 `n`，因为输入保证第二行给出对应数量。
- `list(map(int, input().split()))` 读取整数列表。
- `min(numbers)` 返回列表中的最小值。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数列表输入。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：最值维护思想。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：一行整数数组输入。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

min：

@include-code(./main-pythonic.py, python)


### 复杂度

`min` 会检查所有 `n` 个数，时间复杂度 $O(n)$，空间复杂度 $O(n)$。如果边读边维护最小值，可以把额外空间降到 $O(1)$。

### 总结

Python 中求最小值优先想到 `min`。当题目数据很小，先写清楚输入列表和 `min(numbers)`，比手写循环更适合入门学习。
