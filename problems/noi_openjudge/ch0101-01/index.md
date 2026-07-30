---
oj: "noi_openjudge"
problem_id: "ch0101-01"
title: "Hello, World!"
description: "使用 print 严格输出题面指定的固定字符串。"
difficulty: "入门"
date: 2026-07-30 22:43
toc: true
tags: ["输出", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0101/01/
---

[[TOC]]

### 题意

本题没有输入。输出一行且只能输出字符串 `Hello, World!`。

判题会比较输出内容，因此 `Hello` 后是英文逗号，逗号后还有一个半角空格；不能额外输出提示文字。

### 思路

这是输出格式练习，不需要计算、读入或分支。程序的唯一工作是把题面指定的完整字符串交给 `print`：

```text
Hello, World!
```

Python 的 `print` 默认在末尾补一个换行，正好对应“一行输出”的要求。不要额外打印提示语，也不要遗漏逗号后的空格。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

输出的字符数固定，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

固定输出题的关键是逐字符核对：大小写、英文标点、空格和换行都属于输出格式的一部分。Python 中直接写 `print("Hello, World!")` 即可，不需要任何输入模板。
