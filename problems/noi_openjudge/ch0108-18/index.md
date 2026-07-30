---
oj: "noi_openjudge"
problem_id: "ch0108-18"
title: "肿瘤面积"
description: "从矩形肿瘤边框左上角测量零边框宽高，计算去掉边框后的内部面积。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/18/
---

[[TOC]]

### 题意

灰度图中肿瘤是零像素围成的矩形边框，求边框内部的像素数。

### 思路

最先扫描到的零是边框左上角。沿该行和该列数出边框宽高，内部尺寸分别减去两条边框，面积为 `(height - 2) * (width - 2)`。

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

扫描图像并测量边框，时间复杂度为 $O(n^2)$，矩阵空间为 $O(n^2)$。

### 总结

已知规则矩形边框时，测量宽高即可直接得到内部面积。
