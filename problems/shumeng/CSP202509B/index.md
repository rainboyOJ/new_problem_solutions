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
difficulty: "未知"
---

[[TOC]]

### 题意

给定灰度图和阈值 `k`，灰度不小于 `k` 的像素为白色。求所有能在某个 `5x9` 子矩阵中呈现指定 CSP 图案的阈值 `k`。

### 思路

对一个固定窗口，图案中的白色位置必须满足 `A>=k`，黑色位置必须满足 `A<k`。因此该窗口允许的阈值是

```text
max(黑色位置灰度)+1 <= k <= min(白色位置灰度)
```

枚举所有窗口并把这些整数区间加入差分数组，最后扫描 `0..L-1` 输出覆盖次数大于零的阈值。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

窗口数量为 `O(n^2)`，每个窗口检查固定的 `45` 个格子；总时间复杂度 `O(n^2)`，空间复杂度 `O(n^2+L)`。

### 总结

阈值对一个窗口形成连续整数区间，先求区间再统一差分，比逐阈值检查每个窗口更直接。
