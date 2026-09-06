---
oj: "luogu"
problem_id: "P17413"
title: "「IXOI R3」时间复杂度分析"
description: "比较 n、n^2 与 5×10^8 的关系，按复杂度从高到低输出能够通过的最高级别。"
difficulty: "未知"
date: 2026-09-06 19:06
toc: true
tags: ["复杂度", "数学"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P17413
---

[[TOC]]

## 形式化题目

给定正整数 `n`。允许的复杂度只有 `O(1)`、`O(n)`、`O(n^2)`，一次运算上限为 `5×10^8`。
求能够在该上限内完成的最高复杂度。

## 思路

把三种复杂度对应的运算次数分别写出来：

- `O(1)` 需要 `1` 次，永远可以通过；
- `O(n)` 需要 `n` 次，当 `n≤5×10^8` 时可以通过；
- `O(n^2)` 需要 `n^2` 次，当 `n^2≤5×10^8` 时可以通过。

因此按复杂度从高到低判断即可。平方判断不能直接计算 `n*n`，因为 `n` 最大可达 `10^18`；使用 `n≤5×10^8/n` 可以避免溢出。

下面的暴力程序直接计算平方，只用于小数据验证。

@include-code(./brute.cpp, cpp)

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

只进行常数次判断，时间复杂度为 `O(1)`，额外空间复杂度为 `O(1)`。

## 总结

本题的关键是先判断更高的复杂度。比较乘积时要注意整数溢出，利用 `n≤C/n` 就能安全判断 `n^2≤C`。
