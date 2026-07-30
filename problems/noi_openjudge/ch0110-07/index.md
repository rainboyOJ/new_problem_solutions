---
oj: "noi_openjudge"
problem_id: "ch0110-07"
title: "合影效果"
description: "按性别分组后将男生升序、女生降序排列并固定输出两位小数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0110/07/
---

[[TOC]]

### 题意

从拍照者视角，男生全部站在左侧并按身高从矮到高排列，女生站在右侧并按身高从高到矮排列。所有身高输出两位小数。

### 思路

读入时按性别分到 `boys` 和 `girls` 两个列表。男生升序、女生降序后直接拼接。格式化字符串 `f"{height:.2f}"` 保证每个身高恰好两位小数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

### 总结

分组的先后顺序是输出结构的一部分，两个组内部再各自排序即可。
