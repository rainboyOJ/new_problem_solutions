---
oj: "luogu"
problem_id: "P1001"
title: "A+B Problem"
description: "读取两个整数，用 Python 的大整数直接相加输出。"
difficulty: "入门"
date: 2026-07-15 17:50
toc: true
tags: ["python", "入门", "输入输出"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1001
---

[[TOC]]

### 题意

输入两个整数 $a,b$，输出它们的和 $a+b$。数据范围包含负数，绝对值不超过 $10^9$。

### 思路

这题的计算只有一步：读入两个整数，相加后输出。算法上没有优化空间，重点是把输入中的字符串转换为整数。

`brute.py` 不适合这题，因为朴素做法和最终做法完全相同；再写一个暴力版本只会重复代码。

### Python 知识

- `sys.stdin.read()` 可以一次读完整份输入。
- `split()` 会按空白字符切分，所以输入写成一行或多行都能得到两个 token。
- `map(int, ...)` 把字符串 token 转为整数。
- Python 的 `int` 是任意精度整数，本题范围内不需要担心溢出。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：一行多个整数、按 token 读取整份输入。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：固定数量整数的读入模板。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sum+map：

@include-code(./main-pythonic.py, python)


### 复杂度

只读取和处理两个整数，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

Python OJ 入门时先记住这条线：读入文本、切分 token、转换成整数、输出答案。本题就是这条线的最小版本。
