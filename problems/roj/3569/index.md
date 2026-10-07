---
oj: "roj"
problem_id: "3569"
title: "[NOIP2009-普及] 分数线划定"
description: "按成绩降序、同分报名号升序排序后取第 ⌊1.5m⌋ 名的分数作分数线，再输出所有不低于分数线的选手。"
difficulty: "普及-"
date: 2026-10-02 08:12
updated: 2026-10-07 13:50
toc: true
tags: ["排序", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0110-03"
    reason: "A 教的「排序键写成 (-分数, 姓名)，负号把降序变升序」被 B 逐个迁移为按 (-成绩, 报名号) 排序，再用这一次排序同时供取分数线与输出"
  - oj: "roj"
    problem_id: "1176"
    reason: "B 复用了 A 教的「按成绩降序排序后按下标取第 k 名」这一步，把第 k 名换成第 ⌊1.5m⌋ 名的分数当分数线，再叠加 s>=L 的前缀过滤处理重分扩招。"
  - oj: "noi_openjudge"
    problem_id: "ch0110-01"
    reason: "B 在取分数线时原样套用 A 教的「排序后名次转下标取元素」，代码里即 ranked[r-1][1]，再叠加同分报名号排序键与 >=L 过滤"
common: []
recommend: []
source: https://roj.ac.cn/problem/3569
---

[[TOC]]

## 题目描述

给定 $n$ 名选手的报名号 $k_i$ 与成绩 $s_i$。计划录取 $m$ 人，面试分数线为排名第 $\lfloor 1.5m \rfloor$ 的选手的分数，最终所有成绩不低于该分数线的选手进入面试。输出分数线、实际进面人数，以及进面选手按成绩降序、同分按报名号升序排列的名单。

数据范围：$5 \le n \le 5000$，$3 \le m \le n$，$1000 \le k_i \le 9999$，$1 \le s_i \le 100$。

## 思路

按 $(-成绩, 报名号)$ 排序后，第 $r = \lfloor 1.5m \rfloor$ 名的成绩即为分数线 $L$；再顺序输出所有 $s_i \ge L$ 的选手即可，重分扩招自动满足。

## 参考代码

@include-code(./main.cpp, cpp)
