---
oj: "roj"
problem_id: "1130"
title: "找第一个只出现一次的字符"
description: "两遍扫描：第一遍统计每个字符的频次，第二遍按原串位置序回扫，取第一个频次为 1 的字符。"
difficulty: "入门"
date: 2026-09-29 20:14
updated: 2026-10-05 02:53
toc: true
tags: ["入门", "字符串", "统计", "cpp"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1130
---

[[TOC]]

## 题目描述

给定一个只包含小写字母的字符串（长度小于 100000），找到第一个仅出现一次的字符并输出它；若不存在，输出 `no`。输入一行字符串，输出一行答案或 `no`。样例输入 `abcabd`，输出 `c`。

## 思路

两遍扫描：第一遍统计每个小写字母的出现次数，第二遍按原串位置序回扫，第一个频次为 1 的字符即为答案，扫完都没找到则输出 `no`。第一遍必须扫完整串频次才能定型，否则读到中间时会把后面才重复的字符误判。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
