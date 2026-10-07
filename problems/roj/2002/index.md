---
oj: "roj"
problem_id: "2002"
title: "黑色星期五"
description: "按月递推，利用当月天数模 7 转移下月 13 号的星期，统计 n 年内各星期出现次数。"
difficulty: "入门"
date: 2026-05-22 19:17
updated: 2026-10-06 09:05
toc: true
tags:
  - "模拟"
  - "日期与日历"
favorite: false
favorite_reason: ""
categories:
  - "基础算法"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2002
---

[[TOC]]

## 题目描述

给定非负整数 $n$（$n \leqslant 400$），统计从 1900 年 1 月 1 日到 $1900+n-1$ 年 12 月 31 日之间，每月 13 号落在星期六、星期日、星期一、星期二、星期三、星期四、星期五的次数，按该顺序输出 7 个整数。

1900 年 1 月 1 日为星期一；4、6、9、11 月 30 天，1、3、5、7、8、10、12 月 31 天；闰年 2 月 29 天，平年 28 天。闰年判定：能被 4 整除且不能被 100 整除，或能被 400 整除。

## 思路

1900 年 1 月 13 日是星期六。每个月 13 号到下个月 13 号恰好相隔当月总天数，因此星期直接加当月天数再模 7 即可递推。遍历 $n \times 12$ 个月统计次数。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
