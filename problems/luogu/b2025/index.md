---
oj: "luogu"
problem_id: "B2025"
title: "输出字符菱形"
description: "按样例逐行输出由星号和空格组成的固定菱形图案。"
difficulty: "入门"
date: 2026-07-15 23:33
toc: true
tags: ["入门", "输出", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/B2025
---

[[TOC]]

### 题意

输出一个固定的星号菱形：

```text
  *
 ***
*****
 ***
  *
```

### 思路

没有输入，也没有计算。每一行的前导空格都是图案的一部分，需要原样输出。

本题不写暴力程序，因为它只是固定格式输出。

### Python 知识

- 可以连续调用多次 `print`，每次输出一行。
- 字符串开头的空格会被保留，例如 `"  *"` 会输出两个空格再输出星号。
- 写图案题时，最重要的是不要漏掉前导空格。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

多行字符串：

@include-code(./main-pythonic.py, python)

### 复杂度

时间复杂度是 $O(1)$，空间复杂度是 $O(1)$。

### 总结

固定图案输出题的关键不是算法，而是让程序输出与样例完全一致的空格和字符。
