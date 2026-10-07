---
oj: "roj"
problem_id: "1464"
title: "「一本通 2.1 练习 8」收集雪花"
description: "哈希表记录雪花形状最近出现位置，双指针滑动窗口 O(n) 求最长无重复连续子序列"
difficulty: "普及"
date: 2026-09-30 12:17
updated: 2026-10-06 00:18
toc: true
tags:
  - "双指针"
  - "滑动窗口"
  - "哈希表"
favorite: false
favorite_reason: ""
categories:
  - "双指针"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1464
---

[[TOC]]
## 题目描述
有 $n$ 个时刻，每个时刻落下一片雪花，用非负整数 $x_i$ 表示形状。同学们从某个时刻 $a$ 开始、到某个时刻 $b$ 停止，收集 $a \sim b$ 之间的所有雪花，要求收集到的雪花形状互不相同。第一行输入正整数 $n$，第二行输入 $n$ 个非负整数；输出最多能收集的雪花数量。数据范围：$1 \leqslant n \leqslant 10^6$，$0 \leqslant x_i \leqslant 10^9$。
**样例**：
```text
输入：
5
1 2 3 2 1
输出：
3
```
## 思路
右指针向右扫描，用哈希表记录每个形状最近一次出现的下标；当当前形状上次出现在窗口内时，左端点直接跳到上次位置的下一位，左指针单调不降。答案取每一步窗口长度的最大值，总复杂度 $O(n)$。
## 参考代码
@include-code(./main.cpp, cpp)
