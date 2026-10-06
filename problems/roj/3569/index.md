---
oj: "roj"
problem_id: "3569"
title: "[NOIP2009-普及] 分数线划定"
description: "按成绩降序、同分报名号升序排序后取第 ⌊1.5m⌋ 名的分数作分数线，再输出所有不低于分数线的选手。"
difficulty: "普及-"
date: 2026-10-02 08:12
updated: 2026-10-06 14:15
toc: true
tags: ["排序", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
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
