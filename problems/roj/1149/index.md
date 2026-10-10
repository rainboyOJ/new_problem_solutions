---
oj: "roj"
problem_id: "1149"
title: "最长单词2"
description: "去掉句末标点后逐词扫描，严格更长才更新，保留并列时的第一个最长单词。"
difficulty: "入门"
date: 2026-09-29 20:49
updated: 2026-10-05 03:33
toc: true
tags: ["字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1149
---

[[TOC]]

## 题目描述

输入一行以 `.` 结尾的简单英文句子（长度不超过 500），单词之间用单个空格分隔。去掉句末标点后，输出最长的单词；若多个单词并列最长，输出第一个。

## 思路

先去掉句末的 `.`，然后逐个字符拼出单词。维护当前最长单词及其长度，仅当新单词长度严格更大时才更新，这样并列时自然保留最先出现者。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
