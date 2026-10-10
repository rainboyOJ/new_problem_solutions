---
oj: "roj"
problem_id: "2013"
title: "usaco-1.4.1 时钟"
description: "每种移动做 4 次等于没做，只需枚举 4^9 个次数向量；影响矩阵模 4 可逆，解唯一，找到即可输出。"
difficulty: "普及-"
date: 2026-10-01 02:55
updated: 2026-10-06 09:33
toc: true
tags: ["枚举", "位运算", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2013
---

[[TOC]]

## 题目描述

九只钟排成 $3 \times 3$ 方阵（A~I），指针只有 12/3/6/9 点四种位置。有 9 种移动，第 $m$ 种把它影响的钟顺时针拨 $90°$：1 ABDE，2 ABC，3 BCEF，4 ADG，5 BDEFH，6 CFI，7 DEGH，8 GHI，9 EFHI。输入 3 行各 3 个数表示初始时间（3/6/9/12）；输出一行空格分开的最短移动序列使所有指针指向 12 点，多种方案时输出数字拼接最小的。样例输入 `9 9 12 / 6 6 6 / 6 3 6`，样例输出 `4 5 8 9`。

## 思路

每种移动做 4 次等于没做，把 9 种移动各做几次（0~3）编码成 18 位四进制数，枚举全部 $4^9 = 262144$ 个次数向量，检验每只钟"初值 + 被拨次数"是否模 4 为 0。又因九种移动的影响矩阵在模 4 下可逆（$\det = 5$ 为奇数），每个初态恰有一个合法次数向量，找到第一个可行解直接输出即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
