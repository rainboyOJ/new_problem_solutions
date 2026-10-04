---
oj: "roj"
problem_id: "1199"
title: "全排列"
description: "输入串已按字母序排好，按字典序输出它的全部 n! 个排列。"
difficulty: "入门"
date: 2026-09-29 23:02
updated: 2026-10-05 05:19
toc: true
tags: ["入门", "字符串", "递归", "枚举"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1199
---

[[TOC]]

## 题目描述

给定一个由互不相同的小写字母、已按 `a<b<…<z` 升序排好的字符串 $S$（$1\le|S|\le 6$），按字典序输出 $S$ 的全部 $|S|!$ 个排列，每行一个。字典序：两等长串从左到右找第一个不同位置，字母小的在前。样例：`abc` → 六行 `abc acb bac bca cab cba`。

## 思路

输入已升序，对 `s` 反复调用 `next_permutation(s, s+n)`、每次输出当前串，直到回到起点即可。`n ≤ 6` 时最多 720 行。

## 参考代码

@include-code(./main.cpp, cpp)