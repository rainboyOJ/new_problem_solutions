---
oj: "luogu"
problem_id: "P1307"
title: "[NOIP 2011 普及组] 数字反转"
description: "先拆出负号，用字符串切片反转数字部分，再用 int 自动去掉前导零。"
difficulty: "入门"
date: 2026-06-18 23:15
toc: true
tags: ["模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1307
---

[[TOC]]

### 题意

给定一个整数 `N`，把它的十进制数字顺序反转后输出。

需要注意：

- 如果原数是负数，负号仍然放在最前面；
- 反转后不能保留多余前导零。

### 思路

Python 处理这题最自然的方法是把输入当成字符串。

先判断它是否以 `-` 开头。如果是负数，就把负号单独记下来，只反转后面的数字部分。

数字部分用切片 `digits[::-1]` 反转。反转后可能出现前导零，例如 `380` 反转为 `"083"`。再套一层 `int(...)`，字符串会被转回整数，前导零自然消失。

最后，如果原数是负数，把答案取负即可。

这题主要训练字符串切片和整数转换。旧目录里保留了 C++ 暴力与数位版本；Python 教学版不新增 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：本题用到 `input().strip()`、`startswith` 和字符串切片。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单行字符串输入可以直接使用 `input()`。
- `text[1:]` 表示从下标 `1` 取到末尾，用来去掉负号。
- `digits[::-1]` 表示整串反向切片。
- `int("083")` 会得到整数 `83`，正好用于去掉前导零。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

切片反转去零：

@include-code(./main-pythonic.py, python)


### 复杂度

设数字位数为 `k`。字符串反转和整数转换都是 $O(k)$，空间复杂度也是 $O(k)$。

### 总结

这题用 Python 写时，不必手动一位一位取模。切片负责反转，`int` 负责消除前导零，符号单独处理即可。
