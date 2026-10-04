---
oj: "roj"
problem_id: "1181"
title: "整数奇偶排序"
description: "奇数降序在前、偶数升序在后，用自定义比较函数一次 sort 即可。"
difficulty: "入门"
date: 2026-09-29 22:28
updated: 2026-10-05 04:33
toc: true
tags: ["入门", "排序", "数组", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1181
---

[[TOC]]

## 题目描述

给定一行 10 个非负整数（$0\le a_i\le30000$），要求重新排序：奇数在前且按降序，偶数在后且按升序。

输入：一行 10 个整数。

输出：排序后的一行 10 个整数。

样例输入：`4 7 3 13 11 12 0 47 34 98`

样例输出：`47 13 11 7 3 0 4 12 34 98`

## 思路

把奇数和偶数分别排序后拼接；也可直接用比较函数一次 `std::sort` 完成。

## 参考代码

@include-code(./main.cpp, cpp)
