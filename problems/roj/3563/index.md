---
oj: "roj"
problem_id: "3563"
title: "[NOIP2008-普及] 立体图"
description: "按后→前、左→右、下→上的画家算法，把固定 7×6 字形覆盖到字符画布上生成立体图。"
difficulty: "普及"
date: 2026-10-02 07:50
updated: 2026-10-06 14:09
toc: true
tags: ["模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3563
---

[[TOC]]

## 题目描述

给定 $m \times n$ 的积木高度图（$m,n \le 50$），画出其立体图：每个单位积木用 `+---+`、`/   /|` 等字符拼出正视投影，输出字符矩阵。

## 思路

按"从后往前、从左往右"的次序画每根柱子：先画顶面 `+---+` 与侧面 `/`、`|`，高处的柱子自然遮挡低处，逐格把对应字符写入画布，最后逐行输出。

## 参考代码

@include-code(./main.cpp, cpp)
