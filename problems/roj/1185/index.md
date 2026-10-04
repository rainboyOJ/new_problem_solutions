---
oj: "roj"
problem_id: "1185"
title: "单词排序"
description: "用 set 去重并按 ASCII 字典序输出所有不同单词。"
difficulty: "入门"
date: 2026-09-29 22:38
updated: 2026-10-05 04:41
toc: true
tags: ["排序", "字符串", "集合", "输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1185
---

[[TOC]]

## 题目描述

输入一行单词序列，相邻单词之间由 1 个或多个空格间隔。按字典序输出这些单词，重复的单词只输出一次（区分大小写）。数据范围：$1 \leqslant n \leqslant 100$，每个单词长度不超过 50，只含大小写字母。

## 思路

用 `cin >> word` 按任意空白切分单词，`set<string>` 自动去重并按键的 ASCII 顺序排序，最后遍历输出即可。

## 参考代码

@include-code(./main.cpp, cpp)
