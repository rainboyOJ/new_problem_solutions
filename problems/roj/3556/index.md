---
oj: "roj"
problem_id: "3556"
title: "[NOIP2007-提高] 统计数字"
description: "用 map 计数把 n 个数压成『值 → 次数』，再按键升序输出，O(n log n)（不同值最多 1e4）。"
difficulty: "普及"
date: 2026-10-02 07:19
updated: 2026-10-07 13:50
toc: true
tags: ["计数", "排序", "NOIP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0107-02"
    reason: "B 正解的第一步就是 A 教的 Counter 频率统计：用 Counter(data) 一遍扫描把序列压成值到次数，再在此外层叠加 sorted(counter) 对键升序并逐键输出，A 的入门题只到「统计频率」为止，排序输出才是 B 的新增台阶。"
common: []
recommend: []
source: https://roj.ac.cn/problem/3556
---

[[TOC]]

## 题目描述

给定 $n$ 个自然数，每个数不超过 $1.5 \times 10^9$，其中互不相同的数不超过 $10000$ 个。统计每个数出现的次数，并按数值从小到大的顺序输出。

输入：第 1 行整数 $n$；接下来 $n$ 行每行一个自然数。输出：$m$ 行（$m$ 为不同数个数），每行两个整数 `值 次数`。

样例：$8$ 个数 $2,4,2,4,5,100,2,100$，输出 $2\ 3, 4\ 2, 5\ 1, 100\ 2$。数据范围 $1 \le n \le 200000$。

## 思路

用 `map<ll, ll>` 一边读入一边计数，map 内部按键升序，直接遍历输出即可。

## 参考代码

@include-code(./main.cpp, cpp)
