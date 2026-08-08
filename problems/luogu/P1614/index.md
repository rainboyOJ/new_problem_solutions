---
oj: "luogu"
problem_id: "P1614"
title: "爱与愁的心痛"
description: "先求第一个长度为 m 的窗口和，再滑动窗口维护所有连续 m 项和的最小值。"
difficulty: "入门"
date: 2026-06-18 23:59
toc: true
tags: ["滑动窗口", "枚举", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1614
---

[[TOC]]

### 题意

给定长度为 `n` 的正整数序列，求所有长度恰好为 `m` 的连续子段中，子段和的最小值。

### 思路

朴素做法是枚举每个长度为 `m` 的区间，并重新求一次和。相邻两个固定长度窗口只差两个元素：

- 右边新进入一个元素；
- 左边旧移出一个元素。

所以可以维护当前窗口和 `window_sum`。窗口右移一格时：

```text
window_sum += 新进入的元素
window_sum -= 旧移出的元素
```

先计算第一个窗口 `values[:m]` 的和，再从下标 `m` 开始把窗口向右滑动，并维护最小值。

旧目录中保留了 C++ 朴素区间枚举版本；Python 教学版聚焦滑动窗口，不新增 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：本题后续 `n` 行每行一个整数，可以用列表推导式读取。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：切片 `values[:m]` 表示前 `m` 个元素。
- `sum(values[:m])` 求第一个窗口和。
- `answer = min(answer, window_sum)` 是维护最小值的常见写法。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

滑动窗口：

@include-code(./main-pythonic.py, python)


### 复杂度

每个元素最多进入和移出窗口一次，时间复杂度是 $O(n)$。存储序列需要 $O(n)$ 空间。

### 总结

固定长度连续段适合滑动窗口。不要反复重算整个区间和，利用“新进一个、旧出一个”的关系滚动更新。
