---
oj: "roj"
problem_id: "1018"
title: "其他数据类型存储空间大小"
description: "用 ctypes 的 c_bool/c_char 测量 C 类型的字节数再输出，与评测端 sizeof 同源，既不硬编码也避开 sys.getsizeof 的对象语义"
difficulty: "入门"
date: 2026-09-29 13:31
updated: 2026-09-29 13:31
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1018
---

[[TOC]]

## 形式化题目

对 C++ 的两个基本类型 `bool` 与 `char`，分别求出一个变量占用的存储空间大小
（单位：字节），即 $\texttt{sizeof(bool)}$ 与 $\texttt{sizeof(char)}$，
按先 `bool` 后 `char` 的顺序输出。本题无输入、无样例数据。

## 正解

### 思路

题面给的是 C++ 视角的问题：参考实现 `std.cpp` 就是
`cout << sizeof(bool) << " " << sizeof(char)`，评测答案 `1 1` 由编译器的
`sizeof` 语义决定。但本题要求用 Python 提交，而 Python 里没有 `sizeof`
运算符——`bool` 是 `int` 的子类，连 `char` 类型都不存在。于是"怎么在 Python
里得到 C 的 sizeof"就成了本题唯一要解决的问题，有三条候选路线：

| 做法 | 测的是什么 | 得到的值 | 评价 |
| --- | --- | --- | --- |
| 硬编码 `print("1 1")` | 不测量 | `1 1` | 能过，但是魔法数字，无法论证 |
| `sys.getsizeof(True)` | Python 对象的堆大小 | `28` | 语义错误：问的是类型宽度 |
| `ctypes.sizeof(c_bool/c_char)` | C 类型的存储宽度 | `1 1` | 与评测端 `sizeof()` 同源 |

关键观察有两点：

1. **题面要的是"类型占几字节"，不是"对象占几字节"。** `sys.getsizeof(True)`
   返回 28，因为那是 CPython 里 `True` 这个整型对象的堆内存；而题面问的是
   C 把一个 `bool` 存下来需要几个字节。两者数量级完全不同，用错就直接 WA。
2. **`ctypes` 与 C 共享同一套 ABI。** `ctypes.c_bool` 对应 C99 的 `_Bool`、
   `ctypes.c_char` 对应 C 的 `char`，`ctypes.sizeof()` 返回的就是编译器
   `sizeof()` 的结果，与评测端 `std.cpp` 的计算依据完全相同：`char` 按定义
   恰为 1 字节（`CHAR_BIT = 8` 时），`bool` 在 gcc/clang/MSVC 等常见实现中
   也是 1 字节，故输出 `1 1`。

正因为答案是常数，测量放在**模块级常量** `BOOL_SIZE` / `CHAR_SIZE` 里——名字
本身就是题面两个类型的注解，进程内算一次即可；`solve()` 只负责输出。
输出格式则直接交给 `print`：它默认 `sep=' '`（正是题面的单空格）和
`end='\n'`，不需要任何字符串拼接。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(1)$：两次 `ctypes.sizeof` 常量查询加一次输出，与输入无关
  （本题也没有输入）。
- 空间复杂度：$O(1)$：两个模块级整型常量与一行输出字符串。

## 总结

- 答案是常数 `1 1`，但题解的意义在于**怎么得到它**：用 `ctypes.sizeof`
  测量，依据与评测端的 `sizeof()` 是同一个 C ABI，而不是把 `1` 硬编码。
- `sys.getsizeof` 测 Python 对象的堆大小（`True` 是 28 字节），回答不了
  "类型存储宽度"的问题——看清题目问的是哪一种"大小"。
- 输出格式无需手工拼接：`print(a, b)` 的默认 `sep=' '` 和 `end='\n'`
  恰好就是"一行、单空格隔开"。
