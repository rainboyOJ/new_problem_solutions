---
oj: "luogu"
problem_id: "P4147"
title: "玉蟾宫"
description: "逐行把连续 F 高度压成直方图，并用单调栈求每行结尾的最大矩形面积。"
difficulty: "普及+/提高"
date: 2026-07-16 18:25
updated: 2026-10-06 07:45
toc: true
tags: ["单调栈", "矩阵", "python"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P3467"
    reason: "B 的直方图最大矩形复用 A 教的「递增高度栈、遇更矮就弹出已结束高度层」这一步（只是弹出时改以当前列为右边界结算面积），再叠加逐行 heights 清零建直方图与高度 0 哨兵清栈。"
  - oj: "shumeng"
    problem_id: "CSP201312C"
    reason: "B 把 A 教的直方图最大矩形单调栈原语（弹栈新栈顶为左界、当前为右界、0 哨兵清空栈）逐行套用，额外只做 heights 二维转一维"
  - oj: "roj"
    problem_id: "3032"
    reason: "B 把 A 教的单调栈弹出结算（新栈顶为左界、当前列为右界、末尾补 0 哨兵）作为内层原语，逐行维护 heights 压成直方图后再套用一次，额外流程只是二维转一维。"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4147
---

[[TOC]]

### 题意

在 `F/R` 网格中找全为 `F` 的最大矩形，输出面积的三倍。

### 思路

逐行维护 `heights[j]`：当前位置为 `F` 就加一，否则清零。每一行都得到一个直方图，所有以下边界在当前行的合法矩形都对应直方图中的矩形。

用递增高度栈处理直方图；遇到更矮柱子时弹出旧高度，并以当前列为右边界结算面积。末尾追加高度 0 的逻辑清空栈。

### Python 知识

- `enumerate(input().split())` 直接更新每列高度。
- 栈元素 `(start, height)` 同时记录该高度最早能向左延伸的位置。
- 普通列表尾部操作足够实现单调栈。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(NM)$，空间复杂度 $O(M)$。

### 总结

二维全 1 最大矩形可以逐行转成经典直方图最大矩形。
