---
oj: "luogu"
problem_id: "P1481"
title: "魔族密码"
description: "把所有单词放入集合，枚举每个单词的前缀即可得到以它结尾的最长词链。"
difficulty: "普及-"
date: 2026-07-16 19:57
toc: true
tags: ["字符串", "集合", "前缀", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1481
---

[[TOC]]

### 题意

从单词表中选出尽量多的词，使前一个词始终是后一个词的前缀。

### 思路

固定链的最后一个单词 `word`。所有出现在词表中的 `word` 前缀天然按长度互相包含，所以把它们全部选上就是最优链。

因此只需把单词放入集合，对每个 `word` 枚举所有非空前缀并统计有多少个也在集合中，取最大值。

单词长度最多 75，切片产生的额外常数很小；相比手写 Trie，这种写法更能体现 Python 的字符串和哈希集合优势。

### Python 知识

- `set(data[1:])` 建立平均 $O(1)$ 查询的单词集合。
- `word[:length] in words` 同时使用字节串切片与集合成员测试。
- 内层 `sum(...)` 统计布尔值，外层 `max(...)` 取所有链的最大长度。
- 生成器表达式不保存所有中间计数。

### 代码

@include-code(./main.py, python)

### 复杂度

设最大单词长度为 $L\le75$，考虑切片与哈希字符成本，时间 $O(nL^2)$，空间 $O(nL)$。

### 总结

当键本身就是完整短字符串时，Python 集合往往比节点级 Trie 更短、更清楚。
