---
oj: "roj"
problem_id: "1132"
title: "石头剪子布"
description: "利用固定克制表把石头/剪子/布的胜负判断转换为 O(1) 查询，再逐局输出结果。"
difficulty: "入门"
date: 2026-09-29 20:25
updated: 2026-10-05 02:58
toc: true
tags: ["模拟", "字符串映射"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1132
---

[[TOC]]

## 题目描述

石头剪子布规则：石头打剪刀，剪刀剪布，布包石头。共 $N$（$1 \le N \le 100$）局，每局输入一行 `S1 S2`，两人出法均取自 `{"Rock", "Scissors", "Paper"}`（大小写敏感）。对每局输出一行胜者 `Player1` 或 `Player2`，平局输出 `Tie`。

样例输入：

```
3
Rock Scissors
Paper Paper
Rock Paper
```

样例输出：

```
Player1
Tie
Player2
```

## 思路

每局直接查固定的克制关系表：`Rock` 克 `Scissors`，`Scissors` 克 `Paper`，`Paper` 克 `Rock`。用映射 `win_over[s]` 表示被 `s` 克制的出法：出法相同输出 `Tie`，否则 `win_over[S1] == S2` 时 Player1 胜，反之 Player2 胜。整体 $O(N)$ 扫一遍输入即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
