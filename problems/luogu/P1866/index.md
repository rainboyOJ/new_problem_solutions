---
oj: "luogu"
problem_id: "P1866"
title: "编号"
description: "按编号上限升序处理，第 i 只兔子有 Mi-i 个尚未使用的可选编号，答案为这些选择数之积。"
difficulty: "普及-"
date: 2026-07-16 19:20
toc: true
tags: ["排序", "乘法原理", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1866
---

[[TOC]]

### 题意

第 `i` 只兔子要从 `1..Mi` 选择编号，所有编号互不相同。求编号方案数模 `1e9+7`。

### 思路

把上限从小到大排序。处理第 `used` 只兔子时，前面已经选出的 `used` 个编号都不超过当前上限，因此当前共有 `limit-used` 个可选编号。

根据乘法原理，把所有选择数相乘。若某一步 `limit-used<=0`，方案数就是零。

例如 `[5,8]` 的选择数依次是 `5` 和 `7`，答案 `35`。

### Python 知识

- `sorted` 返回升序上限列表。
- `enumerate(limits)` 同时给出已使用编号数和当前上限。
- `max(0,limit-used)` 把不可能状态变成乘积中的零。
- `math.prod` 直接计算生成器产生的所有选择数，最后统一取模。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：排序与顺序计数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：生成器乘积归约。

### 代码
@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

排序时间 $O(n\log n)$，乘积 $O(n)$，空间复杂度 $O(n)$。

### 总结

先处理限制最紧的对象后，已经占用的编号一定都在当前范围内，剩余选择数便可直接计算。
