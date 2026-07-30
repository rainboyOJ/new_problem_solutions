---
oj: "noi_openjudge"
problem_id: "ch0112-09"
title: "图像旋转翻转变换"
description: "按操作顺序用转置、切片和行逆序模拟图像旋转与翻转。"
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
source: http://noi.openjudge.cn/ch0112/09/
---

[[TOC]]

### 题意

对灰度矩阵依次执行顺时针旋转、逆时针旋转、左右翻转或上下翻转，输出最终图像。

### 思路

顺时针旋转可写为“先逆序行，再转置”：`zip(*image[::-1])`。逆时针旋转为先转置再逆序行。左右翻转是每行 `[::-1]`，上下翻转是行列表 `[::-1]`。操作必须按给定字符串顺序执行。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设操作数为 $q$，时间复杂度为 $O(qmn)$，空间复杂度为 $O(mn)$。

### 总结

矩阵变换的关键是每一步都使用当前矩阵，旋转后行列数会交换。
