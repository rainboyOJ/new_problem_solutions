---
oj: "roj"
problem_id: "1400"
title: "统计单词数"
description: '扫描文章中的独立单词，忽略大小写与给定单词比较，统计出现次数并记录首次真实下标。'
difficulty: "入门"
date: 2026-09-30 08:35
updated: 2026-10-05 12:53
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1400
---

[[TOC]]

## 题目描述

给定一个只含字母的单词 $w$ 和一篇只含字母与空格的文章 $s$，统计 $w$ 在 $s$ 中作为独立单词出现的次数（不区分大小写，但必须是完整单词），并输出第一次出现时首字母在 $s$ 中的下标（从 0 开始）。若未出现则输出 `-1`。

## 思路

文章中的独立单词由空格分隔，连续多个空格也要正确跳过；遍历文章提取每个单词，统一转小写后与目标单词比较，相等则计数并记录首次出现位置。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
