---
oj: "roj"
problem_id: "1016"
title: "整型数据类型存储空间大小"
description: "Python 没有固定宽度的 int/short，用 struct.calcsize 取 C ABI 类型宽度（'i'=int、'h'=short）替代 sizeof，按序输出 4 2。"
difficulty: "入门"
date: 2026-09-29 13:31
updated: 2026-09-29 13:33
toc: true
tags: ["入门", "语法", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1016
---

[[TOC]]

## 形式化题目

求当前 C/C++ 评测环境中 `int` 与 `short` 的存储空间大小（单位：字节），并按此顺序输出两个整数：

$$
\bigl(\operatorname{sizeof}(\texttt{int}),\ \operatorname{sizeof}(\texttt{short})\bigr)
$$

本题无输入，输出是一个常数二元组；在本评测平台（g++ / 64 位 x86）上等于 $(4, 2)$，
即输出 `4 2`。

## 正解

### 思路

本题没有输入，也没有规模 $n$，所以不存在"先写朴素做法、再消除瓶颈"的空间——真正需要想清楚的是
**这两个数从哪里来**。

**1. 不能用 Python 的 `int` 去量。** Python 的 `int` 是任意精度对象，`sys.getsizeof(3)` 得到的是
对象头加数字位的运行时开销，与 C 的 `sizeof(int)` 不是一回事；用它能算出的答案毫无意义。

**2. 答案依赖平台，所以别手写常数。** C 标准只保证

$$
\operatorname{sizeof}(\texttt{char}) = 1, \qquad
\operatorname{sizeof}(\texttt{short}) \leqslant \operatorname{sizeof}(\texttt{int})
\leqslant \operatorname{sizeof}(\texttt{long})
$$

并不保证 `int` 一定是 4 字节。`4 2` 是**平台事实**而非语言事实：换一个 16 位 ABI，`int` 可能只有
2 字节。直接把 `print(4, 2)` 写进代码，在本题能过，却把平台结论硬编码了。

**3. 把查询委托给声明了同一套 ABI 的标准库。** `struct` 的格式字符按 C ABI 定义类型宽度，
`struct.calcsize(code)` 返回它在当前平台的字节数，语义正是 `sizeof`：

| C 类型 | `struct` 格式字符 | 本平台字节数 | C 标准保证 |
| --- | --- | --- | --- |
| `char` | `'b'` | 1 | 恒为 1 |
| `short` | `'h'` | 2 | $\leqslant \operatorname{sizeof}(\texttt{int})$ |
| `int` | `'i'` | 4 | $\geqslant 2$，通常 4 |
| `long long` | `'q'` | 8 | $\geqslant \operatorname{sizeof}(\texttt{long})$ |

表中第二列是 Python 侧的表达方式，第三列是与 g++ `sizeof` 一致的结果。于是题目要求的两个数就是
`struct.calcsize("i")` 与 `struct.calcsize("h")`：平台变了答案自动跟随，代码里不再出现魔法常数。
（`array.array("i").itemsize` 是同一思路的另一种写法，只是多构造一个对象。）

最后按题面顺序输出即可：两个量各只出现一次，交给 `print` 的默认空格分隔，
`print(INT_SIZE, SHORT_SIZE)` 得到 `4 2`，与真实输出 `problem1.out` 一致。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(1)$，两次 `calcsize` 调用与一次输出，与 C++ 直接 `sizeof` 同为常数时间。
- 空间复杂度：$O(1)$，只保存两个整数常量。

## 总结

- 题目问的是 C/C++ 的类型宽度，不能用 Python 对象大小（`sys.getsizeof`）回答。
- `int` 的宽度由平台决定，C 标准只规定相对大小关系，所以答案来自评测环境。
- Python 侧的对应工具是 `struct.calcsize`：`'i'` ↔ `int`、`'h'` ↔ `short`，
  等价于 `sizeof`，且比硬编码 `4 2` 更稳健。
- 本题无输入、无循环、无状态，直接正解，复杂度为 $O(1)$。
