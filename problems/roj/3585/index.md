---
oj: "roj"
problem_id: "3585"
title: "[NOIP2011-普及] 统计单词数"
description: "单词与文章统一转小写，逐位检查匹配并判断左右是否为单词边界。"
difficulty: "普及-"
date: 2026-10-02 09:15
updated: 2026-10-06 14:33
toc: true
tags: ["输入输出", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3585
---

[[TOC]]

## 题目描述

给定一个只含字母的单词和一篇只含字母与空格的文章，输出该单词在文章中出现次数及首次出现位置（首字母下标从 $0$ 开始）。匹配不区分大小写，但必须是独立单词，不能是其他单词的一部分。若未出现则输出 $-1$。

数据范围：单词长度 $1 \sim 10$，文章长度 $1 \sim 10^6$。

## 思路

先把单词和文章统一转成小写，再枚举文章中的每个起始位置，检查该位置起连续 $|w|$ 个字符是否与单词相等，并确认左右两侧不是字母（即处于空格或端点）。记录匹配次数和第一次匹配的位置即可。

## 参考代码

@include-code(./main.cpp, cpp)
