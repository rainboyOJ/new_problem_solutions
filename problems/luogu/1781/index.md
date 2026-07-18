---
oj: "luogu"
problem_id: "P1781"
title: "宇宙总统"
description: "把票数当字符串比较，先比长度，长度相同再按字典序比较大小。"
difficulty: "入门"
date: 2026-07-15 22:18
toc: true
tags: ["高精度", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1781
---

[[TOC]]

### 题意

有 `n` 个候选人，每人的票数可能长达 100 位。输出票数最大的候选人编号和票数。

### 思路

票数很大，可以把它当字符串比较：

1. 位数更多的票数一定更大；
2. 位数相同，按字符串字典序比较即可。

扫描所有候选人，维护当前最大票数字符串和编号。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：长数字可以先作为字符串读取。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 也能用大整数，但字符串比较能直接体现高精度比较规则。
- `len(votes)` 比较位数。
- 字符串长度相同且只含数字时，字典序与数值大小一致。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

精简写法：

@include-code(./main-pythonic.py, python)

### 复杂度

候选人数最多 20，票数字符串长度最多 100。时间复杂度 $O(nL)$，空间复杂度 $O(L)$。

### 总结

高精度比较不一定要转成整数。对于非负整数字符串，先比长度，再比字典序，就是手写高精度比较的核心。
