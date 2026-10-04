---
oj: "roj"
problem_id: "1050"
title: "骑车与走路"
description: "步行耗时 s/1.2 与骑车耗时 s/3+50 同乘 6 化为整数 5s 与 2s+300 再比较，避免浮点误差，临界距离 s=100 时一样快。"
difficulty: "入门"
date: 2026-09-29 16:22
updated: 2026-10-04 23:30
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1050
---

[[TOC]]

## 题目描述

骑车要花 27 秒找车开锁、23 秒停车锁车；步行速度 1.2 米/秒，骑车速度 3.0 米/秒。给定这次要走的距离 $s$（整数，单位米），判断骑车快、走路快还是一样快，分别输出 `Bike`、`Walk`、`All`。

输入一行一个整数 $s$，输出一行一个字符串。样例输入 `120`，输出 `Bike`。

## 思路

步行耗时 $s/1.2$，骑车耗时 $s/3+50$，两边同乘 6 化为整数 $5s$ 与 $2s+300$ 再比较，避免浮点误差。相减得 $3s-300$，所以临界距离恰好是 $s=100$：$s>100$ 输出 `Bike`，$s=100$ 输出 `All`，$s<100$ 输出 `Walk`。

## 参考代码

@include-code(./main.cpp, cpp)
