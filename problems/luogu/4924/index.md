---
oj: "luogu"
problem_id: "P4924"
title: "[1007] 魔法少女小Scarlet"
description: "每次复制待旋转子矩阵，根据顺/逆时针旋转公式生成新子矩阵后写回原矩阵。"
difficulty: "普及-"
date: 2026-07-15 21:35
toc: true
tags: ["矩阵", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4924
---

[[TOC]]

### 题意

初始有一个 `n*n` 矩阵，按行填入 `1..n^2`。接下来多次把某个奇数阶子矩阵顺时针或逆时针旋转 90 度，输出最终矩阵。

### 思路

旋转时不能一边读原矩阵一边写回原位置，否则后面的格子会读到已经被覆盖的新值。稳妥做法是：

1. 先复制出要旋转的子矩阵 `block`；
2. 根据旋转方向生成 `rotated`；
3. 再把 `rotated` 写回原矩阵。

对于边长为 `size` 的子矩阵：

- 顺时针：`new[row][col] = old[size-1-col][row]`
- 逆时针：`new[row][col] = old[col][size-1-row]`

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：二维矩阵可用列表嵌套列表保存。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：二维列表应逐行创建，避免多行引用同一个列表。
- `row[left:left+size]` 可以复制一段连续列。
- 切片赋值 `grid[top+row][left:left+size] = rotated[row]` 可以整段写回。

### 代码

@include-code(./main.py, python)

### 复杂度

每次旋转边长为 `2r+1` 的子矩阵，时间复杂度是 $O(r^2)$。总空间除原矩阵外，需要一个子矩阵副本。

### 总结

矩阵旋转题先复制原子矩阵，再按坐标公式生成新矩阵。这样最不容易被原地覆盖问题干扰。
