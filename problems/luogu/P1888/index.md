---
oj: "luogu"
problem_id: "P1888"
title: "三角函数"
description: "排序后三边中最短边除以最长边，再用 gcd 约分输出较小锐角正弦值。"
difficulty: "入门"
date: 2026-07-15 18:17
toc: true
tags: ["python", "入门", "数学", "排序", "最大公约数"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1888
---

[[TOC]]

### 题意

给出一组勾股数，输出较小锐角的正弦值，要求写成约分后的分数。

### 思路

直角三角形中最长边是斜边。较小锐角对应的对边是最短边，所以正弦值就是：

$$
\frac{\text{最短边}}{\text{最长边}}
$$

先把三条边排序，再用 `gcd` 求最大公约数约分。

这题已有旧 C++ 版本；本篇改成 Python 教学，重点是 `sorted` 和 `math.gcd`。`brute.py` 不单独写，因为排序后公式计算就是完整解法。

### Python 知识

- `sorted(map(int, input().split()))` 读入并排序三个整数。
- `from math import gcd` 可以直接使用最大公约数函数。
- f-string 可以拼出分数格式：`f"{a}/{b}"`。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sorted` 的用法。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：`gcd` 与整数工具。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：输入解析和字符串输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sorted + gcd：

@include-code(./main-pythonic.py, python)


### 复杂度

排序三个数可看作 $O(1)$，求最大公约数为 $O(\log V)$。空间复杂度 $O(1)$。

### 总结

先把边长顺序整理好，问题就变成“最短边 / 最长边”。Python 的 `gcd` 能直接完成约分。
