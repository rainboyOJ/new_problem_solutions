---
oj: "roj"
problem_id: "3540"
title: "谁拿了最多奖学金"
description: "逐名学生按五条严格大于条件累加奖金，并用严格大于维护最大者以保证并列取先出现者，O(N) 模拟。"
difficulty: "入门"
date: 2026-10-02 06:17
updated: 2026-10-06 13:36
toc: true
tags: ["模拟", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3540
---

[[TOC]]

## 题目描述

期末考试后按五条互不排斥的奖学金规则发奖金。输入第一行是学生总数 N，接下来 N 行每行：姓名、期末平均成绩 avg、班级评议成绩 cls、是否干部（Y/N）、是否西部省份（Y/N）、论文数。输出：奖金总数最高的学生姓名（并列取输入中最先的）、该生奖金、全体学生的奖金总和。N ≤ 100。

## 思路

逐名学生按题面五条严格大于条件累加奖金，同时累加全体总和。扫描时用严格大于更新最大者，并列时自然保留先出现的学生。

## 参考代码

@include-code(./main.cpp, cpp)
