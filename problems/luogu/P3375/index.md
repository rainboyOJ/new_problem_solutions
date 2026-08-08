---
oj: "luogu"
problem_id: "P3375"
title: "【模板】KMP"
description: "用前缀函数在线性时间输出所有匹配位置，并给出模式串每个前缀的最长 border。"
difficulty: "普及+/提高"
date: 2026-07-16 19:57
toc: true
tags: ["KMP", "前缀函数", "字符串", "python"]
favorite: true
favorite_reason: "KMP 模板题，前缀函数（pi 数组）和匹配回退的定式"
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

@include-code(./main1.py, python)

`main1.py` 用 `str.find` 做匹配，逻辑正确但有两个点会 TLE（全 `A` 的长串反复调用 `find` 退化到 $O(n^2)$）。

纯 Python 实现的 KMP：

@include-code(./main-kmp.py, python)

`main-kmp.py` 用标准 KMP 算法做匹配，代码可读性好，但未做内存优化，百万字符下 Python 对象开销比 `main.py` 大。

### 复杂度

| 做法 | 时间 | 空间 |
|------|------|------|
| main.py（KMP + array + 缓冲） | $O(\|text\|+\|pattern\|)$ | $O(\|pattern\|)$ 加输出缓冲 |
| main-kmp.py（纯 Python KMP） | $O(\|text\|+\|pattern\|)$ | $O(\|text\|+\|pattern\|)$ |
| main1.py（str.find） | $O(n^2)$ 退化（2 TLE） | $O(1)$ |

### 总结

KMP 的核心不是背循环，而是理解 `prefix[j-1]` 给出了失配后仍可能匹配的最长前缀。
