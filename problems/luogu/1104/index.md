---
oj: "luogu"
problem_id: "P1104"
title: "生日"
description: "把生日和输入顺序组成排序键，按年月日升序、同生日后输入在前输出姓名。"
difficulty: "入门"
date: 2026-06-19 10:10
toc: true
tags: ["排序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1104
---

[[TOC]]

### 题意

输入若干同学的姓名和生日，按年龄从大到小输出姓名。年龄大等价于生日更早。

如果两个人生日完全相同，后输入的人先输出。

### 思路

这是多关键字排序。

对每个同学保存：

```text
(年, 月, 日, -输入顺序, 姓名)
```

Python 元组会从左到右比较。年月日越小，生日越早，年龄越大；同一天生日时，输入顺序越靠后，`-输入顺序` 越小，也就排得越前。

排序后依次输出姓名即可。

### Python 知识

- `name, year, month, day = input().split()` 可以同时读取一个字符串和三个数字字段。
- 元组天然支持多关键字排序，`students.sort()` 会按第 1 项、第 2 项、第 3 项依次比较。
- 字符串字段 `year/month/day` 要转成 `int`，否则字符串比较会按字典序，不是数字大小。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

### 总结

多关键字排序时，先把题目的比较规则逐项写出来，再把它翻译成一个元组排序键。
