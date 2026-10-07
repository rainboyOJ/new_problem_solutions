---
oj: "luogu"
problem_id: "P4924"
title: "[1007] 魔法少女小Scarlet"
description: "每次复制待旋转子矩阵，根据顺/逆时针旋转公式生成新子矩阵后写回原矩阵。"
difficulty: "普及-"
date: 2026-07-15 21:35
updated: 2026-10-06 07:45
toc: true
tags: ["矩阵", "模拟", "python"]
categories: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0108-11"
    reason: "B 复用 A 的顺时针旋转行列对应步骤，把整图旋转换成奇数阶子矩阵按同一坐标映射旋转并复制写回"
  - oj: "noi_openjudge"
    problem_id: "ch0108-13"
    reason: "B 的子矩阵旋转复用 A 教的『变换不能原地读写、先复制原数据生成新矩阵再写回』纪律，再叠加顺逆时针 90 度的下标映射"
  - oj: "roj"
    problem_id: "1127"
    reason: "B 的顺时针分支直接复用 A 教过的坐标映射 new[row][col]=old[size-1-col][row]，只是把它从整图一次旋转改造成子矩阵内、可反复调用的原地旋转"
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

@include-code(./main.cpp, cpp)


### 复杂度

每次旋转边长为 `2r+1` 的子矩阵，时间复杂度是 $O(r^2)$。总空间除原矩阵外，需要一个子矩阵副本。

### 总结

矩阵旋转题先复制原子矩阵，再按坐标公式生成新矩阵。这样最不容易被原地覆盖问题干扰。
