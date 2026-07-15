---
oj: "luogu"
problem_id: "P1425"
title: "小鱼的游泳时间"
description: "把开始和结束时间都换成总分钟数，相减后用 divmod 拆成小时和分钟。"
difficulty: "入门"
date: 2026-07-15 17:56
toc: true
tags: ["python", "入门", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1425
---

[[TOC]]

### 题意

给出开始时间 `a` 时 `b` 分和结束时间 `c` 时 `d` 分，求这段时间一共经过了多少小时多少分钟。题目保证结束时间晚于开始时间。

### 思路

不要在小时和分钟之间手工借位。先把两个时间点都换成总分钟数：

- `start = a * 60 + b`
- `end = c * 60 + d`

差值 `end - start` 就是总游泳分钟数。最后把总分钟数除以 `60`，得到小时和剩余分钟。

`brute.py` 不适合这题，因为这是一道直接时间换算题。文章重点是 Python 中的 `divmod` 写法。

### Python 知识

- `a, b, c, d = map(int, input().split())` 一次读入四个整数。
- `divmod(x, 60)` 同时返回 `x // 60` 和 `x % 60`。
- `print(hours, minutes)` 默认用一个空格分隔，正好符合题目输出格式。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：一行多整数输入和输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：`divmod` 的含义。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：空格分隔输出。

### 代码

@include-code(./main.py, python)

### 复杂度

只做常数次运算，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

计算时间差时，先统一成分钟最稳。`divmod` 可以把“求商”和“求余数”合在一行里，代码比手写两行更清楚。
