---
oj: "luogu"
problem_id: "P3870"
title: "[TJOI2009] 开关"
description: "用翻转懒标记维护区间开关状态和区间亮灯数量。"
difficulty: "普及/提高-"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "懒标记", "区间翻转", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3870
---

[[TOC]]

### 题意

初始所有开关关闭，支持区间取反和查询区间内打开的开关数。

### 思路

节点只需保存区间内 `1` 的个数。翻转长度为 `length` 的节点时，新的数量是 `length - count`；两个翻转标记叠加等于没有翻转，因此懒标记用异或维护。

### Python 知识

- `bytearray` 适合保存只有 `0/1` 的懒标记。
- `tree[node] = length - tree[node]` 直接完成整段取反。
- 把所有答案放进列表，最后一次 `"\\n".join` 输出，减少频繁刷新。

### 代码

@include-code(./main.py, python)

原有 C++ 代码仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

建树隐含为全零，单次修改或查询 `O(log n)`，空间 `O(n)`。

### 总结

“翻转两次抵消”是布尔懒标记最典型的合并规则。
