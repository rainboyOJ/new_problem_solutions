---
oj: "luogu"
problem_id: "P1320"
title: "压缩技术（续集版）"
description: "把输入矩阵按行拼成一维字符串，从 0 开始统计交替游程长度并输出压缩码。"
difficulty: "入门"
date: 2026-07-15 18:58
toc: true
tags: ["模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1320
---

[[TOC]]

### 题意

输入一个 `n * n` 的 `01` 矩阵，要求输出它的压缩码。压缩码第一个数是 `n`，后面从连续 `0` 的个数开始，交替记录连续 `1`、连续 `0` 的长度。

### 思路

先把所有输入行拼成一个一维字符串 `text`。然后从当前字符 `"0"` 开始统计。

如果当前读到的字符等于 `current`，计数加一；否则说明当前游程结束，把计数加入答案，再切换 `current`，重新从 `1` 开始计数。

注意：即使矩阵第一个字符是 `1`，压缩码也必须先输出连续 `0` 的个数，也就是 `0`。

这题是游程编码练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：不知道行数时，可以读到 EOF。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`"".join(rows)` 可以把多行拼成一维字符串。
- `try/except EOFError` 可以用 `input()` 读到文件结束。
- `print(*answer)` 按空格输出压缩码。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

用 `groupby` 做游程编码；若以 `1` 开头则先补一段长度为 `0` 的 `0`：

@include-code(./main-pythonic.py, python)

### 复杂度

每个矩阵字符处理一次，时间复杂度是 $O(n^2)$，保存输入和压缩结果需要 $O(n^2)$ 空间。

### 总结

压缩题的关键是始终从 `0` 的游程开始统计。先拼成一维字符串，再做游程编码，逻辑最清楚。
