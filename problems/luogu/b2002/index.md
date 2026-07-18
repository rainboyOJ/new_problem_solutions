---
oj: "luogu"
problem_id: "B2002"
title: "Hello,World!"
description: "直接使用 print 输出固定字符串 Hello,World!，注意逗号后没有空格。"
difficulty: "入门"
date: 2026-07-15 23:33
toc: true
tags: ["入门", "输出", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/B2002
---

[[TOC]]

### 题意

输出固定内容：

```text
Hello,World!
```

逗号后面没有空格，`H` 和 `W` 都是大写。

### 思路

这是最基础的输出题，不需要读取输入，也不需要计算。把题目要求的字符串原样放进 `print` 即可。

本题没有必要写暴力程序，因为不存在可枚举的决策或待验证的算法。

### Python 知识

- `print(...)` 会把内容输出到标准输出。
- 字符串需要放在引号里，例如 `"Hello,World!"`。
- 默认情况下，`print` 会在末尾输出一个换行，正好符合 OJ 输出格式。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

一行输出：

@include-code(./main-pythonic.py, python)

### 复杂度

时间复杂度是 $O(1)$，空间复杂度是 $O(1)$。

### 总结

这题用来确认 Python 程序的基本结构：写一行 `print`，输出完全匹配题目要求的字符串。
