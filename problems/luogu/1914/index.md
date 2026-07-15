---
oj: "luogu"
problem_id: "P1914"
title: "小书童——凯撒密码"
description: "把每个小写字母转成 0 到 25 的编号，平移 n 位后取模再转回字符。"
difficulty: "入门"
date: 2026-07-15 20:30
toc: true
tags: ["字符串", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1914
---

[[TOC]]

### 题意

给定一个位移量 `n` 和一个只含小写字母的字符串。每个字母向后移动 `n` 位，超过 `z` 后从 `a` 继续循环，输出移动后的密码。

### 思路

把字符看成字母表中的编号：

```text
a -> 0, b -> 1, ..., z -> 25
```

一个字符 `ch` 平移 `n` 位后，新编号是：

```text
(old + n) % 26
```

再把新编号加回到 `'a'` 的 ASCII 编码，就能得到新字符。

这题是字符编码和取模循环练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `input()` 读取字符串，用列表收集结果后 `"".join(...)` 输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：第一行整数、第二行字符串可以分别读取。
- `ord(ch)` 把字符转成编码，`chr(x)` 把编码转回字符。
- `% 26` 表达字母表循环。

### 代码

@include-code(./main.py, python)

### 复杂度

设字符串长度为 `m`，时间复杂度是 $O(m)$，空间复杂度是 $O(m)$。

### 总结

凯撒密码的关键是先把字母映射成数字，再用取模处理循环。
