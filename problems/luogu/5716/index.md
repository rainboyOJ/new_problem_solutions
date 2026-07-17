---
oj: "luogu"
problem_id: "P5716"
title: "【深基3.例9】月份天数"
description: "先判断闰年，再用月份天数列表按下标取出答案。"
difficulty: "入门"
date: 2026-07-15 18:07
toc: true
tags: ["python", "入门", "条件判断", "列表"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5716
---

[[TOC]]

### 题意

输入年份 `y` 和月份 `m`，输出这一年这个月有多少天。二月需要考虑闰年。

### 思路

先用闰年规则判断 `is_leap`。然后准备一个长度为 `12` 的列表，保存每个月的天数，其中二月根据闰年结果选择 `29` 或 `28`。

月份是从 `1` 开始编号，而 Python 列表下标从 `0` 开始，所以第 `m` 个月对应 `days[m - 1]`。

`brute.py` 不适合这题，因为这是规则判断和查表题。

### Python 知识

- 闰年表达式可以复用：`(y % 4 == 0 and y % 100 != 0) or (y % 400 == 0)`。
- 列表可以保存固定的十二个月天数。
- `29 if is_leap else 28` 是条件表达式，用来决定二月天数。
- `days[m - 1]` 体现了“题目编号从 1 开始，列表下标从 0 开始”的转换。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入和列表基础。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单个答案输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：取模和整数判断。

### 代码

@include-code(./main.py, python)

### match-case 写法

月份是离散分支，可用 `case 1 | 3 | ...` 合并同天数月份：

@include-code(./match_case.py, python)

### 复杂度

列表长度固定为 `12`，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

固定月份天数适合用列表查表。只要先处理好二月，再注意 `m - 1` 的下标转换，代码会比很多层 `if` 更清楚。
