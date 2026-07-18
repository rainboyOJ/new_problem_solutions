---
oj: "luogu"
problem_id: "P5015"
title: "[NOIP 2018 普及组] 标题统计"
description: "整行读入标题后，顺序扫描并统计所有不是空格的字符个数即可。"
difficulty: "入门"
date: 2026-06-19 09:32
toc: true
tags: ["模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5015
---

[[TOC]]

### 题意

给出一行标题字符串。

标题中可能包含：

- 大写字母
- 小写字母
- 数字
- 空格

要求统计标题中有多少个有效字符。这里空格不算字符，换行符也不算。

### 思路

这题就是顺序扫描字符串。

只要把整行读进来，然后统计里面有多少个字符不是空格即可。

#### 为什么要用整行读入

因为标题里可能包含空格。

如果用 `input().split()`，空格会被当成分隔符丢掉；如果后续还要保持原始行结构，这就不合适。

所以这里按整行读取，再只删除行末换行符。

#### 为什么只需要判断空格

题目已经说了：

- 空格不计入
- 行末换行符也不计入

`sys.stdin.readline().rstrip("\n")` 删除行末换行符，但保留标题内部的空格。之后跳过空格，其余字符全部计数即可。

这题是整行输入和字符过滤练习，不创建 `brute.py`。目录中保留的旧 C++ 文件只是历史版本，本文以 Python 代码为准。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：包含空格的整行文本不能用 `split()` 直接读。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`sys.stdin.readline()` 可以读取完整一行。
- `rstrip("\n")` 只去掉换行，不会误删标题首尾空格。
- `sum(1 for ch in title if ch != " ")` 用生成器表达式统计满足条件的字符数。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

`replace` 去掉空格后直接 `len`：

@include-code(./main-pythonic.py, python)

### 复杂度

- 时间复杂度：$O(n)$
- 空间复杂度：$O(1)$

其中 `n` 是标题长度。

### 总结

这题的唯一坑点就是输入中有空格。

只要记得用 `getline`，再把空格过滤掉，问题就结束了。
