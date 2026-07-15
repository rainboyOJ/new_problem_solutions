---
oj: "luogu"
problem_id: "P1116"
title: "车厢重组"
description: "相邻交换把序列排成升序所需的最少次数，正好等于原序列中的逆序对数量。"
difficulty: "入门"
date: 2026-07-15 21:20
toc: true
tags: ["排序", "逆序对", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1116
---

[[TOC]]

### 题意

有一列车厢，每次操作只能交换相邻两节车厢。问最少交换多少次，才能把车厢编号排成从小到大。

### 思路

一次相邻交换最多只能消掉一对顺序错误的车厢。

如果 `cars[i] > cars[j]` 且 `i < j`，这两节车厢就是一对逆序对。最终升序排列时，较小的那节一定要越过较大的那节，所以每一对逆序对都至少需要一次相邻交换。

反过来，冒泡排序每交换一次相邻逆序元素，就恰好减少一个逆序对，直到逆序对数量变成 `0`。因此最少操作次数就是初始逆序对数量。

本题 `n <= 1000`，直接两层循环统计即可。

### Python 知识

- `sys.stdin.buffer.read().split()` 适合这种“全是整数，换行不重要”的输入。
- `list(map(int, ...))` 一次把所有 token 转成整数，后面按下标切出数组。
- 双层 `for` 循环直接枚举所有 `i < j` 的数对，写法和 C++ 中的两层循环一一对应。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度为 $O(n^2)$，空间复杂度为 $O(n)$。

### 总结

看到“只能相邻交换，问最少交换次数”，要立刻联想到逆序对。这里数据范围很小，不需要树状数组或归并排序。
