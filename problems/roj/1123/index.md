---
oj: "roj"
problem_id: "1123"
title: "图像相似度"
description: "把两幅 01 图像展开成一维序列，线性统计对应位置像素相等的个数，再按百分比输出。"
difficulty: "入门"
date: 2026-09-29 19:49
updated: 2026-10-04 10:21
toc: true
tags: [python, 模拟, 输入输出, 数组]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1123
---

[[TOC]]

## 形式化题目

给定两个大小同为 $m \times n$ 的 $01$ 矩阵 $A$、$B$，求

$$
\frac{\sum_{i=1}^{m}\sum_{j=1}^{n} [A_{i,j} = B_{i,j}]}{m \cdot n} \times 100\%
$$

的值，保留两位小数。

## 正解

### 思路

题目已经把“相似度”定义得非常清楚：统计两个矩阵在相同位置像素值相等的个数，再除以总像素数并转成百分比。因此不需要任何复杂算法，只需把所有像素按顺序读入，逐位比较一次即可。

具体实现时，可以先把输入中的全部整数读成一个序列。前两个数是 $m$、$n$，接下来的 $m \cdot n$ 个数是第一幅图像，再接下来的 $m \cdot n$ 个数是第二幅图像。用切片把两幅图像分开后，用 `zip` 同步遍历并统计相等位置的数量。

### 代码

@include-code(./main.py, python)

### 复杂度

设总像素数为 $T = m \cdot n$。

- 时间复杂度：$O(T)$，只需一次线性扫描。
- 空间复杂度：$O(T)$，保存两幅图像的像素序列。

本题 $T \leqslant 10^4$，完全在限制范围内。

## 总结

图像相似度是一道直接的统计题：把两幅图像的对应位置逐一比较，计数相等像素并输出百分比。实现上借助 Python 的切片和 `zip` 可以写得很短，核心只有读入、切片、统计、输出四步。
