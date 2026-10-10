---
oj: "roj"
problem_id: "1142"
title: "单词的长度"
description: "整行读入后按空格切分单词，逐个取长度并用逗号连接输出，标点算单词一部分。"
difficulty: "入门"
date: 2026-09-29 20:37
updated: 2026-10-05 03:21
toc: true
tags:
  - 字符串
  - 模拟
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1142
---

[[TOC]]

## 题目描述

输入一行单词序列，相邻单词由 1 个或多个空格间隔，单词数 1~300、序列总长不超过 1000。"没有被空格隔开的连续符号串"（含字母、数字、标点）都算一个单词；按输入顺序输出每个单词的长度，逗号分隔。样例输入 `She was born in 1990-01-02  and  from Beijing city.`，样例输出 `3,3,4,2,10,3,4,7,5`。

## 思路

整行读入后逐字符扫描，维护"是否在单词内"标志与当前长度：碰到空格即结算一次并清零，连续空格自然被吞；用是否已输出过单词的标志，避免行首或词间多打逗号。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)