---
oj: "roj"
problem_id: "1672"
title: "种玉米"
description: "通过一次遍历找出二维网格中所有整数的最大值与最小值，计算两者之差即为玉米杆高度差。"
difficulty: "入门"
date: 2026-10-01 01:23
updated: 2026-10-01 01:25
toc: true
tags:
  - "模拟"
  - "极值"
favorite: false
favorite_reason: ""
categories:
  - "基础题"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1672
---

[[TOC]]

## 形式化题目

给定一个大小为 $m \times n$ 的二维整数矩阵 $A$（$1 \leqslant m, n \leqslant 1000$），求矩阵中所有元素的最大值与最小值的差值，即：

$$\Delta = \max_{1 \leqslant i \leqslant m, 1 \leqslant j \leqslant n} A_{i, j} - \min_{1 \leqslant i \leqslant m, 1 \leqslant j \leqslant n} A_{i, j}$$

### 样例图解

以样例输入为例：

$$m = 2, n = 3$$

矩阵元素如下：

| 行 \ 列 | 第 1 列 | 第 2 列 | 第 3 列 |
| :---: | :---: | :---: | :---: |
| **第 1 行** | 2 | 4 | 9 |
| **第 2 行** | 3 | 7 | 8 |

所有数构成的多重集为 $\{2, 4, 9, 3, 7, 8\}$：
- 最大值为 $9$；
- 最小值为 $2$；
- 高度差为 $9 - 2 = 7$。

## 正解

### 思路

虽然题目背景将玉米杆排列成 $m$ 行 $n$ 列的方阵，但高度差只取决于整块地里的最高值和最低值，与玉米杆所在的具体行、列坐标完全无关。

因此，求解过程分为两步：
1. 将给定的 $m \times n$ 个整数统一读入；
2. 线性扫描所有数据，维护或直接求出最大值与最小值，计算两者的差值即为答案。

由于数据规模 $m \times n \leqslant 10^6$，在 Python 中可以使用 `sys.stdin.buffer.read().split()` 快速读取所有内容，再利用内置函数 `max()` 与 `min()` 在单次线性时间内完成求解。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$\mathcal{O}(m \times n)$。快速读取所有输入数据需要线性时间，转换为整数以及调用 `max()`、`min()` 也各需要遍历一次列表，总操作次数与数字总量 $m \times n$ 成线性比例，对于 $10^6$ 个数能在约 0.1 秒内完成。
- **空间复杂度**：$\mathcal{O}(m \times n)$。需要存储读入的所有数字列表，最大内存开销约为几十兆字节，满足 128MB 的内存限制。

## 总结

本题是求集合极值与极差（Range）的典型入门问题。关键点在于认清“网格结构对最终答案无约束”，从而将二维问题直接降维为一维数组或流式数据的单次极值统计。
