---
oj: "roj"
problem_id: "3655"
title: "龙虎斗"
description: "把龙虎气势差折叠成带符号的 delta = Σ c_i×(m-i)，再枚举投放位置 p 取 |delta + s_2×(m-p)| 最小的最小编号。"
difficulty: "入门"
date: 2026-10-02 13:30
updated: 2026-10-06 16:00
toc: true
tags: ["枚举", "前缀和思想", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3655
---

[[TOC]]

## 题目描述

线段上有 n 个兵营，第 i 个有 c_i 位工兵。以 m 号兵营为界，左侧（p<m）属龙方，右侧（p>m）属虎方，m 号不属于任何一方；兵营 p 的气势为 c_p × |p-m|，一方势力为所属兵营气势之和。先在 p_1 号兵营增加 s_1 位工兵，再把 s_2 位工兵全部投放到某个兵营 p_2，使龙、虎两方势力之差的绝对值最小，输出最优的 p_2（并列取最小编号）。

输入第一行 n，第二行 n 个整数 c_i，第三行四个整数 m, p_1, s_1, s_2；输出一个整数 p_2。数据范围：1 < m < n ≤ 10^5，c_i, s_1, s_2 ≤ 10^9。样例 1 输入 `6 / 2 3 2 3 2 3 / 4 6 5 2`，输出 `2`；样例 2 输入 `6 / 1 1 1 1 1 16 / 5 4 1 1`，输出 `1`。

## 思路

把龙虎气势差折叠成一个带符号的和 δ = Σ c_i×(m-i)：p<m 的项为正（龙），p>m 的项为负（虎），p=m 恰为 0。投放 s_2 人到 p 后的差距为 |δ + s_2×(m-p)|，从左到右扫一遍取最小值，并列取最小编号；初值取 p=m 即“不改变气势”。气势差可达约 2×10^19，需用 `__int128`。

## 参考代码

@include-code(./main.cpp, cpp)
