---
oj: "shumeng"
problem_id: "CSP202312B"
title: "因子化简"
description: "试除分解每个 n，统计各质因子的指数，只保留指数不小于阈值 k 的完整质因数幂。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["数论", "质因数分解", "枚举"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202312B
---

[[TOC]]

## 形式化题目

对正整数 $n$ 做质因数分解，得到 $n=p_1^{t_1}\times\cdots\times p_m^{t_m}$。给定阈值 $k$，指数 $t_i<k$ 的质因数幂整体删除，指数 $t_i\ge k$ 的完整保留；若全部删除则结果为 $1$。处理 $q$ 组查询，每组给出 $n,k$ 输出简化后的值。

## 思路

直接在 $n$ 上做试除分解即可。

### 试除并统计指数

从 $2$ 开始枚举可能的质因子 `prime`。当 `value % prime == 0` 时不断除去它并统计指数 `exponent`，直到除尽；这样既完成了分解，也拿到了该质因子的完整次数。

### 按阈值决定去留

- 若 `exponent >= k`，把 `prime^exponent` 完整乘入答案；
- 否则忽略这一整项。

这里必须先完整统计一个质因子的指数，再决定是否乘回，不能一边除一边乘。

### 处理剩余的大质因子

试除循环只枚举到 $\sqrt{value}$。结束后如果 `value > 1`，它必然是一个指数为 $1$ 的大质因子。由于本题保证 $k>1$，它不会被保留；代码保留了 `k<=1` 时的通用处理作为兜底。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

单次查询最多试除到 $\sqrt n$，时间复杂度为 $O(\sqrt n)$，空间复杂度为 $O(1)$；全部查询为 $O(q\sqrt n)$。

## 总结

因子是否保留只取决于它的指数，必须先统计完整次数再决定去留。试除结束后剩余的大质因子只能出现一次，指数判断是本题容易遗漏的边界。