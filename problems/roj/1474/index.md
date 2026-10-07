---
oj: "roj"
problem_id: "1474"
title: "Immediate Decodability"
description: "将数字串按字典序排序后只需检查相邻两串是否为前缀关系，即可判定集合是否可立即解码。"
difficulty: "入门"
date: 2026-09-30 12:56
updated: 2026-10-06 00:24
toc: true
tags:
  - "字符串"
  - "排序"
  - "字典树"
favorite: false
favorite_reason: ""
categories:
  - "字符串算法"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1474
---

[[TOC]]

## 题目描述

原题来自：ACM Pacific NW Region 1998。给出多组数据，每组 2~8 个只含 0/1 的数字串（1≤l≤10），以单独一行的数字 9 结束本组；判断每组中是否有一个数字串是另一个串的前缀，是则输出 `Set t is not immediately decodable`，否则输出 `Set t is immediately decodable`，t 为组号（从 1 开始）。输入样例：`01 10 0010 0000 9`、`01 10 010 0000 9`（两组，各以 9 结束），输出样例：`Set 1 is immediately decodable`、`Set 2 is not immediately decodable`。

## 思路

把每组数字串按字典序排序后，若存在某串是另一串的前缀，则必有一对相邻串满足前缀关系，因此只需检查排序后相邻两串是否为前缀即可。n≤8、l≤10，逐对比较总代价极小。

## 参考代码

@include-code(./main.cpp, cpp)
