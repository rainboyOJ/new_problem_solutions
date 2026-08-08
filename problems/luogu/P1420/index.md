---
oj: "luogu"
problem_id: "P1420"
title: "最长连号"
description: "顺序扫描数组，相邻两项差为 1 时延长当前段，否则从当前位置重新计数。"
difficulty: "入门"
date: 2026-06-18 23:11
toc: true
tags: ["模拟", "枚举", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1420
---

[[TOC]]

### 题意

给定长度为 `n` 的整数序列，求原序列中最长的一段“连号”的长度。

这里的连号要求相邻位置满足：

```text
a[i] = a[i-1] + 1
```

注意不是排序后找连续值，而是在原序列中看连续位置。

### 思路

顺着数组扫一遍，维护两个变量：

- `current`：以当前位置结尾的连号长度；
- `best`：目前见过的最长连号长度。

从第二个数开始，如果当前数正好等于前一个数加一，说明这一段还能延长，`current += 1`。

否则连号断开，只能从当前位置重新开始，令 `current = 1`。

每处理一个位置，都用 `best = max(best, current)` 更新答案。

旧目录中保留了 C++ 朴素枚举版本；Python 教学版聚焦一次扫描和列表下标，不新增 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `n = int(input())` 和 `list(map(int, input().split()))` 读取数组。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：`range(1, n)` 会枚举下标 `1` 到 `n-1`，适合访问前一个元素。
- `numbers[i - 1]` 表示当前位置的前一个数。
- `best = max(best, current)` 是维护最大值的常见写法。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

条件表达式扫描：

@include-code(./main-pythonic.py, python)

### 复杂度

只扫描数组一次，时间复杂度是 $O(n)$；存储输入数组需要 $O(n)$ 空间。

### 总结

这题的关键是看“相邻位置”是否连续。只要当前段长度和历史最大值维护正确，一次扫描就能得到答案。
