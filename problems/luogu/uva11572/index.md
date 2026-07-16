---
oj: "luogu"
problem_id: "UVA11572"
title: "唯一的雪花 Unique Snowflakes"
description: "用字典记录每种雪花最近位置，在线移动左端点求最长无重复连续段。"
difficulty: "普及/提高-"
date: 2026-07-16 18:25
toc: true
tags: ["滑动窗口", "哈希", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/UVA11572
---

[[TOC]]

### 题意

多组数据中，求最长的元素互不相同连续子段长度。

### 思路

`last[x]` 记录雪花 `x` 最近出现位置。扫描到位置 `right` 时，合法窗口左端至少是 `last[x]+1`，但不能向左退，所以更新 `left=max(left,last.get(x,-1)+1)`。

### Python 知识

- `dict.get(key, -1)` 统一处理第一次出现。
- 只保存最近位置，不需要保存窗口集合或原数组。
- 多组答案先转成字符串再一次换行输出。

### 代码

@include-code(./main.py, python)

### 复杂度

每组时间复杂度 $O(n)$，空间复杂度 $O(n)$。

### 总结

最长无重复子段的左边界由当前元素上一次出现位置直接决定。
