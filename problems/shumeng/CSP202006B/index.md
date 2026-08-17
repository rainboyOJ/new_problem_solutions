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

## 形式化题目

两个 $n$ 维整数向量用稀疏表示给出：每个非零项为 `(index, value)` 且坐标严格递增。求两个向量的内积

$$
\boldsymbol{u}\cdot\boldsymbol{v}=\sum_{i=1}^{n}\boldsymbol{u}_i\cdot\boldsymbol{v}_i。
$$

## 思路

只有两个向量在同一坐标都非零时，才会为内积贡献对应值的乘积。由于两份坐标表都严格递增，可以用双指针像归并一样扫描。

### 双指针扫描

1. 保存第一个向量的全部非零项；
2. 顺序读入第二个向量的每一项，不断后移第一个向量的指针，跳过所有坐标更小的项；
3. 若坐标相等，累加两个值的乘积。

每个非零项至多被访问一次，因此复杂度只与两个向量的非零项个数有关。因为 $n$ 最大可达 $10^9$，不能也无需开长度为 $n$ 的数组。

先看一个用 `map` 按坐标查询的朴素实现：

@include-code(./brute.cpp, cpp)

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

每个非零项至多扫描一次，时间复杂度为 $O(a+b)$，保存第一个向量的空间复杂度为 $O(a)$。

## 总结

稀疏表示的关键是只处理实际出现的坐标。两个有序稀疏表的公共坐标可以直接用双指针求出，完整维度 $n$ 不影响算法复杂度。