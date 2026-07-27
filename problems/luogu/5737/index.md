---
oj: "luogu"
problem_id: "P5737"
title: "【深基7.例3】闰年展示"
description: "封装闰年判断函数，枚举区间内年份并筛出所有闰年。"
difficulty: "入门"
date: 2026-07-15 21:08
toc: true
tags: ["模拟", "函数", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5737
---

[[TOC]]

### 题意

给定年份区间 `[x, y]`，输出其中闰年的个数，并按升序输出所有闰年。

### 思路

闰年规则是：

```text
能被 400 整除，或者能被 4 整除但不能被 100 整除。
```

把这个判断写成函数 `is_leap_year(year)`，再枚举 `start` 到 `end` 的所有年份，保留满足条件的年份。

这题是函数和区间枚举练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：一行两个整数用 `map(int, input().split())`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：列表推导式适合从区间中筛选结果。
- `range(start, end + 1)` 表示闭区间 `[start, end]`。
- `or` 和 `and` 可以直接表达闰年规则。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

列表推导筛闰年：

@include-code(./main-pythonic.py, python)


### 复杂度

设区间长度为 `L = y - x + 1`，时间复杂度是 $O(L)$，空间复杂度是 $O(L)$。

### 总结

遇到有明确判定规则的题，先把规则封装成布尔函数，再用枚举筛选，主流程会很清楚。
