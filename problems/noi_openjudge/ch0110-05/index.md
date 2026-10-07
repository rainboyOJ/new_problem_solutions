---
oj: "noi_openjudge"
problem_id: "ch0110-05"
title: "分数线划定"
description: "按分数降序和报名号升序排序，以计划人数的 150% 位置确定分数线。"
difficulty: "普及-"
date: 2026-07-30 23:01
updated: 2026-10-06 07:45
toc: true
tags: ["排序", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0110-01"
    reason: "B 的分数线划定复用 A 教的排序后按名次取元素（名次转下标要减一）：第 int(m*1.5) 名的成绩对应下标 int(m*1.5)-1，再叠加 key 元组排序与同线全保留"
  - oj: "noi_openjudge"
    problem_id: "ch0110-03"
    reason: "B 的排序直接复用 A 的「(-分数, 次键) 元组键」这一步：负号让分数降序、报名号升序做次键，一条 sort 表达两级规则，再叠加 A 未教的 150% 分数线取第 int(m*1.5) 名成绩与不低于线的筛选。"
recommend: []
source: http://noi.openjudge.cn/ch0110/05/
common:
  - oj: "luogu"
    problem_id: "P1093"
    reason: "同难度同型题（M5 自 pre 移入；master 重新定级后两者同档）：B 直接复用 A 教的多关键字 key 元组写法（降序字段取负、升序字段取原值）按分数降序报名号升序排序，再叠加 150% 分数线划定与同线全保留"
---

[[TOC]]

### 题意

根据计划录取人数的 $150\%$ 确定面试分数线，并输出所有分数不低于分数线的选手。成绩相同的选手按报名号升序输出。

### 思路

先按 `(-分数, 报名号)` 排序。分数线是第 `int(m * 1.5)` 名的成绩，对应 Python 下标 `int(m * 1.5) - 1`。再从排好序的序列中筛出所有分数不低于这条线的选手，自然保持题目要求的输出顺序。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

### 总结

分数线只决定最低分数，和分数线相同的所有选手都必须保留。
