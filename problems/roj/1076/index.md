---
oj: "roj"
problem_id: "1076"
title: "正常血压"
description: "把每次测量压成正常/异常布尔值，一次遍历维护以当前位置结尾的连续段长，逐步取 max 得到最长正常小时数。"
difficulty: "入门"
date: 2026-09-29 17:30
updated: 2026-10-05 00:21
toc: true
tags: ["入门", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1076
---

[[TOC]]

## 题目描述

监护室每小时测一次血压。若收缩压在 $90\sim140$ 且舒张压在 $60\sim90$（均含端点），则该次测量正常。给定 $n$（$n<100$）次测量的收缩压和舒张压，输出连续正常的最长小时数。

## 思路

每次测量独立判定正常与否，然后求最长连续正常段。遍历一次，正常则当前段长度加一，异常则清零，同时维护最大值。

## 参考代码

@include-code(./main.cpp, cpp)
