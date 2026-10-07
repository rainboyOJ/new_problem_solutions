---
oj: "roj"
problem_id: "3552"
title: "[NOIP2007-普及] 奖学金"
description: "读入三科成绩算总分，按总分、语文、学号排序后输出前 5 名。"
difficulty: "入门"
date: 2026-10-02 07:06
updated: 2026-10-06 13:43
toc: true
tags: ["入门", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3552
---

[[TOC]]

## 题目描述

$n$ 名学生每人有语文、数学、英语三科成绩，学号即输入顺序 $1 \sim n$。按总分从高到低排序；总分相同则语文高者靠前；仍相同则学号小者靠前。输出前 $5$ 名的学号与总分。

## 思路

读入时计算总分并记录语文成绩和学号，用结构体数组按规则排序后输出前 $5$ 名即可。

## 参考代码

@include-code(./main.cpp, cpp)

