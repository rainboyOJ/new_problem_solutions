---
oj: "luogu"
problem_id: "P4653"
title: "[CEOI 2017] Sure Bet"
description: "分别降序排列两类收益，每次给当前总收益较小的一侧加入最大剩余灯泡以平衡最坏收益。"
difficulty: "普及+/提高"
date: 2026-07-16 18:25
toc: true
tags: ["贪心", "排序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4653
---

[[TOC]]

### 题意

可任选四灯泡，每选一个成本 1；最终只点亮 A 或 B 一类。最大化两种结果中较小的净收益。

### 思路

两类权值分别降序排列。当前较小总收益决定最坏情况，因此下一步若要改善最坏值，应从这一类取最大尚未选择权值。每加入一个灯泡后，用 `min(sumA,sumB)-chosen` 更新答案；空选择使答案至少为 0。

### Python 知识

- 把四位小数解析成乘 $10000$ 的整数，完全避免浮点比较与输出误差。
- `zip(*pairs)` 分离两类权值，随后各自降序排序。
- f-string `:04d` 固定输出四位小数。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

### 总结

目标由较弱一侧决定，贪心始终用该侧最大剩余收益补平衡。
