---
oj: "roj"
problem_id: "1621"
title: "「一本通 6.2 练习 2」轻拍牛头"
description: "值域统计 cnt 后让每个出现过的数字向自己的倍数广播，答案为 Σ_{d|A_i} cnt[d] − 1。"
difficulty: "普及-"
date: 2026-09-30 22:32
updated: 2026-10-06 01:18
toc: true
tags: ["数学", "数论", "筛法", "倍数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1621
---

[[TOC]]

## 题目描述

$N$ 头奶牛各持数字 $A_i$，每头牛拍打所有持有 $A_i$ 约数的牛（不含自己）。输入第一行 $N$，接下来 $N$ 行每行一个 $A_i$；输出 $N$ 行答案。$1 \le N \le 10^5$，$1 \le A_i \le 10^6$。样例输入 `5 / 2 1 2 3 4`，样例输出 `2 0 2 1 3`。

## 思路

统计每个数字出现次数 `cnt`，让每个出现过的数字 $d$ 向自己的所有倍数广播 `cnt[d]`，得到 `div_sum[v]` 表示能整除 $v$ 的数字个数（含自己），答案为 `div_sum[A_i] - 1`。

## 参考代码

@include-code(./main.cpp, cpp)
