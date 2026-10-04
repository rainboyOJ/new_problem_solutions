---
oj: "roj"
problem_id: "1146"
title: "判断字符串是否为回文"
description: "回文即正读与倒读相同；用双指针从两端向中间比较字符，遇到不等立即判否，全部配对成功则是回文。"
difficulty: "入门"
date: 2026-09-29 20:49
updated: 2026-10-05 03:27
toc: true
tags: ["入门", "字符串", "回文", "python"]
favorite: false
favorite_reason: ""
categories:
  - 字符串
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1146
---

[[TOC]]

## 题目描述

输入一字符串（无空白，长度 ≤ 100），判断它正读与倒读是否相同：是则输出 `yes`，否则输出 `no`。

样例输入：`abcdedcba` → 样例输出：`yes`。

## 思路

用双指针从字符串两端向中间扫，每步比较两指针字符，相等则继续向内收缩，否则不是回文；扫到 `i >= j` 时所有对称位都配对成功，即为回文。整体 $O(n)$、$O(1)$ 额外空间，n ≤ 100 完全够用。

## 参考代码

@include-code(./main.cpp, cpp)