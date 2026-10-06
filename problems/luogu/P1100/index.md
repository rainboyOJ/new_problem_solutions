---
oj: "luogu"
problem_id: "P1100"
title: "高低位交换"
description: "用掩码取出低 16 位并左移，同时把高 16 位右移，再按位或合并。"
difficulty: "入门"
date: 2026-07-16 19:20
updated: 2026-10-07 00:32
toc: true
tags: ["位运算", "掩码", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1100
---

[[TOC]]

### 题意

把一个 32 位无符号整数的高 16 位与低 16 位交换，输出新整数。

### 思路

`number>>16` 把高半部分移动到低位；`number&0xFFFF` 只保留低 16 位，再左移 16 位。两部分没有重叠，用按位或合并：

```text
(number >> 16) | ((number & 0xFFFF) << 16)
```

### Python 知识

- 十六进制字面量 `0xFFFF` 正好是 16 个二进制 `1`。
- `&` 是按位与掩码，`<<`、`>>` 是位移，`|` 合并位段。
- Python 整数没有固定 32 位，但输入范围保证上述结果与无符号 32 位运算一致。
- 一行表达式已完整表达算法，不需要额外函数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：Python 与 C++ 固定位宽整数差异。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

位运算高低互换：

@include-code(./main-pythonic.py, python)

### STL 写法

把整数装进 `bitset<32>` 后每一位都有确定的下标：下标 0 是最低位，下标 31 是最高位，于是「高 16 位」就是下标 16..31、「低 16 位」是下标 0..15。`bits << 16` 把低半段顶到高位、`bits >> 16` 把高半段落回低位，两段互不重叠，按位或合并就完成了交换，最后用 `to_ulong()` 转回十进制输出。和上面 `main.cpp` 直接对整数做掩码位移相比，这里不必手写 `0xFFFF`，位段的位置由下标直接说明；读入用 `unsigned long long`，因为输入可能达到 $2^{32}-1$，超出 `int` 的范围。

对应的 cppbook 章节：[bitset：一组二进制开关](https://cppbook.roj.ac.cn/stl/bitset/)

@include-code(./main-stl.cpp, cpp)

### 复杂度

固定次数位运算，时间和额外空间复杂度均为 $O(1)$。

### 总结

位段操作的标准步骤是“掩码取出、位移到位、按位或合并”。
