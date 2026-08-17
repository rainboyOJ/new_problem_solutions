---
oj: "shumeng"
problem_id: "CSP202006A"
title: "线性分类器"
description: "代入直线方程检查两类点内部同号且两类代表符号相反。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "几何", "分类"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202006A
---

[[TOC]]

## 形式化题目

有 $n$ 个带类别 $\text{A}$ 或 $\text{B}$ 的平面点 $(x_i,y_i)$ 和 $m$ 条直线

$$
\theta_0+\theta_1x+\theta_2y=0,
$$

对每条直线判断它是否把两类点完全分到两侧：一侧只有 A 类点，另一侧只有 B 类点。数据保证没有任何点恰好落在直线上。

## 思路

把每个点 $(x,y)$ 代入直线方程，得到的值的正负号表示这个点位于直线的哪一侧。因为不会出现零，只需要比较符号。

### 判断步骤

1. 记录第一个 A 点与第一个 B 点的符号，作为两类各自的代表符号；
2. 扫描全部点：A 点都必须与 A 的代表符号相同，B 点都必须与 B 的代表符号相同；
3. 两个代表符号还必须相反，说明两类点分居直线两侧。

三个条件全部满足时输出 `Yes`，否则输出 `No`。

先看一个朴素的两遍扫描实现，第一遍确定每类代表符号，第二遍验证所有点：

@include-code(./brute.cpp, cpp)

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

每条查询扫描全部 $n$ 个点，时间复杂度为 $O(nm)$，空间复杂度为 $O(n)$。

## 总结

线性分类器的“分隔”条件不需要做复杂的几何运算。把所有点代入同一个一次式，检查同类同号、异类异号即可。