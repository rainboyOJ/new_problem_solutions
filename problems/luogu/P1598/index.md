---
oj: "luogu"
problem_id: "P1598"
title: "[USACO03FEB] 垂直柱状图 Vertical Histogram"
description: "统计 A 到 Z 的出现次数，从最高层向下逐行输出星号，并用 rstrip 删除行尾多余空格。"
difficulty: "普及-"
date: 2026-07-15 21:01
toc: true
tags: ["字符串", "计数", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1598
---

[[TOC]]

### 题意

读入四行字符，统计 `A` 到 `Z` 每个大写字母出现的次数，并按样例格式输出垂直柱状图。每一行末尾不能有多余空格。

### 思路

先统计 26 个大写字母的出现次数。设最高次数是 `max_height`，柱状图就从第 `max_height` 层往第 1 层输出。

对于某一层 `level`：

- 如果某个字母的次数 `>= level`，这一列输出 `*`；
- 否则输出空格。

列与列之间固定用一个空格隔开。整行生成后，用 `rstrip()` 删除右侧多余空格，避免违反格式要求。最后输出字母行：

```text
A B C ... Z
```

这题是计数和格式化输出练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`Counter` 可以统计字符出现次数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`" ".join(row)` 拼接一行输出。
- `chr(ord("A") + i)` 生成第 `i` 个大写字母。
- `rstrip()` 删除行尾空格，保留中间空格。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Guide 风格代码

cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：

@include-code(./main-guide.cpp, cpp)

### Pythonic 写法

`Counter` 统计字母，按高度逐行输出柱状图：

@include-code(./main-pythonic.py, python)

### 复杂度

输入总长度最多约 400，统计和输出都很小。若用总字符数 `n`、最高柱高 `h` 表示，时间复杂度是 $O(n + 26h)$，空间复杂度是 $O(1)$。

### 总结

垂直柱状图的关键是“按高度从上到下输出”。生成含空格的格式化行后，最后统一 `rstrip()` 去掉行尾多余空格。
