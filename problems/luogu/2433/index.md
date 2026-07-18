---
oj: "luogu"
problem_id: "P2433"
title: "【深基1-2】小学数学 N 合一"
description: "把 14 个固定问题的答案整理成字典，根据输入编号输出对应文本。"
difficulty: "入门"
date: 2026-07-15 18:02
toc: true
tags: ["python", "入门", "分支", "输出"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2433
---

[[TOC]]

### 题意

输入一个题号 `T`，范围是 `1..14`。每个题号对应一道固定的小学数学题，程序只需要输出对应答案。

### 思路

这题可以写很长的 `if/elif`。但这些答案都是固定文本，用字典保存会更清楚：

- 键是题号；
- 值是要输出的答案字符串；
- 多行答案直接在字符串中写 `\n`。

读入 `T` 后输出 `answers[T]` 即可。

`brute.py` 不适合这题，因为它是固定答案分支题，不存在需要验证的优化算法。

### Python 知识

- 字典 `{1: "...", 2: "..."}` 可以把题号映射到答案。
- 字符串中的 `\n` 表示换行，适合保存多行输出。
- `answers[t]` 根据输入编号取出对应答案。
- `print(text, end="")` 可以避免额外追加最后一个换行，便于精确匹配固定输出。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：普通字典保存键到值的映射。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串、多行输出和输入解析。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：按题面控制输出格式。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

match-case：

@include-code(./main-pythonic.py, python)

### match-case 写法

题号是离散分支，用 `match-case` 按编号分发同样清晰：

@include-code(./match_case.py, python)

### 复杂度

字典大小固定，查询一次即可，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

当题目是“编号 -> 固定答案”时，字典比很长的分支更容易检查。多行答案可以直接保存在字符串中，输出时不要再手动拼很多 `print`。
