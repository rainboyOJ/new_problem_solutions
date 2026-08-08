---
oj: "luogu"
problem_id: "P1308"
title: "[NOIP 2011 普及组] 统计单词数"
description: "在文章两端补空格后查找带空格的目标单词，从而实现不区分大小写的整词匹配。"
difficulty: "普及-"
date: 2026-06-19 10:13
toc: true
tags: ["字符串", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1308
---

[[TOC]]

### 题意

给定一个目标单词和一整行文章。匹配时不区分大小写，但必须匹配完整单词，不能只匹配某个长单词的一部分。输出出现次数和第一次出现的位置；如果没有出现，输出 `-1`。

### 思路

先把目标单词和文章都转成小写。

为了保证“完整单词”匹配，可以在文章两端各补一个空格，并把目标单词也变成 `" " + word + " "`。这样只有左右都是边界空格时才会匹配。

如果：

```text
padded_article = " " + article + " "
padded_word = " " + word + " "
```

那么 `padded_article.find(padded_word)` 返回的位置，刚好等于目标单词在原文章中的起始位置。

这题是整行输入和字符串查找练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：文章包含空格，需要整行读取，不能用 `split()` 丢掉空格位置。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`lower()`、`find()`、`count()` 是常用字符串操作。
- `rstrip("\n")` 只删除行末换行，保留文章中的空格。
- `find()` 找不到返回 `-1`。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

`re.finditer` + 单词边界统计出现次数与首位置：

@include-code(./main-pythonic.py, python)

### 复杂度

设文章长度为 `n`，字符串查找和计数都是线性级别，时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

整词匹配的关键是处理边界。给文章和目标词补空格，可以把“左右是单词边界”的判断转化成普通子串查找。
