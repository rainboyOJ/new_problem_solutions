---
oj: "roj"
problem_id: "20017"
title: "藏宝图"
description: "从每个格子沿 8 个方向 DFS 游走匹配单词，用标记记录是否已转过一次 90° 弯。"
difficulty: "普及-"
date: 2026-08-28 22:10
updated: 2026-10-07 12:15
toc: true
tags: ["网格", "枚举", "搜索"]
favorite: false
favorite_reason: ""
categories: []
pre:
  - oj: "luogu"
    problem_id: "P3654"
    reason: "B 沿用 A 的网格上枚举起点加直线方向逐格检查这一枚举骨架，扩到 8 方向与最多一次 90 度拐弯的 L 形匹配"
common: []
recommend: []
source: https://roj.ac.cn/problem/20017
---

[[TOC]]

## 题目描述

在一张由大写字母组成的 $R \times C\ (1 \le R, C \le 100)$ 网格藏宝图中，统计单词 $W$（长度至少为 2，由互不相同的大写字母组成）按顺序连续出现的次数。一次出现中，字母要么全在同一条直线（横、竖或对角方向，可正向可反向）上，要么前一部分在一条直线上、剩下的字母在与之垂直的第二条直线上，形成一个 90° 直角拐弯（第一段至少 2 个字母，同一格子的同一种摆放只计一次）。

输入：第一行为单词 $W$，第二行为 $R$，第三行为 $C$，接下来 $R$ 行每行 $C$ 个用空格隔开的大写字母。输出一个整数，表示单词出现次数。

样例 1：在下面 5 行 7 列的网格中，单词 `MENU` 共出现 3 次。

```text
F T R U B L K
P M N A X C U
A E R C N E O
M N E U A R M
M U N E M N S
```

## 思路

把每次出现看成一条"至多拐一次 90° 弯"的路径：枚举起点（内容为 $W[0]$ 的格子）和初始方向，出现的位置就完全确定，天然不重不漏，反向读取也被枚举覆盖。从每个起点沿 8 个方向 DFS 逐格匹配，用 `turned` 标记保证整条路径至多转一次弯，且拐点不能是起点（第一段至少 2 个字母）。时间复杂度 $O(R \cdot C \cdot 8 \cdot L)$，本题数据小轻松通过。

## 参考代码

@include-code(./main.cpp, cpp)
