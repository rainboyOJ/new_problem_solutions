---
oj: "luogu"
problem_id: "P5713"
title: "【深基3.例5】洛谷团队系统"
description: "分别计算本地和洛谷团队耗时，用条件表达式输出更短方案。"
difficulty: "入门"
date: 2026-07-15 18:07
toc: true
tags: ["python", "入门", "条件判断", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5713
---

[[TOC]]

### 题意

配置 `n` 道题。本地每题花 `5` 分钟；洛谷团队每题花 `3` 分钟，还要额外花 `11` 分钟。若本地更短输出 `Local`，否则输出 `Luogu`。

### 思路

直接计算两种方案总耗时：

- `local = 5 * n`
- `luogu = 3 * n + 11`

如果 `local < luogu`，本地更短；否则按题意输出 `Luogu`。

`brute.py` 不适合这题，因为直接比较两个公式就是完整解法。

### Python 知识

- 条件表达式 `"Local" if local < luogu else "Luogu"` 可以把二选一输出写成一行。
- 注意题目说“本地配置花费的总时间短”才输出 `Local`，相等时输出 `Luogu`。
- 先把两个方案分别命名成变量，比直接把公式塞进 `if` 更容易检查。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：输出字符串答案。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

条件表达式：

@include-code(./main-pythonic.py, python)


### 复杂度

只做常数次运算和比较，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

比较方案类题目，先把每个方案的代价算出来，再比较。特别注意题面中“小于”和“小于等于”的区别。
