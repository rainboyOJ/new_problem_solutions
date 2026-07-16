---
oj: "luogu"
problem_id: "P3017"
title: "[USACO11MAR] Brownie Slicing G"
description: "二分最小块权值，并用非负权值下的横向、纵向贪心判断能否切出 A×B 块。"
difficulty: "提高+/省选-"
date: 2026-07-16 17:48
toc: true
tags: ["二分答案", "贪心", "矩阵", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3017
---

[[TOC]]

### 题意

把非负矩阵先横切成 $A$ 条，每条再独立竖切成 $B$ 块，最大化所有 $A\times B$ 块中的最小权值。

### 思路

二分答案 `target`。从上到下累加各列权值；对当前行带从左到右贪心，只要累计值达到 `target` 就形成一块。若能形成至少 $B$ 块，就立即完成一条横带并清空列和。

矩阵元素非负，因此越早切完一块不会损害后续；越早完成横带也为剩余横带留下更多行。若能贪心完成至少 $A$ 条，`target` 可行。

### Python 知识

- `enumerate(row)` 让“按列累加”保持为一个直接循环。
- `sum(map(sum, grid))` 组合内置 `sum` 求全矩阵总和，给二分提供上界。
- 判断函数闭包直接读取网格和切块数量，参数只保留 `target`。

### 代码

@include-code(./main.py, python)

### 复杂度

设权值总和为 $S$，时间复杂度 $O(RC\log S)$，空间复杂度 $O(RC+C)$。

### 总结

“最大化最小值”给出二分方向，非负性则保证二维切割可以用两层贪心判定。
