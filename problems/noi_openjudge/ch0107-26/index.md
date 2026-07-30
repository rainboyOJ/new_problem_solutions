---
oj: "noi_openjudge"
problem_id: "ch0107-26"
title: "字符串最大跨距"
description: "取 S1 最左出现和 S2 最右出现，检查不重叠后计算最大间隔。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "匹配", "贪心", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/26/
---

[[TOC]]

### 题意

求字符串 $S$ 中位于左侧且不交叉的 $S1$、$S2$ 的最大跨距。

### 思路

为了让间隔最大，左边的 $S1$ 应尽量靠左，右边的 $S2$ 应尽量靠右。因此取 `find(S1)` 和 `rfind(S2)`；若前者结尾不在后者起点左边，则无合法方案。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

字符串查找最坏时间复杂度为 $O(nm)$，额外空间复杂度为 $O(1)$。

### 总结

最大间隔由两端极值位置决定，不必枚举全部出现位置。
