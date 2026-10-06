---
oj: "roj"
problem_id: "3546"
title: "Jam的计数法"
description: "把 Jam 数字看作升序字母组合：从右找第一个未到上界的位加 1，其后各位重置为最小连续字母，即得字典序后继，单次 O(w)。"
difficulty: "入门"
date: 2026-10-02 06:54
updated: 2026-10-06 13:42
toc: true
tags: ["模拟", "构造", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3546
---

[[TOC]]

## 题目描述
Jam 用小写英文字母计数。一个 **Jam 数字**是 $w$ 个互不相同、从左到右严格递增的小写字母组成的串，字母只能取序号区间 $[s, t]$ 内的字母（$1 \leqslant s < t \leqslant 26$，$w \leqslant 10$，输入保证合法）。所有 Jam 数字按字典序从小到大排列。**输入**：第 1 行三个整数 $s\ t\ w$；第 2 行一个 Jam 数字。**输出**：紧接其后的至多 $5$ 个 Jam 数字，每行一个；不足 $5$ 个时有几个输出几个。

**输入样例**：第 1 行 `2 10 5`，第 2 行 `bdfij`。

**输出样例**：`bdghi`、`bdghj`、`bdgij`、`bdhij`、`befgh`。

## 思路
Jam 数字全体就是「从 $[s,t]$ 里选 $w$ 个字母的升序组合」按字典序的排列，求后继等同于“组合加一”：从右往左找第一个未到上界的位（最右位上界是第 $t$ 号字母，其余位上界是右邻位的前一个字母），该位加 1，右边各位重置为紧随其后的最小连续字母。全部顶界说明已是最大数字，停止输出；最多求 5 次，单次 $O(w)$。

## 参考代码

@include-code(./main.cpp, cpp)
