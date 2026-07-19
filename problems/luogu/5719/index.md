---
oj: "luogu"
problem_id: "P5719"
title: "【深基4.例3】分类平均"
description: "遍历 1 到 n，把 k 的倍数和非倍数分别累加计数，再格式化输出平均值。"
difficulty: "入门"
date: 2026-07-15 18:22
toc: true
tags: ["python", "入门", "循环", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5719
---

[[TOC]]

### 题意

把 `1..n` 的正整数分成两类：能被 `k` 整除的数，和不能被 `k` 整除的数。输出两类数的平均值，保留 1 位小数。

### 思路

直接遍历 `1..n`。如果 `x % k == 0`，把它加入 A 类；否则加入 B 类。两类都分别维护“总和”和“数量”，最后计算平均值。

`brute.py` 不适合这题，因为逐个分类累加就是完整解法。

### Python 知识

- `range(1, n + 1)` 会产生从 `1` 到 `n` 的整数。
- `x % k == 0` 判断 `x` 是否是 `k` 的倍数。
- 平均值是 `sum / count`。
- `f"{value:.1f}"` 控制输出小数点后 1 位。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入和格式化输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：控制浮点小数位数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：取模和整数工具。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

列表推导分类：

@include-code(./main-pythonic.py, python)


### 复杂度

遍历 `1..n` 一次，时间复杂度 $O(n)$，空间复杂度 $O(1)$。

### 总结

分类统计题通常维护每一类的计数和总和。最后再统一计算平均值，能避免边遍历边处理格式的问题。
