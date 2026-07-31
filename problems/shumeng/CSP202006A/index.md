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

### 题意

给出带类别 `A` 或 `B` 的平面点，以及若干直线

$$
\theta_0+\theta_1x+\theta_2y=0.
$$

判断每条直线是否将两类训练点完全分到直线的两侧。题目保证没有点恰好落在直线上。

### 思路

把点 `(x,y)` 代入直线方程。结果为正和为负分别表示直线的两个半平面，因为不会为零，只需记录符号。

对一条查询，记录第一个 A 点和第一个 B 点各自的符号。扫描全部点时，A 点必须都等于 A 的代表符号，B 点必须都等于 B 的代表符号，且两个代表符号必须相反；三个条件都满足时输出 `Yes`。

小数据暴力解同样逐点检查，用两遍扫描先确定每类代表符号再验证所有点。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个查询扫描全部 `n` 个点，时间复杂度为 $O(nm)$，空间复杂度为 $O(n)$。

### 总结

线性分类器的“分隔”条件不需要做复杂几何运算。把所有点代入同一个一次式，检查同类同号、异类异号即可。
