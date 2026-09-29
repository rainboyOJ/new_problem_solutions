---
oj: "roj"
problem_id: "1127"
title: "图像旋转"
description: "顺时针旋转矩阵 90°：新矩阵的第 i 行是原矩阵第 i 列从下到上读取。"
difficulty: "入门"
date: 2026-09-29 20:02
updated: 2026-09-29 20:03
toc: true
tags: ["矩阵", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1127
---

[[TOC]]

## 形式化题目

给定 $n \times m$ 整数矩阵 $A$，构造 $m \times n$ 矩阵 $B$，使得

$$
B_{i,j} = A_{n-1-j,\, i}
$$

输出矩阵 $B$。

## 正解

### 思路

顺时针旋转 $90^\circ$ 的几何意义是：新矩阵的每一行，对应原矩阵的同一列，并且方向由“从上往下”变成“从下往上”。因此若原矩阵为 $a_{r,c}$，则新矩阵为 $b_{i,j} = a_{n-1-j,\, i}$。

用样例验证这个映射方向。原矩阵：

$$
\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9
\end{bmatrix}
$$

新矩阵第一行应是原矩阵第一列从下到上：$7, 4, 1$；第二行是第二列从下到上：$8, 5, 2$；第三行是第三列从下到上：$9, 6, 3$。与样例输出一致。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n \cdot m)$，每个像素只被读取和输出一次。
- 空间复杂度：$O(n \cdot m)$，保存原矩阵与输出字符串。

## 总结

本题直接利用顺时针 $90^\circ$ 旋转的坐标映射 $b_{i,j} = a_{n-1-j,\, i}$ 即可，实现时只需注意新矩阵的行数变列数、列数变行数。
