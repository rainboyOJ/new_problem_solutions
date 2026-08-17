---
oj: "shumeng"
problem_id: "CSP201912B"
title: "回收站选址"
description: "用坐标集合判断四个正交邻居和四个对角邻居，按对角垃圾数计分。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "集合", "坐标"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201912B
---

[[TOC]]

## 形式化题目

平面上有 $n$ 个互不相同的整数坐标点（垃圾点）。一个点 $(x,y)$ 可作为回收站选址，当且仅当上下左右四个相邻位置 $(x\pm 1,y),\ (x,y\pm 1)$ 都有垃圾。此时它的得分等于四个对角位置 $(x\pm 1,y\pm 1)$ 中有垃圾的位置数。统计得分为 $0,1,2,3,4$ 的选址个数。

## 思路

### 朴素做法

对每个垃圾点都扫描全部坐标，线性检查它需要的八个邻居。时间复杂度 $O(n^2)$，作为对拍基准。

@include-code(./brute.cpp, cpp)

### 坐标集合查询

把所有坐标放入集合。每个候选点只做 8 次集合查询：先确认四个正交邻居，成立后统计四个对角邻居，得到分数并计数。坐标范围很大且可以为负，所以使用 `long long` 保存坐标。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：集合构建和每次查询为 $O(\log n)$，总时间复杂度 $O(n\log n)$。
- 空间：$O(n)$。

## 总结

小范围几何邻居判断不需要建网格。将实际出现的坐标存为集合后，平移八个固定方向逐一查询即可。