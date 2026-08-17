---
oj: "shumeng"
problem_id: "CSP202503A"
title: "数值积分"
description: "找到区间内第一个偶数坐标，按步长 2 枚举函数值并乘以坐标间距。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数学"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202503A
---

[[TOC]]

## 形式化题目

给定二次函数 $f(x)=x^2+bx+c$ 和整数区间 $[l,r]$，令

$$
s=2 \times \sum_{x \text{ 为 } [l,r] \text{ 中偶数}} f(x),
$$

求整数 $s$。

## 思路

直接按题意模拟采样过程，分两步完成。

### 确定第一个采样点

采样点的横坐标必须是偶数。若 $l$ 是偶数就从 $l$ 开始，否则从 $l+1$ 开始，即先找到区间内第一个偶数 $first$。

### 以步长 2 累加

从 $first$ 开始每次加 $2$，枚举所有偶数坐标点，累加函数值 $x^2+bx+c$。题目保证 $0 \le l < l+2 \le r \le 1000$，点数很少，直接循环即可。最后把累加结果乘以采样间距 $2$ 输出。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

设区间内偶数点数量为 $k$，时间复杂度为 $O(k)$，空间复杂度为 $O(1)$。

## 总结

本题的关键是正确处理第一个偶数采样点，以及相邻采样点之间步长为 $2$。用一个 `%2` 判断起点，再用循环步长 $2$，就能完整覆盖所有偶数坐标点。