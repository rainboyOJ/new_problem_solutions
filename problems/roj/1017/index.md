---
oj: "roj"
problem_id: "1017"
title: "浮点型数据类型存储空间大小"
description: "用 struct.calcsize 查询 float/double 的字节数，得到 C 语言 sizeof 的等价结果，print 以默认空格分隔直接输出。"
difficulty: "入门"
date: 2026-09-29 13:30
updated: 2026-09-29 13:32
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1017
---

[[TOC]]

## 形式化题目

无输入。要求输出两个常数：C/C++ 中 `float` 类型变量与 `double` 类型变量各占多少字节，用一个空格隔开。这由语言标准确定——`float` 是 IEEE 754 单精度、`double` 是双精度，与平台字长无关，答案恒为：

```
4 8
```

本题的实质是：Python 自己的 `float` 统一是双精度，没有"单精度变量"这一概念，所以要找一个能回答"`float` 占几字节"的等价查询，而不是把 `4 8` 硬编码进代码。

## 正解

### 思路

这道题没有循环、状态或搜索，也不存在"先写朴素做法、再消除瓶颈"的空间——`print(4, 8)` 和"查询后输出"跑起来完全一样，慢版本只会是同一份代码的劣化。真正值得讲的是**这两个数从哪来**：抄答案进字面量，读者无法验证，也无法迁移到别的类型（`long long` 占几字节？）。

C 里答案来自 `sizeof(float)` / `sizeof(double)`，Python 的对应物是 `struct` 模块的 `calcsize`：

```python
import struct
struct.calcsize("f")   # 4，格式 "f" = C 的 float（单精度）
struct.calcsize("d")   # 8，格式 "d" = C 的 double（双精度）
```

`calcsize` 返回某种 C 结构格式占的字节数，语义与 `sizeof` 一致：查询在导入时就完成（相当于 C 的编译期常量），且答案由标准库给出而非手写数字。

两个查询结果各只出现一次，按惯例提成模块级常量，名字就是题面两个名词的注解：

| 常量 | 查询 | 含义 | 输出 |
| --- | --- | --- | --- |
| `FLOAT_SIZE` | `struct.calcsize("f")` | 单精度字节数 | `4` |
| `DOUBLE_SIZE` | `struct.calcsize("d")` | 双精度字节数 | `8` |

最后 `print(FLOAT_SIZE, DOUBLE_SIZE)`：题目要"一个空格隔开"，而 `print` 的默认 `sep` 正是单空格，不必手拼字符串；本题无输入，`solve()` 里也不需要读 stdin。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(1)$：两次 `calcsize` 在模块导入时完成（等价于编译期常量），运行期只有一次 `print`。
- 空间复杂度：$O(1)$：只保存两个整数常量与一行输出字符串。

## 总结

- `float` 4 字节、`double` 8 字节是语言标准钦定的常量，但答案应**查询得到**：`struct.calcsize("f")` / `("d")` 就是 Python 侧的 `sizeof`。
- 输出量只出现一次也值得命名——`FLOAT_SIZE`、`DOUBLE_SIZE` 这两个名字本身就是题面的注解。
- "空格分隔的两个数"用 `print(a, b)` 的默认 `sep` 即可，无需自己拼接。
