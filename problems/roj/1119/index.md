---
oj: "roj"
problem_id: "1119"
title: "矩阵交换行"
description: "读入固定 5×5 矩阵，直接交换指定两行后输出。"
difficulty: "入门"
date: 2026-09-29 19:38
updated: 2026-09-29 19:39
toc: true
tags:
  - 模拟
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1119
---

[[TOC]]

## 形式化题目

给定一个固定的 $5 \times 5$ 整数矩阵 $A$ 和两个行号 $m, n$（$1 \leqslant m, n \leqslant 5$），要求输出将 $A$ 的第 $m$ 行与第 $n$ 行整体交换后得到的新矩阵 $A'$。行内元素的相对顺序保持不变。

## 正解

### 思路

矩阵大小固定为 $5 \times 5$，数据规模极小，直接模拟“交换两行”即可。

具体步骤：

1. 读入全部数据，把前 25 个整数按每 5 个一组切分成 5 行；
2. 将输入的 1 基行号转成 0 基下标，交换对应的两行；
3. 按新的行顺序输出矩阵。

由于 $m$ 与 $n$ 可能相同，Python 的元组解包 `rows[m], rows[n] = rows[n], rows[m]` 在这种情况下也不会出错，结果保持原矩阵不变。

### 代码

@include-code(./main.py, python)

### 复杂度

读入、交换、输出都只在固定 25 个元素上进行。

- 时间复杂度：$O(1)$（实际为常数 $5 \times 5$）
- 空间复杂度：$O(1)$

## 总结

本题是最基础的矩阵行交换模拟。核心在于把矩阵按行存储成列表，再用一次解包完成交换；无需任何额外算法优化。
