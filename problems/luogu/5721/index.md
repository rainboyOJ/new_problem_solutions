---
oj: "luogu"
problem_id: "P5721"
title: "【深基4.例6】数字直角三角形"
description: "用双层循环按行生成两位编号字符串，再用 join 拼接多行输出。"
difficulty: "入门"
date: 2026-07-15 18:22
toc: true
tags: ["python", "入门", "循环", "输出格式"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5721
---

[[TOC]]

### 题意

输入 `n`，输出一个数字直角三角形。第一行有 `n` 个数，第二行有 `n-1` 个数，直到最后一行 1 个数。所有数字都要输出成两位，不足两位补前导 `0`。

### 思路

用 `current` 记录当前要输出的数字。外层循环控制每行宽度，从 `n` 递减到 `1`；内层循环生成这一行的所有两位数字。

每行先放进 `row` 列表，再用 `"".join(row)` 拼成一行。所有行放进 `lines`，最后用 `"\n".join(lines)` 输出。

`brute.py` 不适合这题，因为它是输出格式练习题。

### Python 知识

- `range(n, 0, -1)` 会产生 `n, n-1, ..., 1`。
- `f"{current:02d}"` 表示整数宽度至少为 2，不足时左侧补 `0`。
- `"".join(row)` 拼接同一行，`"\n".join(lines)` 拼接多行。
- 先收集字符串再一次输出，能更容易控制末尾换行。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串拼接和多行输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：输出多行答案。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

格式化填三角：

@include-code(./main-pythonic.py, python)

### 复杂度

输出的数字个数是 $1+2+\cdots+n=O(n^2)$，时间复杂度 $O(n^2)$，空间复杂度 $O(n^2)$ 用于保存输出行。

### 总结

格式输出题先设计“每一行怎么生成”，再处理“多行怎么连接”。`02d` 是补零输出的常用格式。
