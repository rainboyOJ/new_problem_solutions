---
oj: "luogu"
problem_id: "P5703"
title: "【深基2.例5】苹果采购"
description: "读入每人苹果数和人数，直接相乘得到采购总数。"
difficulty: "入门"
date: 2026-07-15 17:50
toc: true
tags: ["python", "入门", "输入输出", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5703
---

[[TOC]]

### 题意

每名同学分到同样数量的苹果。输入每人分到的苹果数和同学人数，输出一共需要采购多少个苹果。

### 思路

如果每人拿 `a` 个苹果，有 `b` 名同学，那么总数就是 `a * b`。题目保证答案在整数范围内，Python 直接乘法即可。

`brute.py` 不适合这题，因为没有隐藏的枚举过程；直接公式就是完整解法。

### Python 知识

- `input().split()` 读取一行并切成两个字符串。
- `map(int, ...)` 把两个字符串转换成整数。
- `a, b = ...` 是解包赋值，要求右侧正好产生两个值。
- `print(a * b)` 输出表达式结果。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：一行读取多个整数和解包。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：固定数量整数的输入模板。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

只做一次乘法，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

遇到“每份数量 × 份数”的题目，先把变量含义写清楚，再直接使用乘法。Python 代码可以和数学式保持一致。
