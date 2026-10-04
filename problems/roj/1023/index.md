---
oj: "roj"
problem_id: "1023"
title: "Hello,World!的大小"
description: "C 字符串字面量在可见字符外还隐含一个 '\\0' 结束符，Python 侧用 len(字面量) + 1 复刻 sizeof 语义，一次打印即得 14。"
difficulty: "入门"
date: 2026-09-29 13:52
updated: 2026-09-29 13:53
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1023
---

[[TOC]]

## 形式化题目

输入为空。求 C 字符串字面量 `"Hello, World!"` 所占的字节数，输出一个整数。

样例：无输入，输出 `14`。

## 正解

### 思路

题面问的其实是 C 的 `sizeof("Hello, World!")`。C 语言里字符串字面量不是
"一串字符"，而是一个编译期建好的 `char` 数组：编译器在末尾自动追加一个
`'\0'` 结束符。所以它的大小 = 可见字符数 + 1：

$$\texttt{sizeof("Hello, World!")} = \underbrace{13}_{\text{可见字符}} + \underbrace{1}_{\texttt{'\\0'}} = 14$$

其中 13 的来源逐段清点：`Hello` 5 个 + `,` 1 个 + 空格 1 个 + `World` 5 个 +
`!` 1 个 = 13。

Python 的 `len()` 统计的是字符个数，`str` 没有结束符概念，因此
`len("Hello, World!")` 只得 13——直接打印它会差 1。要在 Python 里复刻 C 的
`sizeof` 语义，只需把那 1 字节的隐式 `'\0'` 手工补回来：**`len(s) + 1`**。

本题输入为空、答案是常数，不存在随数据增长的代价，也就没有可优化的瓶颈；
再写一个"暴力版本"只会得到同一行代码，因此直接给出常数解，不单设暴力层。

### 代码

@include-code(./main.py, python)

核心就是 `print(len("Hello, World!") + 1)`：`+ 1` 即 C 字面量隐含的结束符，
docstring 里写明了这条语义换算；题面"输入：无"，所以 `solve` 里没有任何读入。

### 复杂度

- 时间复杂度 $O(1)$：无输入，只打印一个常量。
- 空间复杂度 $O(1)$：只用到一个字面量和一个整数。

## 总结

`sizeof` 与 `len` 的差别在于那一个看不见的字节：C 的字符串字面量自带
`'\0'` 结束符，所以 `sizeof("Hello, World!")` 是 13 + 1 = 14；Python 的
`len()` 只数可见字符，等价写法是 `len("Hello, World!") + 1`。$O(1)$ 时间、
$O(1)$ 空间，一行打印即正解——这类"输出常量"题真正的考点是两种语言对字符串
占位语义的差异，而不是算法。
