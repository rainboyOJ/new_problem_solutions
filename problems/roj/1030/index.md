---
oj: "roj"
problem_id: "1030"
title: "计算球的体积"
description: "π 固定取 3.14，直译公式 V=4/3·π·r³，再用 printf(\"%.2f\") 保留 2 位小数输出，O(1) 求值。"
difficulty: "入门"
date: 2026-09-29 14:40
updated: 2026-10-04 22:51
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1030
---

[[TOC]]

## 题目描述

给定球的半径 $r$（不超过 100 的非负实数），按题面指定的 $\pi = 3.14$ 计算球体积 $V = \frac{4}{3}\pi r^3$，结果保留小数点后 2 位输出。

输入：一个非负实数，即球半径。输出：一个实数，即球的体积，保留 2 位小数。

样例：输入 `4`，输出 `267.95`。

## 思路

代入公式直接求值即可，注意 $\pi$ 必须取题面给的 3.14，不能用 `math.pi`，否则舍入结果可能差 0.01。

另外 `4/3` 要写成真除法（`4.0/3.0`），最后用 `printf("%.2f")` 四舍五入到 2 位小数并补零。

## 参考代码

@include-code(./main.cpp, cpp)
