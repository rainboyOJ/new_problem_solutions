---
oj: "luogu"
problem_id: "P3143"
title: "[USACO16OPEN] Diamond Collector S"
description: "排序后用双指针求每个起点的最长合法区间，再用后缀最优组合两个不相交展示柜。"
difficulty: "普及/提高-"
date: 2026-07-16 18:25
toc: true
tags: ["双指针", "后缀最值", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3143
---

[[TOC]]

### 题意

把尽量多的钻石放进两个展示柜，每柜内部最大尺寸差不超过 $K$。

### 思路

排序后，一个柜中的最优选择一定是连续区间。双指针求出每个左端 `i` 能延伸到的最远 `right[i]`。`best_suffix[p]` 保存从位置 `p` 开始可选的最长合法区间，枚举第一柜后把第二柜接在 `right[i]+1` 之后即可保证不重叠。

### Python 知识

- `diamonds = sorted(data)` 直接消费剩余整数迭代器。
- 右指针只前进不后退，总计线性移动。
- 逆序循环一行维护后缀最大长度。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

### 总结

两个不相交区间的组合常用“枚举第一段 + 后缀最优第二段”。
