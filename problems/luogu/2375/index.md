---
oj: "luogu"
problem_id: "P2375"
title: "[NOI2014] 动物园"
description: "KMP 统计 border 链长度，再用第二遍线性扫描限制前后缀不能重叠。"
difficulty: "提高+/省选-"
date: 2026-07-16 19:57
toc: true
tags: ["KMP", "border", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2375
---

[[TOC]]

### 题意

对每个前缀，统计同时是前缀和后缀且两份不重叠的非空字符串数量 `num[i]`，求所有 `num[i]+1` 的乘积。

### 思路

第一遍 KMP 求 `prefix`，并递推 `border_count[length] = border_count[j] + 1`，它表示当前前缀的 border 链节点数（连当前前缀本身一起计数）。

第二遍再次扫描字符串，维护当前最长 border `j`。若 `2*j > length`，前后两份发生重叠，就继续沿 `prefix[j]` 回退。留下的 `j` 是最长不重叠 border，而它及其 border 链都合法，所以因子为 `border_count[j] + 1`。

不能对每个位置从 `prefix[length]` 重新向下找，否则全相同字符串会退化为平方复杂度；第二遍延续 `j` 才能保持线性。

### Python 知识

- `sys.stdin.buffer.readline` 逐测试串读取，不会同时保留最多五个百万字符数组。
- `array("i")` 控制 `prefix` 和计数数组的内存。
- Python 整数乘法后立即 `% MOD`，无需考虑溢出。

### 代码

@include-code(./main.py, python)

### 复杂度

每组时间 $O(|S|)$，空间 $O(|S|)$。

### 总结

本题的关键是把“数量”转成 border 链长度，再让非重叠限制通过 `2*j <= length` 落到同一条链上。
