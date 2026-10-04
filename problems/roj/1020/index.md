---
oj: "roj"
problem_id: "1020"
title: "打印ASCII码"
description: "读入一个可见字符，用内建函数 ord() 直接取其 ASCII 码输出，一次读取一次转码，O(1) 完成"
difficulty: "入门"
date: 2026-09-29 13:42
updated: 2026-09-29 13:43
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1020
---

[[TOC]]

## 形式化题目

给定一个除空格外的可见字符 $\text{ch}$，求它在 ASCII 表中的编号，即

$$
f(\text{ch}) = \text{ch 在 ASCII 表中的下标}
$$

并以十进制整数输出。例如样例中 $\text{ch} = \texttt{A}$，而 `A` 在 ASCII 表中
排第 65 位，故输出 $65$。

## 正解

### 思路

题目只要求"字符 → 编号"的一次映射查询，没有任何循环、状态或数据范围，
所以朴素做法本身就是最终做法，关键只在 **Python 里怎么完成这次映射**。

在 C/C++ 中 `printf("%d", ch)` 能直接输出，是因为 `char` 会整型提升为 `int`；
但 Python 的字符是长度为 1 的字符串，没有数值语义，需要显式调用内建函数
`ord(ch)`——它返回字符的 Unicode 码点，对可见 ASCII 字符恰好等于其 ASCII 码。

读入方面，输入只有一个字符（外加一个换行）：

1. `sys.stdin.buffer.read()` 读出全部字节；
2. `.split()` 按空白切成列表，顺带吞掉尾随换行，取 `[0]` 就是那个字符的字节串；
3. `.decode()` 转回 `str`（ASCII 字符的 UTF-8 编码恒等），交给 `ord`。

题面保证字符"除空格外可见"，所以空白切分不会把字符本身切碎——这正是
`split()[0]` 这条路线安全的原因。整个 `solve()` 只做读入、转码、输出三件事，
不需要任何辅助函数或预计算。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(1)$：读入字节数为常数（1 个字符 + 换行），`split`、`decode`、
  `ord` 各执行一次。
- 空间复杂度：$O(1)$：一个字节串和一个长度为 1 的字符串，与输入规模无关。

## 总结

- 字符到编号的查询在 Python 里就是 `ord(ch)`：它与 C 的 `char→int` 提升、
  `printf("%d")` 回答的是同一个问题，只是 Python 需要显式调用。
- 读单字符输入的简洁写法是 `sys.stdin.buffer.read().split()[0].decode()`：
  `.split()` 同时解决"取第一个 token"和"去掉换行"，前提是输入不含空格
  （本题题面恰好保证了这一点）。
- 本题时间 $O(1)$、空间 $O(1)$，10 组真实测试数据全部通过，远低于
  1000ms / 128MB 的限制。
