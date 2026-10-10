---
oj: "roj"
problem_id: "1143"
title: "最长最短单词"
description: "顺序扫描一行句子，把连续字母段看作单词，取第一个最长单词和第一个最短单词。"
difficulty: "入门"
date: 2026-09-29 20:40
updated: 2026-10-05 03:20
toc: true
tags: ["字符串", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1143"
---

[[TOC]]

## 题目描述

输入一行句子（不超过 200 个单词，每个单词长度不超过 100），只含字母、空格和逗号，空格和逗号都是单词之间的间隔。输出第一行是第一个最长的单词，第二行是第一个最短的单词。样例输入 `I am studying Programming language C in Peking University`，输出 `Programming` 和 `I`。

## 思路

顺序扫描整行，把每一段连续字母当作一个单词；只有严格更长时才替换最长单词，只有严格更短时才替换最短单词，长度相等的保留先出现的那个，正好得到"第一个最长/第一个最短"。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
