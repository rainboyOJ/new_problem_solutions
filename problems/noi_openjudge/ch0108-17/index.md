---
oj: "noi_openjudge"
problem_id: "ch0108-17"
title: "最好的草"
description: "从每个未访问的草格开始四连通 BFS 并标记，统计连通草丛数量。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["图论", "搜索", "矩阵", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/17/
---

[[TOC]]

### 题意

统计牧场中由公共边连通的 `#` 草格形成的草丛数量。

### 思路

扫描到未访问的 `#` 时，答案加一并从它出发做四方向 BFS，把同一连通块改为 `.`。之后再次扫描到的草格一定属于新草丛。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

每格至多入队一次，时间复杂度为 $O(rc)$，空间复杂度为 $O(rc)$。

### 总结

连通块计数的标准模式是“发现未访问点，搜索并标记整块”。
