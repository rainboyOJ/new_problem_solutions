---
oj: "luogu"
problem_id: "P1271"
title: "【深基9.例1】选举学生会"
description: "候选人编号范围很小，用计数数组统计每个编号票数，再按编号升序展开输出。"
difficulty: "入门"
date: 2026-07-15 22:10
toc: true
tags: ["排序", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1271
---

[[TOC]]

### 题意

给出 `m` 张选票，每张票是 `1..n` 之间的候选人编号。要求把所有选票编号从小到大输出。

### 思路

虽然票数最多有 `2,000,000`，但候选人编号最多只有 `999`。可以使用计数排序：

1. `count[x]` 记录编号 `x` 出现次数；
2. 从 `1` 到 `n` 枚举候选人编号；
3. 每个编号输出 `count[x]` 次。

这比直接排序更能体现“值域小”的优势。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：计数数组适合值域较小的频率统计。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量输入用 `sys.stdin.buffer.read()` 更稳。
- `answer.extend([str(candidate)] * count[candidate])` 批量追加重复编号。
- `"\n".join(...)` 或 `" ".join(...)` 适合集中输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

统计 `m` 张票，展开 `m` 个结果，时间复杂度是 $O(n+m)$，空间复杂度是 $O(n+m)$。

### 总结

当待排序元素值域很小、数量很大时，计数排序比比较排序更直接。
