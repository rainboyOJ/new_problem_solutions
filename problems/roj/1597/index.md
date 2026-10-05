---
oj: "roj"
problem_id: "1597"
title: "「一本通 5.5 例 1」滑动窗口"
description: "单调队列求滑动窗口最值：队尾淘汰被新元素支配的下标、队首弹出过期下标，队首即窗口答案，两遍 O(N) 扫描输出最小值行与最大值行。"
difficulty: "普及"
date: 2026-09-30 20:52
updated: 2026-10-06 00:54
toc: true
tags: ["单调队列", "滑动窗口", "最值", "python", "一本通"]
favorite: false
favorite_reason: ""
categories:
  - "一本通"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1597
---

[[TOC]]

## 题目描述

给定长度 $N$ 的整数序列与窗口长度 $K$（$1 \le K \le N \le 10^6$，$|a_i| \le 2 \times 10^9$）。窗口每次右移一位，对每个位置求窗口内最小值和最大值：第一行输出全部最小值，第二行输出全部最大值，数字间单空格分隔。样例输入 `8 3` 换行 `1 3 -1 -3 5 3 6 7`，样例输出 `-1 -3 -3 -3 3 3` 换行 `3 3 5 5 6 7`。

## 思路

相邻窗口只差一进一出，用单调队列只保留下标：入队前从队尾弹掉被新元素支配的下标，再从队首弹掉已滑出窗口的下标，队首即为当前窗口最值。最小值、最大值各扫一遍，每个下标进出队各一次，总复杂度 $O(N)$。

## 参考代码

@include-code(./main.cpp, cpp)
