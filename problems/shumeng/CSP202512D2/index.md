---
oj: "shumeng"
problem_id: "CSP202512D2"
title: C 形阵 - 加强版
description: "使用与 C 形阵基础版相同的乘法函数容斥和 Min_25 质因数递归，支持 n<=10^10。"
date: 2026-07-31 16:22
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202512D2
difficulty: "未知"
---

[[TOC]]

### 题意

求大小不超过 `n` 的 C 形阵价值总和，或其中完美 C 形阵的价值总和；本加强版将 `n` 提高到 `10^10`。

### 思路

先由 `B=F` 固定大小并参数化 `C,E`，将每个方案的价值分解为质因子上的独立局部选择。完美方案的非完美条件对应六个指数向量线性关系，利用两两交集均为 `X=Y=0` 的容斥公式统计。

代码预计算各质数幂的六组局部函数值，再通过 Min_25 筛得到质数贡献，并递归枚举最小质因子，计算乘法函数的前缀和。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

使用整除分块和质数筛处理 `n<=10^10`，空间复杂度为整除分块状态数级别。

### 总结

加强版的关键不是枚举大小，而是把答案改写成少量乘法函数的前缀和。
