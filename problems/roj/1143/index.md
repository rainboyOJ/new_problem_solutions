---
oj: "roj"
problem_id: "1143"
title: "最长最短单词"
description: "把一行字符串按非字母字符切成单词，利用 max/min 的稳定顺序分别取出第一个最长、第一个最短单词。"
difficulty: "入门"
date: 2026-09-29 20:40
updated: 2026-10-04 14:24
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

## 形式化题目

给定一行字符串 $s$，字符集为 `A-Za-z`、空格和逗号。将 $s$ 中所有极大连续字母子串称为**单词**。设单词序列为 $w_1, w_2, \dots, w_n$（按出现顺序）。要求输出：

- 满足 $|w_i|$ 最大的第一个 $w_i$；
- 满足 $|w_i|$ 最小的第一个 $w_i$。

## 正解

### 思路

题目只关心“连续字母段”的长度，而不关心字母本身。因此，先把整行按非字母字符切分成单词列表；随后分别按长度取最大值、最小值。

关键观察：Python 的 `max(iterable, key=len)` 和 `min(iterable, key=len)` 在比较键相等时，会保留先出现的元素。这正好对应题面要求的“第一个最长/最短单词”。

### 代码

@include-code(./main.py, python)

### 复杂度

设整行长度为 $L$，则：

- 时间复杂度：$O(L)$。正则扫描一次，再各遍历一次单词列表。
- 空间复杂度：$O(L)$，用于存放切分后的单词。

## 总结

本题是一道入门字符串模拟：把分隔符统一看成“非字母字符”，提取连续字母段后用稳定顺序的最大/最小值即可得到答案。
