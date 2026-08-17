---
oj: "shumeng"
problem_id: "CSP201809A"
title: "卖菜"
description: "保存第一天价格，按端点两项和中间三项的整数平均值计算第二天价格。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201809A
---

[[TOC]]

## 形式化题目

给定长度为 $n$ 的整数序列 $a_1, a_2, \dots, a_n$。构造新序列 $b_1, b_2, \dots, b_n$，满足

$$
b_i = \begin{cases}
\left\lfloor \dfrac{a_1 + a_2}{2} \right\rfloor, & i = 1,\\[4pt]
\left\lfloor \dfrac{a_{i-1} + a_i + a_{i+1}}{3} \right\rfloor, & 2 \le i \le n - 1,\\[4pt]
\left\lfloor \dfrac{a_{n-1} + a_n}{2} \right\rfloor, & i = n.
\end{cases}
$$

其中 $\lfloor \cdot \rfloor$ 表示去尾法向下取整。

## 思路

### 端点与中间分开处理

端点 $1$ 和 $n$ 各只有一个邻居，取两项的平均值；中间的每个位置取自己与左右邻居三项的平均值。用整数除法 `a / b` 即可实现向下取整。

### 新旧状态分离

所有 $b_i$ 都只依赖第一天的价格 $a$。因此必须先完整保存 $a$，再统一计算 $b$，不能在原数组上边算边覆盖。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：每个商店只计算一次，$O(n)$。
- 空间：保存两天的价格数组，$O(n)$。

## 总结

同步更新题的核心是区分旧状态和新状态：先完整读入旧值，再据此推出全部新值。两个端点的参与项数不同，单独处理即可，整数除法天然满足去尾规则。