---
oj: "luogu"
problem_id: "P1098"
title: "[NOIP 2007 提高组] 字符串的展开"
description: "逐字符扫描字符串，遇到减号时按可展开性、字符变换、重复次数和正逆序规则做分类模拟。"
difficulty: "普及/提高-"
date: 2026-06-19 10:06
toc: true
tags: ["字符串", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1098
---

[[TOC]]

### 题意

给定参数 `p1,p2,p3` 和一个字符串。字符串中某些减号可以展开成中间的连续字符；展开时还要控制大小写、重复次数和正逆序。

### 思路

从左到右扫描字符串。普通字符直接加入答案。遇到 `-` 时，检查它左右两边字符：

- 两边同为数字或同为小写字母；
- 右边字符 ASCII 严格大于左边字符。

不满足则保留 `-`。满足时枚举中间字符，不包括两端字符：

```text
ord(left)+1 ... ord(right)-1
```

再按 `p3` 决定是否反转顺序，按 `p1` 决定输出原字符、大写或 `*`，按 `p2` 决定重复次数。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串支持下标访问、`isdigit()`、`islower()`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：构造长答案时用列表收集片段再 `join`。
- `ord()` 和 `chr()` 可以在字符和 ASCII 编码之间转换。
- `chars.reverse()` 原地反转列表。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

设原串长度为 `n`，展开后新增字符总数为 `L`，时间复杂度是 $O(n+L)$，空间复杂度是 $O(n+L)$。

### 总结

本题关键是先判断减号是否有资格展开，再处理大小写、星号、重复和顺序。把展开逻辑封装成函数可以减少主循环分支。
