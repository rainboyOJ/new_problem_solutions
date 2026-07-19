---
oj: "luogu"
problem_id: "P1228"
title: "地毯填补问题"
description: "递归把棋盘分成四个象限，在中心放一块 L 形地毯制造三个新的特殊格。"
difficulty: "普及/提高-"
date: 2026-07-15 22:30
toc: true
tags: ["递归", "分治", "构造", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1228
---

[[TOC]]

### 题意

给定一个 `2^k x 2^k` 棋盘，其中有一个特殊格不能覆盖。要求用 L 形地毯覆盖其余所有格子，并输出每块地毯的位置和形状。

### 思路

经典分治铺棋盘。

把当前棋盘分成四个象限。特殊格一定在其中一个象限。我们在棋盘中心放一块 L 形地毯，覆盖另外三个象限靠近中心的格子。这样做以后：

- 原来有特殊格的象限继续用原特殊格；
- 另外三个象限把刚刚被中心地毯覆盖的格子看作“特殊格”。

于是一个大问题变成四个规模减半的小问题。

### Python 知识

- 递归函数 `cover(top, left, size, special_x, special_y)` 用左上角和边长描述子棋盘。
- 输出行先放进 `answers`，最后用 `"\n".join(...)` 一次输出。
- `1 << k` 可以快速得到 `2^k`。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`

### 代码

@include-code(./main.py, python)


### 复杂度

每块地毯输出一次，地毯数量为 $(4^k-1)/3$。时间复杂度和输出规模同阶，空间复杂度主要是递归栈与输出列表。

### 总结

这题的关键是“中心补一块”，让四个子棋盘都变成同一种问题。
