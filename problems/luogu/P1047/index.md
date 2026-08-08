---
oj: "luogu"
problem_id: "P1047"
title: "[NOIP 2005 普及组] 校门外的树"
description: "用差分数组记录每个删树区间的覆盖边界，再前缀扫描统计未被覆盖的位置。"
difficulty: "入门"
date: 2026-06-18 23:34
toc: true
tags: ["差分", "模拟", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1047
---

[[TOC]]

### 题意

数轴 `0..l` 的每个整数点都有一棵树。给出 `m` 个闭区间 `[u, v]`，这些区间内的树都要移走，包含端点。问最后还剩多少棵树。

### 思路

直接做法是开一个布尔数组，遇到区间就把区间内所有位置标记为删除。本题这样也能通过。

这里用差分写法来练习“区间修改，最后统一统计”：

- 在 `left` 位置让覆盖数加一；
- 在 `right + 1` 位置让覆盖数减一。

处理完所有区间后，从 `0` 到 `l` 做前缀和。当前覆盖数 `covered` 为 `0`，说明这个位置没有被任何删树区间覆盖，答案加一。

旧目录中保留了 C++ 直接标记版本；Python 教学版使用列表实现差分，不新增 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `map(int, input().split())` 读取每行两个整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：本题是第一行两个整数，后面 `m` 行区间的常见格式。
- `[0] * (length + 2)` 创建差分列表，多开一位用于 `right + 1`。
- `for _ in range(interval_count):` 表示只关心循环次数，不使用循环变量。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

差分数组：

@include-code(./main-pythonic.py, python)


### 复杂度

处理区间需要 $O(m)$，扫描所有树的位置需要 $O(l)$，总时间复杂度是 $O(l+m)$，空间复杂度是 $O(l)$。

### 总结

这题既能直接标记，也很适合作为差分入门：区间删除不必逐点处理，只改两个边界，最后统一前缀扫描。
