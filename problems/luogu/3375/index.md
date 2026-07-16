---
oj: "luogu"
problem_id: "P3375"
title: "【模板】KMP"
description: "用前缀函数在线性时间输出所有匹配位置，并给出模式串每个前缀的最长 border。"
difficulty: "普及/提高-"
date: 2026-07-16 19:57
toc: true
tags: ["KMP", "前缀函数", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3375
---

[[TOC]]

### 题意

输出模式串在文本中的所有出现位置，以及模式串每个前缀的最长真前后缀长度。

### 思路

`prefix[i]` 表示 `pattern[:i+1]` 的最长 border 长度。计算新位置时，若字符失配，就令 `j = prefix[j-1]`，沿 border 链退到下一个可能长度；每次指针的增加和回退总量都是线性的。

匹配文本时使用相同回退规则。`j == m` 表示找到一次完整匹配，输出位置后退到模式串的次长 border，从而允许重叠匹配。

### Python 知识

- 字符串按 `bytes` 处理时，下标访问直接得到整数，百万字符扫描更省内存。
- `array("i")` 只用 4 字节保存一个前缀函数值。
- 匹配位置先写入 `bytearray`，前缀数组再按 8192 个一块输出，避免创建百万个字符串对象。
- `enumerate(text)` 同时取得文本下标和字符。

### 代码

@include-code(./main.py, python)

### 复杂度

时间 $O(|text|+|pattern|)$，空间 $O(|pattern|)$ 加输出缓冲。

### 总结

KMP 的核心不是背循环，而是理解 `prefix[j-1]` 给出了失配后仍可能匹配的最长前缀。
