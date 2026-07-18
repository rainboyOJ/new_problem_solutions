---
oj: "luogu"
problem_id: "P1803"
title: "凌乱的yyy / 线段覆盖"
description: "按比赛结束时间升序排序，每次选择当前能参加且结束最早的比赛。"
difficulty: "普及-"
date: 2026-06-22 21:07
toc: true
tags: ["贪心", "排序", "区间贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1803
---

[[TOC]]

### 题意

给定若干比赛的开始时间和结束时间。参加一个比赛必须完整参加，不能同时参加两个比赛。问最多能参加几个比赛。

### 思路

经典区间调度贪心：按结束时间从早到晚排序。

扫描排序后的比赛，如果当前比赛的开始时间不早于上一个已选比赛的结束时间，就选择它。

为什么这样对？结束越早，留给后面比赛的时间越多。若某个最优方案当前选了一个结束更晚的可选比赛，可以把它替换成结束更早的比赛，不会减少后续可选空间。

### Python 知识

- 把区间保存成 `(end, start)`，直接 `sort()` 就按结束时间升序排列。
- `sys.stdin.buffer.read().split()` 适合 `n` 最大到 `10^6` 的大量整数输入。
- 扫描时只维护 `last_end` 和答案数量，不需要保存选择列表。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

排序时间复杂度为 $O(n\log n)$，扫描为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

区间覆盖/区间调度中，“最多选不相交区间”通常优先考虑按右端点排序的贪心。
