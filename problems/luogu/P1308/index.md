---
oj: "luogu"
problem_id: "P1308"
title: "[NOIP 2011 普及组] 统计单词数"
description: "在文章两端补空格后查找带空格的目标单词，从而实现不区分大小写的整词匹配。"
difficulty: "普及-"
date: 2026-06-19 10:13
updated: 2026-10-07 12:15
toc: true
tags: ["字符串", "模拟", "python"]
categories: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0107-17"
    reason: "B 复用 A 教的「统一 lower() 规范化实现忽略大小写」这一步做不区分大小写匹配，再叠加 A 未教的两端补空格判完整单词边界与 find/count 定位统计。"
  - oj: "noi_openjudge"
    problem_id: "ch0107-18"
    reason: "B 的单词统计用 A 教的子串存在性判定做完整单词匹配（两端补空格后查找 \" word \" 子串并计数与取首现位置），再叠加大小写归一与边界补空格技巧"
  - oj: "noi_openjudge"
    problem_id: "ch0107-16"
    reason: "B 复用 A 的转小写规范化步骤，在统一大小写后再做完整单词的补空格查找匹配"
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

### Guide 风格代码

cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：

@include-code(./main-guide.cpp, cpp)

### Pythonic 写法

`re.finditer` + 单词边界统计出现次数与首位置：

@include-code(./main-pythonic.py, python)

### STL 写法

用 `string` 的 `find` 做整词匹配：把目标单词和文章都转成小写，再各补一个空格，然后在补过空格的文章里循环查找 `" " + word + " "`，每次都用 `string::npos` 判断是否还要继续找。因为 `find` 返回的下标指向单词左边那个边界空格，这个下标正好就是单词首字母在原文里的位置，不用再换算。相比上面手写的逐词切分，这里省掉了 `left`、`right` 两个下标的维护，代价是额外拼出两个补空格的字符串。

对应的 cppbook 章节：[string：把字符串当作可操作的数据](https://cppbook.roj.ac.cn/stl/string/)

@include-code(./main-stl.cpp, cpp)

### 复杂度

设文章长度为 `n`，字符串查找和计数都是线性级别，时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

整词匹配的关键是处理边界。给文章和目标词补空格，可以把“左右是单词边界”的判断转化成普通子串查找。
