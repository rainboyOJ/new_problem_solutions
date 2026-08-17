---
oj: "shumeng"
problem_id: "CSP201409C"
title: "字符串匹配"
description: "按大小写选项统一字符串后，用子串查找逐行筛选包含模式串的文本。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["字符串", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201409C
---

[[TOC]]

## 形式化题目

给定模式串 $S$、大小写敏感选项（`0` 不敏感，`1` 敏感）和多行文本，按输入顺序输出所有包含模式串的文本行。大小写不敏感时，同一字母的大小写视为相同字符。

## 思路

先看手写逐位置比较的暴力：

@include-code(./brute.cpp, cpp)

每一行独立判断，不需要保存全部文本。大小写不敏感时，先把模式串和当前文本都转换为小写，再调用 `find()` 判断模式串是否出现；大小写敏感时直接查找原字符串。输出时保留原始文本行。

### 处理流程

以样例为例，模式串 `Hello`，敏感选项为 `1`：

| 文本行 | 包含 `Hello`? | 输出 |
| --- | --- | --- |
| HelloWorld | 是 | 输出 |
| HiHiHelloHiHi | 是 | 输出 |
| GrepIsAGreatTool | 否 | - |
| HELLO | 否（大小写敏感） | - |
| HELLOisNOTHello | 是 | 输出 |

若把敏感选项改为 `0`，第 4 行 `HELLO` 转成小写 `hello` 后也能匹配，应当输出。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

设文本行和模式串长度上界为 $L$，共有 $n$ 行。标准库子串查找的最坏复杂度为 $O(L^2)$，总时间复杂度为 $O(nL^2)$，额外空间复杂度为 $O(L)$。

## 总结

字符串匹配题的关键是先明确比较规则，再统一输入的表示。匹配时使用规范化后的字符串，输出时使用原字符串，就能同时满足大小写选项和原行输出要求。