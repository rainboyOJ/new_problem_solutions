---
oj: "luogu"
problem_id: "P1765"
title: "手机"
description: "预处理每个小写字母和空格需要按键的次数，再顺序累加整句话。"
difficulty: "入门"
date: 2026-06-19 09:27
toc: true
tags: ["模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1765
---

[[TOC]]

### 题意

给出一行只包含小写字母和空格的句子。按照老式手机键盘规则，求打出整句话至少需要按多少次键。

### 思路

同一个按键上的第几个字母，就需要按几次。例如 `abc` 在同一个键上，`a` 需要 1 次，`b` 需要 2 次，`c` 需要 3 次。

先用字典预处理每个字符的按键次数：

```text
a -> 1, b -> 2, c -> 3, ...
空格 -> 1
```

然后扫描整句话，把每个字符对应的次数加起来。

这题是字符映射和累加练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：包含空格的一行要整行读取。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：普通 `dict` 适合保存字符到次数的映射。
- `enumerate(group)` 可以同时得到组内下标和字符。
- `sum(press_count[ch] for ch in sentence)` 用生成器表达式累加。

### 代码

@include-code(./main.py, python)

### 复杂度

设句子长度为 `n`，时间复杂度是 $O(n)$，字典大小固定，空间复杂度是 $O(1)$。

### 总结

固定规则的字符题，先预处理一张映射表，再逐字符扫描，代码会比写很多 `if` 更清楚。
