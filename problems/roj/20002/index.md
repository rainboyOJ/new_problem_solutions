---
oj: "roj"
problem_id: "20002"
title: "平整广场"
description: "允许石板伸出边界时，铺满 n×m 广场最少需要 ⌈n/a⌉×⌈m/a⌉ 块 a×a 石板。"
difficulty: "入门"
date: 2026-10-02 19:16
updated: 2026-10-06 02:11
toc: true
tags: [数学, 整除]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20002
---

[[TOC]]

## 题目描述

广场是 $n \times m$ 的矩形，要用 $a \times a$ 的正方形石板铺满。石板不能切割、不能重叠，边必须与广场边平行，但可以伸出边界。求最少石板数。数据范围：$1 \le n,m,a \le 10^9$。

## 思路

石板边平行广场边时，长、宽两个方向互不影响。铺满长度为 $n$ 的边至少需要 $\lceil n/a \rceil$ 块；同理高度方向需要 $\lceil m/a \rceil$ 块。把两个方向的最少块数相乘即可取到下界，因此答案为 $\lceil n/a \rceil \times \lceil m/a \rceil$。

## 参考代码

@include-code(./main.cpp, cpp)
