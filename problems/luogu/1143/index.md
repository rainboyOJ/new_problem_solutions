---
oj: "luogu"
problem_id: "P1143"
title: "进制转换"
description: "用 int(text, base) 转成十进制整数，再反复 divmod 得到目标进制数码。"
difficulty: "入门"
date: 2026-07-16 19:20
toc: true
tags: ["进制转换", "字符串", "divmod", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1143
---

[[TOC]]

### 题意

把一个 `2..16` 进制的非负整数转换成另一个 `2..16` 进制表示。

### 思路

先把源字符串转换为整数，再做目标进制短除法。每次 `divmod(value,base)` 得到新的商和最低位余数，余数映射到 `0..F`；数码按低位到高位产生，最后反转。

值为 `0` 时短除循环不会执行，需要单独输出 `0`。

### Python 知识

- `int(number,source_base)` 原生支持 2 到 36 进制字符串解析。
- `divmod(a,b)` 一次返回商和余数。
- `DIGITS[remainder]` 把 10 到 15 映射为大写字母。
- `"".join(reversed(converted))` 连接逆序产生的数码。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串解析、切片与连接。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：Python 整数与 C++ 数值范围差异。

### 代码

@include-code(./main.py, python)


### 复杂度

设目标表示有 `d` 位，短除部分时间复杂度 $O(d)$，空间复杂度 $O(d)$。

### 总结

Python 已经解决“任意进制字符串到整数”，我们只需掌握整数到目标进制的 `divmod` 模板。
