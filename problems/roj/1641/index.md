---
oj: "roj"
problem_id: "1641"
title: "「一本通 6.5 例 1」矩阵 A×B"
description: "按矩阵乘法定义实现 n×m 与 m×p 矩阵相乘，利用转置与列表推导式高效完成行向量与列向量的点积计算。"
difficulty: "入门"
date: 2026-09-30 23:31
updated: 2026-09-30 23:36
toc: true
tags:
  - 矩阵
  - 模拟
favorite: false
favorite_reason: ""
categories:
  - 线性代数
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1641
---

[[TOC]]

## 形式化题目

给定一个规模为 $n \times m$ 的整数矩阵 $A$ 和一个规模为 $m \times p$ 的整数矩阵 $B$。
求矩阵乘积 $C = A \times B$。根据定义，$C$ 的规模为 $n \times p$，其第 $i$ 行第 $j$ 列元素定义为：

$$c_{ij} = \sum_{k=1}^m a_{ik} b_{kj}$$

## 正解

### 思路

根据矩阵乘法的数学定义，结果矩阵 $C$ 中位于位置 $(i, j)$ 的元素，是矩阵 $A$ 的第 $i$ 个行向量与矩阵 $B$ 的第 $j$ 个列向量的点积。

矩阵乘法图示如下：

```
矩阵 A (第 i 行)                矩阵 B (第 j 列)             矩阵 C (第 i 行第 j 列)
[ a_{i1}, a_{i2}, ..., a_{im} ]  *  [ b_{1j} ]            =   c_{ij} = ∑_{k=1}^m a_{ik} b_{kj}
                                   [ b_{2j} ]
                                   [  ...   ]
                                   [ b_{mj} ]
```

以样例为例：
$A = \begin{bmatrix} 1 & 2 & 3 \\ 3 & 2 & 1 \end{bmatrix}$，$B = \begin{bmatrix} 1 & 1 \\ 2 & 2 \\ 3 & 3 \end{bmatrix}$。
- 计算 $c_{11}$：取 $A$ 第 $1$ 行 $[1, 2, 3]$ 与 $B$ 第 $1$ 列 $[1, 2, 3]^\top$ 点积，$1 \times 1 + 2 \times 2 + 3 \times 3 = 14$。
- 计算 $c_{12}$：取 $A$ 第 $1$ 行 $[1, 2, 3]$ 与 $B$ 第 $2$ 列 $[1, 2, 3]^\top$ 点积，$1 \times 1 + 2 \times 2 + 3 \times 3 = 14$。
- 计算 $c_{21}$：取 $A$ 第 $2$ 行 $[3, 2, 1]$ 与 $B$ 第 $1$ 列 $[1, 2, 3]^\top$ 点积，$3 \times 1 + 2 \times 2 + 1 \times 3 = 10$。
- 计算 $c_{22}$：取 $A$ 第 $2$ 行 $[3, 2, 1]$ 与 $B$ 第 $2$ 列 $[1, 2, 3]^\top$ 点积，$3 \times 1 + 2 \times 2 + 1 \times 3 = 10$。

在实现时，二维列表按行存储，访问 $B$ 的某一行很方便，但逐列访问 $B$（即 `b[k][j]`）会存在跨行索引。因此在 Python 中，我们可以先预先对矩阵 $B$ 进行转置，得到 $p \times m$ 的列表 `b_cols`，使得每个元素 `b_cols[j]` 直接表示矩阵 $B$ 的第 $j$ 列向量。之后利用列表推导式配合 `sum()`，直观、高效地完成每一行与每一列的点积计算。

此外注意数值范围：$a_{ik}, b_{kj} \in [-10^4, 10^4]$，项数 $m \leqslant 100$，最大和可能达到约 $100 \times 10^4 \times 10^4 = 10^{10}$，在 C++ 等静态语言中需要使用 64 位整型（`long long`），Python 自带大整数精度支持，计算天然安全。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n \cdot m \cdot p)$。转置矩阵 $B$ 耗时 $O(m \cdot p)$，计算结果矩阵 $C$ 的 $n \cdot p$ 个元素，每个元素需要累加 $m$ 项乘积，总运算次数不超过 $100 \times 100 \times 100 = 10^6$，在时限内瞬间完成。
- 空间复杂度：$O(n \cdot m + m \cdot p + n \cdot p)$。用于存储输入矩阵 $A$、$B$ 以及转置列向量与输出矩阵 $C$。

## 总结

矩阵乘法是线性代数最基础的操作，其核心在于行向量与列向量的点积。通过对右矩阵进行预转置，不仅符合点积计算的数学语义，还能让内存访问连续，配合 Python 的列表推导式能写出简洁优美且高效的代码。
