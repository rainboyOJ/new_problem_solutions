---
oj: "shumeng"
problem_id: "CSP202406A"
title: "矩阵重塑（其一）"
description: "把矩阵按行优先展平成一维序列，再按新矩阵的列数重新解释每个元素的位置。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "矩阵"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202406A
---

[[TOC]]

## 形式化题目

给定一个 $n \times m$ 矩阵与目标形状 $p \times q$，满足 $n \times m = p \times q$。

按行优先顺序读取原矩阵的元素，再按行优先顺序填入 $p \times q$ 新矩阵并输出。

## 思路

行优先重塑不会改变元素在一维线性序列中的顺序，本质是“换一种方式解释同一串数据”。

### 保存线性序列

按行优先依次读入全部 $n \times m$ 个元素，存入一维数组 `value`。

### 用新列数定位

新矩阵第 $i$ 行第 $j$ 列的元素，正是线性序列中的第 $i \times q + j$ 个，直接输出 `value[i * q + j]` 即可。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：每个元素读取与输出一次，时间复杂度 $O(nm)$。
- 空间：保存整个线性序列，空间复杂度 $O(nm)$。

## 总结

矩阵重塑只改变二维下标，不改变行优先线性顺序。先固定线性序号，再用新列数 $q$ 计算行列下标，就能在一维数组上直接完成重塑。