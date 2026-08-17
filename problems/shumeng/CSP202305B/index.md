---
oj: "shumeng"
problem_id: "CSP202305B"
title: "矩阵运算"
description: "利用矩阵乘法结合律先计算 K^T V，再计算按行缩放后的 Q 与该小矩阵的乘积。"
difficulty: "普及+/提高-"
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

## 形式化题目

给定 $n\times d$ 的矩阵 $Q,K,V$ 和长度为 $n$ 的向量 $W$，计算

$$\left(W\cdot(QK^T)\right)V,$$

其中 $W$ 按行缩放 $QK^T$（第 $i$ 行的每个元素都乘以 $W_i$），输出一个 $n\times d$ 矩阵。数据范围 $n\le 10^4,\ d\le 20$，矩阵元素为整数。

## 思路

先看直接按照题目公式展开的朴素做法，它把 $QK^T$ 的每个元素显式算出来：

@include-code(./brute.cpp, cpp)

直接计算 $QK^T$ 需要 $O(n^2d)$，当 $n=10^4$ 时约为 $2\times 10^9$ 次乘法，不可行。

### 利用矩阵乘法结合律

矩阵乘法满足结合律，可以调整括号顺序：

$$\left(W\cdot(QK^T)\right)V=(W\cdot Q)(K^TV)。$$

观察维数：$K^TV$ 是 $d\times d$ 的小矩阵，而 $(W\cdot Q)$ 仍是 $n\times d$。中间矩阵从 $n\times n$ 缩小为 $d\times d$，运算量大大下降。

### 计算步骤

1. 先算 $B=K^TV$，其中
   $$B_{i,j}=\sum_{r=1}^{n}K_{r,i}V_{r,j}。$$
2. 对答案第 $r$ 行，把 $Q_r$ 先乘上 $W_r$，再与 $B$ 相乘：
   $$A_{r,j}=\sum_{i=1}^{d}W_rQ_{r,i}B_{i,j}。$$

实现时统一使用 `long long`：中间与最终结果的数量级都可能远超 `int` 范围。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

计算 $K^TV$ 与最终结果都需要 $O(nd^2)$ 时间；存储三个输入矩阵和 $d\times d$ 中间矩阵需要 $O(nd+d^2)$ 空间。

## 总结

矩阵乘法不满足交换律，但满足结合律。面对形如 $ABC$ 的乘积，应优先选择中间结果规模更小的括号化顺序；本题通过先算 $K^TV$ 把 $n\times n$ 的中间矩阵变成了 $d\times d$。