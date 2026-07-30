---
oj: "noi_openjudge"
problem_id: "ch0108-22"
title: "神奇的幻方"
description: "采用暹罗法在 2N-1 阶奇阶方阵中循环右上移动，冲突时向下填入幻方。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "构造", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/22/
---

[[TOC]]

### 题意

按给定规则构造阶数为 $2N-1$ 的奇阶幻方。

### 思路

从首行中点填入 $1$。每次默认尝试向右上循环移动；若目标已填数，则改为从当前格向下移动。取模实现穿越边界后的回绕。

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

方阵边长为 $s=2N-1$，时间和空间复杂度均为 $O(s^2)$。

### 总结

奇阶幻方构造的状态只包含当前位置和下一候选位置。
