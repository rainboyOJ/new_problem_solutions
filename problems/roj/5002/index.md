---
oj: "roj"
problem_id: "5002"
title: "汽车加油"
description: "一维扫描贪心：油够走下一段就绝不在站上加油，缺油时在最后到过的站把油补满，次数即最少；补入量 = m − 当前油量。"
difficulty: "普及-"
date: 2026-10-02 15:41
updated: 2026-10-06 16:30
toc: true
tags: ["贪心", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/5002
---

[[TOC]]

## 题目描述

汽车从 A 到 B，沿途有 $n$ 个加油站；满箱油可跑 $m$ 公里，出发满箱、每次加油都加满。多组数据读到文件尾：每组第一行 $n, m$，第二行 $n+1$ 个实数 $d_1,\dots,d_{n+1}$，$d_i$ 为站 $i-1$ 到站 $i$ 的距离（$0$ 号站为 A、$n+1$ 号站为 B）；输出最少加油次数与加油总量。样例输入 `5 15` 与 `5 7 5 2 6 4`，输出 `2 25`。

## 思路

从满箱出发逐段消耗：油够就开下一段；不够走下一段时在当前站补满（补入量 $= m -$ 当前油量），次数加一。出发那箱不计入答案；数据中存在超过 $m$ 的段，按此规则递推，油量允许为负。

## 参考代码

@include-code(./main.cpp, cpp)
