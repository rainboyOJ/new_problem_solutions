---
oj: "roj"
problem_id: "3557"
title: "[NOIP2007-提高] 字符串的展开"
description: "扫描每个减号，判定它是否满足展开条件（两侧同类且左 < 右），再按 p1/p2/p3 三个参数生成中间填充段，O(n) 模拟。"
difficulty: "普及"
date: 2026-10-02 07:19
updated: 2026-10-06 13:52
toc: true
tags: ["模拟", "字符串", "NOIP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3557
---

[[TOC]]

## 题目描述

给定 $p_1,p_2,p_3$ 和一个仅含小写字母、数字、减号 `-` 的字符串 $s$（$|s|\le 100$）。
扫描每个 `-`：若两侧同为小写字母或同为数字，且右侧 ASCII 严格大于左侧，则把减号替换成两端字符之间的序列，按 $p_1$（1小写/2大写/3星号）、$p_2$（每个字符重复次数）、$p_3$（1正序/2逆序）生成填充段；否则保留原字符。输出展开后的字符串。

## 思路

遍历字符串，对每个 `-` 检查两侧是否同类且左<右，满足则按 $p_1,p_2,p_3$ 生成中间字符序列并拼接。$p_1=2$ 时仅字母转大写，数字不变；$p_1=3$ 时全部用 `*` 代替。

## 参考代码

@include-code(./main.cpp, cpp)
