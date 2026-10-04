---
oj: "roj"
problem_id: "1011"
title: "甲流疫情死亡率"
description: "读入确诊数与死亡数，按死亡率 = 死亡数 ÷ 确诊数 × 100 的公式计算，用 %.3f 保留 3 位小数并拼上百分号输出。"
difficulty: "入门"
date: 2026-09-29 13:06
updated: 2026-10-04 22:30
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1011
---

[[TOC]]

## 题目描述

根据截止 2009 年 12 月 22 日各省报告的甲流确诊数和死亡数，计算甲流死亡率。输入一行两个整数：确诊数 $c$、死亡数 $d$（$d \leqslant c$）；输出一行死亡率，百分数形式，精确到小数点后 3 位。如输入 `10433 60` 则输出 `0.575%`（$60 \div 10433 \times 100 \approx 0.575$）。

## 思路

死亡率就是死亡数占确诊数的百分比：$r = \dfrac{d}{c} \times 100$，必须用浮点除法，整数除法会截断小数。用 `%.3f` 格式化即可完成四舍五入保留 3 位，再在末尾拼上 `%`。

## 参考代码

@include-code(./main.cpp, cpp)
