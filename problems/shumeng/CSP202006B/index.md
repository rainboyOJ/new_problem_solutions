---
oj: "shumeng"
problem_id: "CSP202006B"
title: "稀疏向量"
description: "利用两份递增稀疏坐标表的双指针，线性累加公共坐标的乘积。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["双指针", "模拟", "稀疏矩阵"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202006B
---

[[TOC]]

### 题意

给出两个 `n` 维向量的稀疏表示：每个非零项为 `(index,value)`，坐标严格递增。求两个向量的内积。

### 思路

只有两个向量在同一坐标的非零项才会为内积贡献乘积。由于两份坐标表都递增，可以像归并一样扫描。

保存第一个向量。顺序读入第二个向量的每项 `(index,value)` 时，移动第一个向量指针，跳过所有更小的坐标；若当前坐标相同，累加两个值的乘积。每个项最多被访问一次，不需要也不能开长度为 `n` 的数组。

小数据暴力解用 `map` 按坐标查询第一个向量的值。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个非零项至多扫描一次，时间复杂度为 $O(a+b)$，保存第一个向量的空间复杂度为 $O(a)$。

### 总结

稀疏表示的关键是只处理出现的坐标。两个有序稀疏表的公共坐标可以直接用双指针求出，完整维度 `n` 不影响算法复杂度。
