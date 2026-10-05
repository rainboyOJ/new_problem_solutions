---
oj: "roj"
problem_id: "1438"
title: "「一本通 1.2 练习 3」灯泡"
description: "根据相似三角形建立人位置到影子长度的分段单峰函数，利用三分查找求最大影子长度。"
difficulty: "普及"
date: 2026-09-30 10:22
updated: 2026-10-05 23:47
toc: true
tags:
  - "三分"
  - "计算几何"
favorite: false
favorite_reason: ""
categories:
  - "三分"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1438
---

[[TOC]]

## 题目描述

高度 $h$ 的人站在灯泡与墙之间：灯高 $H$（$H>h$），灯到墙水平距离 $D$，人距灯 $x$，灯光过人头顶投到地面或墙上形成影子（地面与墙面部分之和）。求影子最大长度，保留三位小数。输入：第一行整数 $T$，随后每行三个实数 $H, h, D$；输出：每组一行答案。数据范围：$T \le 100$，$10^{-2} \le H, h, D \le 10^3$，$H-h \ge 10^{-2}$。

样例输入 `3 / 2 1 0.5 / 2 0.5 3 / 4 3 4`（`/` 表示换行），样例输出 `1.000 / 0.750 / 4.000`。

## 思路

设人距灯 $x$，影子长度 $L(x)$ 是单峰函数：光线交点未到墙角（$x \le x_0=\frac{D(H-h)}{H}$）时影子全在地面，$L(x)=\frac{hx}{H-h}$ 单调递增；之后影子爬上墙面，$L(x)=D-x+H-\frac{D(H-h)}{x}$ 是凹函数先增后减。直接在 $[0,D]$ 上三分 $L(x)$ 取最大值，迭代足够多次即可满足精度。

## 参考代码

@include-code(./main.cpp, cpp)
