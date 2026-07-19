---
oj: "luogu"
problem_id: "P5709"
title: "【深基2.习6】Apples Prologue / 苹果和虫子"
description: "用向上取整计算已经吃掉的苹果数，并处理 t 为 0 的除零边界。"
difficulty: "入门"
date: 2026-07-15 18:02
toc: true
tags: ["python", "入门", "数学", "边界处理"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5709
---

[[TOC]]

### 题意

小 B 有 `m` 个苹果，吃完一个苹果需要 `t` 分钟。经过 `s` 分钟后，问还剩多少个完整苹果。

### 思路

如果 `t > 0`，已经开始吃过的苹果数是 $\lceil s/t\rceil$。因为只要某个苹果已经被吃了一部分，它就不是完整苹果。

答案是：

$$
\max(0, m-\lceil s/t\rceil)
$$

但题目允许 `t = 0`，此时不能做除法。吃一个苹果不需要时间，可以认为所有苹果都会被吃完，所以答案是 `0`。

`brute.py` 不适合这题，因为核心是一个向上取整公式和一个除零边界。

### Python 知识

- `from math import ceil` 导入向上取整函数。
- `ceil(s / t)` 表示已经影响到多少个苹果。
- `max(0, m - eaten)` 防止剩余数量变成负数。
- 写除法前先检查除数是否可能为 `0`，这是 OJ 中很常见的边界意识。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：常用数学工具和边界意识。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入与输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单个答案输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

ceil + 条件表达式：

@include-code(./main-pythonic.py, python)


### 复杂度

只做常数次运算，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

“还剩完整的几个”往往需要向上取整计算已经被影响的数量。只要题面允许除数为 `0`，就必须先单独处理。
