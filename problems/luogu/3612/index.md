---
oj: "luogu"
problem_id: "P3612"
title: "[USACO17JAN] Secret Cow Code S"
description: "不构造巨大字符串，而是把目标位置从当前倍增长度反推回原始字符串中的位置。"
difficulty: "普及-"
date: 2026-07-15 22:15
toc: true
tags: ["字符串", "递归", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3612
---

[[TOC]]

### 题意

给定初始字符串 `s`。每次把当前字符串变成：

```text
s + rotate_right(s)
```

长度不断翻倍。给定位置 `N`，求无限扩展字符串中第 `N` 个字符。

### 思路

不能真的构造字符串，因为 `N` 可以到 `10^18`。

先找到一个长度 `length`，使扩展后的字符串长度至少覆盖目标位置。当前字符串由两半组成：

- 前半：上一轮字符串；
- 后半：上一轮字符串右旋一位。

如果目标在后半，设后半中的位置为 `j = position - half`：

- `j == 1` 时，对应上一轮的最后一个字符；
- `j > 1` 时，对应上一轮的第 `j-1` 个字符。

这样不断把 `position` 映射回上一轮，直到落回原始字符串。

#### 位置映射示例

样例 `COW`：

```text
COW -> COWWCO -> COWWCOOCOWWC
```

第 `8` 位在长度 `12` 的字符串中。前半长度 `6`，后半位置 `2`，映射回上一轮位置 `1`，也就是 `C`。

### Python 知识

- Python `int` 可以直接保存 `10^18`。
- 只维护 `position` 和当前长度，不保存扩展字符串。
- `input().split()` 可以读取字符串和数字两个字段。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`

### 代码

@include-code(./main.py, python)

### 复杂度

长度每次减半，所以时间复杂度为 $O(\log N)$，空间复杂度为 $O(1)$。

### 总结

遇到指数级增长的字符串，优先考虑“反推位置”而不是构造内容。
