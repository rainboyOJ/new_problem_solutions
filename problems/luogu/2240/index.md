---
oj: "luogu"
problem_id: "P2240"
title: "【深基12.例1】部分背包问题"
description: "金币可以分割，所以按单位价值从高到低贪心装入，最后一堆可只取一部分。"
difficulty: "入门"
date: 2026-07-15 22:30
toc: true
tags: ["贪心", "排序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2240
---

[[TOC]]

### 题意

有若干堆金币，每堆有重量和价值。金币可以任意分割，背包容量为 `T`，求最多能拿走多少价值。

### 思路

因为金币可以分割，所以这是部分背包。

每堆金币只需要看单位价值：

```text
value / weight
```

按单位价值从高到低排序，能整堆拿就整堆拿，装不下时拿剩余容量对应的一部分，然后结束。

### Python 知识

- `items.append((value / weight, weight, value))` 把排序关键字放在元组第一项。
- `items.sort(reverse=True)` 按单位价值降序排列。
- `print(f"{answer:.2f}")` 输出两位小数。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

排序时间复杂度为 $O(N\log N)$，扫描为 $O(N)$，空间复杂度为 $O(N)$。

### 总结

部分背包和 0/1 背包不同：能拆分时，单位价值最高的先拿一定不亏。
