---
oj: "luogu"
problem_id: "P2004"
title: "领地选择"
description: "构造二维前缀和，O(1) 计算每个 C×C 正方形价值并按行列顺序寻找唯一最优位置。"
difficulty: "普及/提高-"
date: 2026-07-16 17:48
toc: true
tags: ["二维前缀和", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2004
---

[[TOC]]

### 题意

在 $N\times M$ 矩阵中找到价值和最大的 $C\times C$ 正方形，输出左上角坐标。

### 思路

构造二维前缀和 `prefix[i][j]`。以 `(bottom, right)` 为右下角的正方形可用四个前缀值容斥得到。枚举所有右下角，遇到更大值时记录对应左上角。

### Python 知识

- 每读一行就维护 `row_sum`，无需先保存原矩阵。
- `array("q")` 用紧凑 64 位整数保存前缀表，显著小于 Python 整数列表。
- 多行整数用 `map(int, input().split())` 直接迭代，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(NM)$，空间复杂度 $O(NM)$。

### 总结

固定大小子矩形求和时，二维前缀和能让每个候选位置只做常数次运算。
