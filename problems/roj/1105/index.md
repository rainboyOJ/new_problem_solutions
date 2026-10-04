---
oj: "roj"
problem_id: "1105"
title: "数组逆序重存放"
description: "读入 n 个整数后按逆序输出：用下标从 n 倒到 1 的循环直接打印，O(1) 额外空间。"
difficulty: "入门"
date: 2026-09-29 19:03
updated: 2026-10-05 01:15
toc: true
tags: ["数组", "输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1105
---

[[TOC]]
## 题目描述
把数组按逆序重新存放，例如 8 6 5 4 1 改为 1 4 5 6 8。输入两行：元素个数 $n$（$1<n<100$）与 $n$ 个整数，之间用空格分隔；输出为一行逆序后的 $n$ 个整数，之间用空格分隔。
样例：
```
输入：5  /  8 6 5 4 1
输出：1 4 5 6 8
```
## 思路
读入到数组 a[1..n]，i 从 n 倒到 1 直接打印 a[i]，元素之间补一个空格。
## 参考代码
@include-code(./main.cpp, cpp)