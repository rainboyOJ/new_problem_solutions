---
oj: "shumeng"
problem_id: "CSP202509B"
title: "水印检查"
description: "把每个 5x9 窗口转成阈值区间，用差分数组合并所有能呈现 CSP 水印的阈值。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["枚举", "差分", "二维数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202509B
---

[[TOC]]

## 形式化题目

给定 $n \times n$ 灰度图，灰度值在 $[0, L-1]$。对阈值 $k$，灰度 $\ge k$ 的像素视为白色，否则黑色。求所有能在一个 $5 \times 9$ 子矩阵中呈现固定 CSP 图案的阈值 $k$，从小到大输出。

## 思路

先看最直接的做法：对每个阈值、每个窗口逐一比对。

@include-code(./brute.cpp, cpp)

### 关键观察：阈值形成连续区间

固定一个 $5 \times 9$ 窗口，图案中的白色位置必须满足 $A \ge k$，黑色位置必须满足 $A < k$。因此该窗口能呈现水印的阈值是一个整数区间：

$$
\max(\text{黑色位置灰度}) + 1 \le k \le \min(\text{白色位置灰度})
$$

### 差分合并

每个窗口只贡献一个区间。枚举所有窗口，用差分数组合并这些区间，最后扫描 $0..L-1$ 输出覆盖次数大于 0 的阈值即可。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

窗口数为 $O(n^2)$，每个窗口检查固定 45 个格子，总时间复杂度 $O(n^2)$，空间复杂度 $O(n^2 + L)$。

## 总结

阈值对固定窗口形成一个连续区间，先求区间再统一差分，比逐阈值检查每个窗口快得多。本题也可以先对所有窗口收集区间，再用扫描线求并，差分是最简单的实现。