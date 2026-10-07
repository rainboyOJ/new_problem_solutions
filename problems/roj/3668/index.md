---
oj: "roj"
problem_id: "3668"
title: "报数"
description: "把含数字 7 的数当作筛子做埃氏筛，预处理出全部禁报数；查询时从 x+1 扫到下一个未被标记的数，x 被标记则输出 -1。"
difficulty: "普及-"
date: 2026-10-02 14:43
updated: 2026-10-06 02:35
toc: true
tags: ["筛法", "埃氏筛", "数学", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1151"
    reason: "A 教的埃氏筛「枚举筛子、标记其全部倍数」这一步被 B 直接搬用：把筛子从素数换成含 7 的数，只是把倍数改标为禁报，B 原文也点明与埃氏筛结构一模一样"
common: []
recommend: []
source: https://roj.ac.cn/problem/3668
---

[[TOC]]

## 题目描述

报数游戏中，十进制含数字 7 的数及其所有倍数都不能报出。给定 $T$ 个询问，每个询问给出 $x$：若 $x$ 不能报出输出 $-1$，否则输出严格大于 $x$ 的最小可报数。输入首行 $T$，随后 $T$ 行每行一个 $x$；$1\le T\le 2\times10^5$，$1\le x\le 10^7$。样例输入 `4` / `6 33 69 300`，输出 `8 36 80 -1`。

## 思路

像埃氏筛一样，把每个含数字 7 的数当作筛子标记它的全部倍数，得到禁报表；再从后往前推出 `nxt[i]`（不小于 $i$ 的最小可报数），查询时 $x$ 禁报输出 $-1$，否则输出 `nxt[x+1]`。预处理 $O(N\log\log N)$、单次询问 $O(1)$，$N$ 取 $1.2\times10^7$ 以覆盖答案越过 $10^7$ 的情况。

## 参考代码

@include-code(./main.cpp, cpp)
