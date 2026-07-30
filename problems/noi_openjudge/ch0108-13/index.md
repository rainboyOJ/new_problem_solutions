---
oj: "noi_openjudge"
problem_id: "ch0108-13"
title: "图像模糊处理"
description: "保留原图，使用中心与四邻域五个像素的四舍五入平均更新内部像素。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/13/
---

[[TOC]]

### 题意

模糊图像：边缘不变，内部像素取自身与上下左右原值的平均并四舍五入。

### 思路

新值必须全由原图计算，所以复制一份 `blurred` 保存结果。非负整数除以 $5$ 的四舍五入可写作 `(total + 2) // 5`。

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

时间和空间复杂度均为 $O(nm)$。

### 总结

邻域更新题不要原地写入，否则后续像素会读到本轮新值。
