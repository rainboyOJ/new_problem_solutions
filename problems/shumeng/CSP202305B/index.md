---
oj: "shumeng"
problem_id: "CSP202305B"
title: "矩阵运算"
description: "利用矩阵乘法结合律先计算 K^T V，再计算按行缩放后的 Q 与该小矩阵的乘积。"
difficulty: "普及+/提高"
date: 2026-07-31 16:21
toc: true
tags: ["线性代数", "矩阵乘法", "结合律"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202305B
---

[[TOC]]

### 题意

给定 $n\times d$ 的矩阵 $Q,K,V$ 和长度为 $n$ 的向量 $W$，求

$$\left(W\cdot(QK^T)\right)V,$$

其中 $W$ 按行缩放 $QK^T$，输出一个 $n\times d$ 矩阵。数据范围为 $n\le 10^4,d\le20$。

### 思路

先看直接按照题目公式枚举中间矩阵的做法：

@include-code(./brute.cpp, cpp)

直接计算 $QK^T$ 需要 $O(n^2d)$，$n=10^4$ 时不可行。利用矩阵乘法结合律：

$$\left(W\cdot(QK^T)\right)V=(W\cdot Q)(K^TV)。$$

因此先计算只有 $d\times d$ 大小的矩阵 $B=K^TV$：

$$B_{i,j}=\sum_{r=1}^{n}K_{r,i}V_{r,j}。$$

对于答案第 $r$ 行，先将 $Q_{r,i}$ 乘以 $W_r$，再与 $B$ 相乘：

$$A_{r,j}=\sum_{i=1}^{d}W_rQ_{r,i}B_{i,j}。$$

实现时使用 `long long`。中间和最终结果的数量级都可能远大于 `int`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

计算 $K^TV$ 和最终结果都需要 $O(nd^2)$ 时间，存储三个输入矩阵和中间矩阵需要 $O(nd+d^2)$ 空间。

### 总结

矩阵乘法不满足交换律，但满足结合律。面对形如 $ABC$ 的乘积，应优先选择中间结果规模更小的括号化顺序；本题把 $n\times n$ 的中间矩阵变成了 $d\times d$。
