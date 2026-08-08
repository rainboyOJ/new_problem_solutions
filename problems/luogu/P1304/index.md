---
oj: "luogu"
problem_id: "P1304"
title: "哥德巴赫猜想"
description: "先用埃氏筛预处理质数表，再对每个偶数从小到大枚举第一个质数加数。"
difficulty: "普及-"
date: 2026-07-15 21:15
toc: true
tags: ["数学", "质数", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1304
---

[[TOC]]

### 题意

输入偶数 `N`，对 `4,6,8,...,N` 中的每个偶数，输出它写成两个质数之和的一种方案。若有多种方案，要求第一个加数最小。

### 思路

先用埃氏筛预处理 `0..N` 的质数表 `is_prime`。

对每个偶数 `even`，从小到大枚举第一个加数 `first`，令：

```text
second = even - first
```

如果 `first` 和 `second` 都是质数，就输出这一组并停止枚举。因为 `first` 是从小到大枚举的，所以第一次找到的方案就是第一个加数最小的方案。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：用 `range(4, n+1, 2)` 可以按步长枚举偶数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：质数相关判断适合用整数运算。
- 列表 `is_prime[x]` 可以作为快速查询表。
- f-string `f"{even}={first}+{second}"` 适合按题目格式输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

埃氏筛复杂度约为 $O(N \log\log N)$。之后对每个偶数枚举加数，最坏 $O(N^2)$，但 `N <= 10000` 可以通过。空间复杂度是 $O(N)$。

### 总结

需要反复判断质数时，先预处理质数表。要求“第一个加数最小”时，从小到大枚举并在第一次成功时停止。
