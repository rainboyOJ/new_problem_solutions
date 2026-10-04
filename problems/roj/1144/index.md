---
oj: "roj"
problem_id: "1144"
title: "单词翻转"
description: "整行读入一次扫描：非空格字符进缓冲区，遇空格就把缓冲区逆序结算并原样保留空格，单遍 O(n)。"
difficulty: "入门"
date: 2026-09-29 20:38
updated: 2026-10-05 03:27
toc: true
tags: ["字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1144
---

[[TOC]]

## 题目描述

输入一个句子（一行，不超过 500 个字符），将句子中的每一个单词翻转后输出。单词之间以空格隔开，输出时单词之间的空格需与原文一致。

样例：输入 `hello world`，输出 `olleh dlrow`。

## 思路

空格是内容不是分隔符，必须整行读入：用一次扫描，非空格字符累积进缓冲区，遇到空格就把缓冲区逆序追加到结果、再原样补上这个空格，行尾对缓冲区做一次兜底结算。每个字符只被处理常数次，复杂度 $O(n)$，连续空格、串首尾空格都由同一机制天然覆盖。

## 参考代码

@include-code(./main.cpp, cpp)
