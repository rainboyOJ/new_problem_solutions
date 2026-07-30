---
oj: "noi_openjudge"
problem_id: "ch0108-19"
title: "肿瘤检测"
description: "统计灰度不超过 50 的肿瘤格，并以边界或四邻非肿瘤条件判断周长。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/19/
---

[[TOC]]

### 题意

灰度不超过 $50$ 的格属于肿瘤，求肿瘤面积和边界格数量。

### 思路

扫描每个肿瘤格累加面积。它位于图像边缘，或任一上下左右合法邻居不是肿瘤时，便是边界格，累加周长。

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

每格检查固定四邻居，时间复杂度为 $O(n^2)$，矩阵空间为 $O(n^2)$。

### 总结

区域边界判定的核心是检查相邻位置是否离开该区域或图像。
