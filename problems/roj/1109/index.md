---
oj: "roj"
problem_id: "1109"
title: "开关灯"
description: "把三类操作统一成翻倍数，按人只翻 k,2k,3k,… 模拟，输出被翻奇数次的灯。"
difficulty: "入门"
date: 2026-09-29 19:15
updated: 2026-10-05 01:40
toc: true
tags: ["模拟", "数论"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1109
---

[[TOC]]

## 题目描述

有 $N$ 盏编号 $1\ldots N$ 的灯，初始全部**开启**。$M$ 个人按编号从小到大操作：1 号关掉全部灯，2 号打开编号为 2 的倍数的灯，$k\ (k\ge 3)$ 号把 $k$ 的倍数取反。操作完后从小到大输出所有仍然关闭的灯的编号，用逗号分隔。$N,M\le 5000$。样例输入 `10 10`，输出 `1,4,9`。

## 思路

初始全亮让三类操作统一为“第 $k$ 个人翻转 $k$ 的倍数”，无需分支；循环直接落在倍数 $k,2k,3k,\ldots$ 上做异或，总翻转次数即调和级数 $O(N\log M)$，最后输出被翻过奇数次的灯。

## 参考代码

@include-code(./main.cpp, cpp)
